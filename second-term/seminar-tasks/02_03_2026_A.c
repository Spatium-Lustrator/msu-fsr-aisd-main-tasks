/* 
    This is an implementation of the Ford-Fulkerson algorithm,
    specifically the Edmonds-Karp algorithm (the search for the next path
    is based on breadth-first traversal)
*/

#include <stdlib.h>
#include <stdio.h>

// Define values
#define INFINITY 2147483647

// Path
typedef struct path_node {
    int from_vertex;
    int to_vertex;
    struct path_node *next;
} path_node;

typedef struct path {
    int min_capacity;
    int exist;
    path_node *start;

} path;

// Queue
typedef struct queue_element {
    int value;
    struct queue_element *next;

} queue_element;

typedef struct queue {
    queue_element *head;
    queue_element *tail;
    int size;

} queue;

void push(queue *queue, int value) {
    queue_element *new_element = (queue_element*) malloc(sizeof(queue_element));

    new_element->next = NULL;
    new_element->value = value;

    if (queue->size > 0) {
        queue->tail->next = new_element;
        queue->tail = new_element;
    } else {
        queue->head = queue->tail = new_element;
    }

    queue->size += 1;
}

int pop(queue *queue) {
    int result = -1;
    queue_element *head;

    if (queue->size > 0) {
        head = queue->head;

        result = head->value;
        if (queue->size == 1) queue->tail = NULL;
        queue->head = head->next;
        queue->size -= 1;
        
        free(head);

    }

    return result;
}

int is_not_empty(queue *queue) {
    return (queue->size > 0);
}

// BFS
void find_path_breadth_first_search(int **remnant_capacity, int *previous_vertexes, queue *queue, int count_of_vertexes, int index_start, int index_end) {
    int i, current_vertex;

    for (i=0; i<count_of_vertexes; i++) previous_vertexes[i] = -1;
    push(queue, index_start);
    while (is_not_empty(queue)) {
        current_vertex = pop(queue);
        for (i=0; i<count_of_vertexes; i++) {
            if (remnant_capacity[current_vertex][i] != 0 && previous_vertexes[i] == -1) {
                previous_vertexes[i] = current_vertex;
                push(queue, i);
            }
        }
    }


} 

// Put path to list in corret order and get minimum capacity
void add_new_vertex_to_the_path(int **remnant_capacity, int *previous_vertexes, path *current_path, int index_start, int index_current) {
    int index_previous_vertex;
    path_node *new_path_node;


    if (index_current != index_start) {
        index_previous_vertex = previous_vertexes[index_current];
        if (index_previous_vertex == -1) {
            current_path->exist = 0;
        } else {
            if (current_path->min_capacity > remnant_capacity[index_previous_vertex][index_current]) current_path->min_capacity = remnant_capacity[index_previous_vertex][index_current];

            new_path_node = (path_node*) malloc(sizeof(path_node));
            new_path_node->from_vertex = index_previous_vertex;
            new_path_node->to_vertex = index_current;
            new_path_node->next = current_path->start;

            current_path->start = new_path_node;

            add_new_vertex_to_the_path(remnant_capacity, previous_vertexes, current_path, index_start, index_previous_vertex);

        }
    }
}

path* restore_path(int **remnant_capacity, int *previous_vertexes, int index_start, int index_end) {
    path *new_path = (path*) malloc(sizeof(path));

    new_path->min_capacity = INFINITY;
    new_path->start = NULL;
    new_path->exist = 1;

    add_new_vertex_to_the_path(remnant_capacity, previous_vertexes, new_path, index_start, index_end);    

    return new_path;

    
}

void free_path(path *path_to_free) {
    path_node *current = path_to_free->start;
    path_node *next;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }

}

// Launch bfs and restore path
path* get_path(int **remnant_capacity, int *previous_vertexes, queue *queue, int count_of_vertexes, int index_start, int index_end) {
    find_path_breadth_first_search(remnant_capacity, previous_vertexes, queue, count_of_vertexes, index_start, index_end);

    return restore_path(remnant_capacity, previous_vertexes, index_start, index_end);
}

int find_maximum_flow(int **remnant_capacity, int *previous_vertexes, queue *queue, int count_of_vertexes, int index_start, int index_end) {
    path_node *current_path_node;
    path *current_path;
    int i, result = 0;


    current_path = get_path(remnant_capacity, previous_vertexes, queue, count_of_vertexes, index_start, index_end);
    

    while (current_path && current_path->exist) {
        current_path_node = current_path->start;
        result += current_path->min_capacity;
        while(current_path_node) {
            remnant_capacity[current_path_node->from_vertex][current_path_node->to_vertex] -= current_path->min_capacity;
            remnant_capacity[current_path_node->to_vertex][current_path_node->from_vertex] += current_path->min_capacity;
            current_path_node = current_path_node->next;
        }

        free_path(current_path);
        current_path = get_path(remnant_capacity, previous_vertexes, queue, count_of_vertexes, index_start, index_end);
    }

    return result;
}

int main(void) {
    // Variables initialization 
    int i;
    int from_vertex, to_vertex, weight, result;
    int count_of_vertexes, count_of_edges, index_start, index_end;
    int **capacity, *previous_vertexes; 

    queue *queue_of_vertexes;

    // Get info 
    scanf("%d %d %d %d", &count_of_vertexes, &count_of_edges, &index_start, &index_end);

    capacity = (int**) malloc(sizeof(int*)*count_of_vertexes);
    previous_vertexes = (int*) malloc(sizeof(int)*count_of_vertexes);

    queue_of_vertexes = (queue*) malloc(sizeof(queue));
    queue_of_vertexes->head = NULL;
    queue_of_vertexes->tail = NULL;
    queue_of_vertexes->size = 0;

    for (i=0; i<count_of_vertexes; i++) {
        capacity[i] = calloc(count_of_vertexes, sizeof(int));
    }

    for (i=0; i<count_of_edges; i++) {
        scanf("%d %d %d", &from_vertex, &to_vertex, &weight);
        capacity[from_vertex][to_vertex] = weight;
    }

    // Calculate result and show it 
    result = find_maximum_flow(capacity, previous_vertexes, queue_of_vertexes, count_of_vertexes, index_start, index_end);
    if (result == 0) {
        printf("The source and sink nodes are already disconnected");
    } else {
        printf("%d", result);
    }

    // Free used memory 
    for (i=0; i<count_of_vertexes; i++) {
        free(capacity[i]);
    }

    free(capacity);
    free(previous_vertexes);
    free(queue_of_vertexes);



    return 0;
}
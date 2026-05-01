#include <stdlib.h>
#include <stdio.h>

#define INFINITY 10000000

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
    int i, j, type;
    int from_vertex, to_vertex, weight, result=0;
    int count_of_vertexes, count_of_edges;
    int **capacity, *previous_vertexes; 
    int *is_source, *is_exit;

    queue *queue_of_vertexes;

    scanf("%d", &count_of_vertexes);

    capacity = (int**) malloc(sizeof(int*)*(count_of_vertexes+2));
    previous_vertexes = (int*) malloc(sizeof(int)*(count_of_vertexes+2));
    is_source = (int*) calloc(sizeof(int), count_of_vertexes);
    is_exit = (int*) calloc(sizeof(int), count_of_vertexes);

    queue_of_vertexes = (queue*) malloc(sizeof(queue));
    queue_of_vertexes->head = NULL;
    queue_of_vertexes->tail = NULL;
    queue_of_vertexes->size = 0;

    for (i=0; i<count_of_vertexes+2; i++) {
        capacity[i] = calloc(count_of_vertexes+2, sizeof(int));
    }

    for (i=0; i<count_of_vertexes; i++) {
        scanf("%d", &type);
        if (type==1) {
            is_source[i] = 1;
        } else if (type==2) {
            is_exit[i] = 1;
        }
    }

    for (i=0; i<count_of_vertexes; i++) {
        for (j=0; j<count_of_vertexes; j++) {
            scanf("%d", capacity[i+1] + j+1);
        }
    }

    for (i=0; i<count_of_vertexes; i++) {
        if (is_source[i]) {
            capacity[0][i+1] = INFINITY;
        } else if (is_exit[i]) {
            capacity[i+1][count_of_vertexes+1] = INFINITY;
        }
    }

    result = find_maximum_flow(capacity, previous_vertexes, queue_of_vertexes, count_of_vertexes+2, 0, count_of_vertexes+1);
    printf("%d", result);

    for (i=0; i<count_of_vertexes+2; i++) {
        free(capacity[i]);
    }

    free(capacity);
    free(previous_vertexes);
    free(queue_of_vertexes);
    free(is_exit);
    free(is_source);



    return 0;
}
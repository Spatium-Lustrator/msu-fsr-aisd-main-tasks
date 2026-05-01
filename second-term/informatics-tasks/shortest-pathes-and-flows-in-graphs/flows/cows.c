#include <stdio.h>
#include <stdlib.h>

#define INFINITY 10000000

typedef struct hummock {
    long long int x;
    long long int y;
} hummock;

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
    while (is_not_empty(queue)) pop(queue);
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

int hummock_equals_to_cords(hummock *h, long long int x, long long int y) {
    return (h->x == x) && (h->y == y);
}

int find_or_add_hummock(hummock **hummock_by_id, long long int x, long long int y, int max_count) {
    int i;
    hummock *new_h;

    for (i=0; i<max_count && hummock_by_id[i] != NULL && !hummock_equals_to_cords(hummock_by_id[i], x, y); i++);

    if (hummock_by_id[i] == NULL) {
        new_h = (hummock*) malloc(sizeof(hummock));
        new_h->x = x;
        new_h->y = y;
        hummock_by_id[i] = new_h;
    }

    return i;
}


int main(void) {
    long long int cfx, cfy, ctx, cty;
    int i, result=2;
    int index_start, index_end;
    int count_of_desks;
    int cur_index_from, cur_index_to;
    int **adjacency_matrix, *previous_vertexes;
    int count_of_hummocks, count_of_vertexes;

    
    hummock **hummock_by_id;
    queue *queue_of_vertexes;

    scanf("%d", &count_of_desks);

    count_of_hummocks = 3000*2 + 5;
    count_of_vertexes = count_of_hummocks*2;

    hummock_by_id = (hummock**) calloc(count_of_hummocks, sizeof(hummock*));
    adjacency_matrix = (int**) calloc(count_of_vertexes, sizeof(int*));
    previous_vertexes = (int*) malloc(sizeof(int)*(count_of_vertexes));

    queue_of_vertexes = (queue*) malloc(sizeof(queue));
    queue_of_vertexes->head = NULL;
    queue_of_vertexes->tail = NULL;
    queue_of_vertexes->size = 0;

    for (i=0; i<count_of_vertexes; i++) adjacency_matrix[i] = (int*) calloc(count_of_vertexes, sizeof(int));

    for (i=0; i<count_of_desks; i++) {
        scanf("%lld %lld %lld %lld", &cfx, &cfy, &ctx, &cty);
        cur_index_from = find_or_add_hummock(hummock_by_id, cfx, cfy, count_of_hummocks);
        cur_index_to = find_or_add_hummock(hummock_by_id, ctx, cty, count_of_hummocks);
        if (cur_index_from >= count_of_hummocks || cur_index_to >= count_of_hummocks) {
            printf("CAUGHT");
            return 0;
        }

        adjacency_matrix[2*cur_index_to][2*cur_index_to+1] = 1;

        adjacency_matrix[2*cur_index_from+1][2*cur_index_to] = INFINITY;
        adjacency_matrix[2*cur_index_to+1][2*cur_index_from] = INFINITY;


    }

    scanf("%lld %lld %lld %lld", &cfx, &cfy, &ctx, &cty);
    index_start = find_or_add_hummock(hummock_by_id, cfx, cfy, count_of_hummocks);
    index_end = find_or_add_hummock(hummock_by_id, ctx, cty, count_of_hummocks);

    adjacency_matrix[2*index_start][2*index_start+1] = INFINITY;
    adjacency_matrix[2*index_end][2*index_end+1] = INFINITY;

    result = find_maximum_flow(adjacency_matrix, previous_vertexes, queue_of_vertexes, count_of_vertexes, index_start*2+1, index_end*2);

    printf("%d", result);

    for (i=0; i<count_of_vertexes; i++) free(adjacency_matrix[i]);
    free(adjacency_matrix);
    free(queue_of_vertexes);
    free(hummock_by_id);
    free(previous_vertexes);


    return 0;
}
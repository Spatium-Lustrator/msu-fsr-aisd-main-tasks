#include <stdio.h>
#include <stdlib.h>

#define INFINITY 2147483647

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

// void breadth_first_search(int **remnant_capacity, int *previous_vertexes, queue *queue, int count_of_vertexes, int index_start, int index_end) {
//     int i, current_vertex;

//     for (i=0; i<count_of_vertexes; i++) previous_vertexes[i] = -1;
//     push(queue, index_start);
//     while (is_not_empty(queue)) {
//         current_vertex = pop(queue);
//         for (i=0; i<count_of_vertexes; i++) {
//             if (remnant_capacity[current_vertex][i] != 0 && previous_vertexes[i] == -1) {
//                 previous_vertexes[i] = current_vertex;
//                 push(queue, i);
//             }
//         }
//     }


// }


int main(void) {
    
    int number_of_available_right_turns, hall_width, hall_length; 
    int **hall_scheme, *distances;
    int start_cell, finish_cell;
    int i, j;

    scanf("%d %d %d", &number_of_available_right_turns, &hall_width, &hall_length);

    hall_scheme = (int**) calloc(hall_width, sizeof(int*));
    distances = (int*) calloc(hall_width*hall_length, sizeof(int));

    for (i=0; i<hall_width; i++) {
        hall_scheme[i] = (int*) calloc(hall_length, sizeof(int));
        for (j=0; j<hall_length; j++) {
            scanf("%d", hall_scheme[i] + j);
            if (hall_scheme[i][j] == 2) {
                start_cell = i*hall_width + j;
            } else if (hall_scheme[i][j] == 3) {
                finish_cell = i*hall_width + j;
            }

        }
    }




    return 0;
}
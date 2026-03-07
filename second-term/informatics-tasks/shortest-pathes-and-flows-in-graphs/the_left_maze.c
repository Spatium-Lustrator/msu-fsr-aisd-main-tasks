#include <stdio.h>
#include <stdlib.h>

#define INFINITY 2147483647
#define NOT_VISITED 0
#define WEST 1
#define EAST 2
#define NORTH 3
#define SOUTH 4
#define ANY 5

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

void update_neighbors_info(int *hall_scheme, int *distances, int *remaining_right_turns_per_cell, int *got_here_by_direction, queue *queue, int current_cell, int hall_width, int hall_length) {
    int total_cell_count = hall_length*hall_width;
    int cell_to_the_west = current_cell-1;
    int cell_to_the_east = current_cell+1;
    int cell_to_the_north = current_cell-hall_length;
    int cell_to_the_south = current_cell+hall_length;

    if (0 <= cell_to_the_west  && cell_to_the_west < total_cell_count && hall_scheme[cell_to_the_west] != 1 && got_here_by_direction[cell_to_the_west] == NOT_VISITED) {
        if (got_here_by_direction[current_cell] == SOUTH && remaining_right_turns_per_cell[current_cell] >= 1) {
            distances[cell_to_the_west] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_west] = remaining_right_turns_per_cell[current_cell] - 1;
            got_here_by_direction[cell_to_the_west] = WEST;
            push(queue, cell_to_the_west);
        } else if (got_here_by_direction[current_cell] != SOUTH) {
            distances[cell_to_the_west] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_west] = remaining_right_turns_per_cell[current_cell];
            got_here_by_direction[cell_to_the_west] = WEST;
            push(queue, cell_to_the_west);
        }
    }

    if (0 <= cell_to_the_east  && cell_to_the_east < total_cell_count && hall_scheme[cell_to_the_east] != 1 && got_here_by_direction[cell_to_the_east] == NOT_VISITED) {
        if (got_here_by_direction[current_cell] == NORTH && remaining_right_turns_per_cell[current_cell] >= 1) {
            distances[cell_to_the_east] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_east] = remaining_right_turns_per_cell[current_cell] - 1;
            got_here_by_direction[cell_to_the_east] = EAST;
            push(queue, cell_to_the_east);
        } else if (got_here_by_direction[current_cell] != NORTH) {
            distances[cell_to_the_east] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_east] = remaining_right_turns_per_cell[current_cell];
            got_here_by_direction[cell_to_the_east] = EAST;
            push(queue, cell_to_the_east);
        }
    }

    if (0 <= cell_to_the_north  && cell_to_the_north < total_cell_count && hall_scheme[cell_to_the_north] != 1 && got_here_by_direction[cell_to_the_north] == NOT_VISITED) {
        if (got_here_by_direction[current_cell] == WEST && remaining_right_turns_per_cell[current_cell] >= 1) {
            distances[cell_to_the_north] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_north] = remaining_right_turns_per_cell[current_cell] - 1;
            got_here_by_direction[cell_to_the_north] = NORTH;
            push(queue, cell_to_the_north);
        } else if (got_here_by_direction[current_cell] != WEST) {
            distances[cell_to_the_north] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_north] = remaining_right_turns_per_cell[current_cell];
            got_here_by_direction[cell_to_the_north] = NORTH;
            push(queue, cell_to_the_north);
        }
    }

    if (0 <= cell_to_the_south  && cell_to_the_south < total_cell_count && hall_scheme[cell_to_the_south] != 1 && got_here_by_direction[cell_to_the_south] == NOT_VISITED) {
        if (got_here_by_direction[current_cell] == EAST && remaining_right_turns_per_cell[current_cell] >= 1) {
            distances[cell_to_the_south] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_south] = remaining_right_turns_per_cell[current_cell] - 1;
            got_here_by_direction[cell_to_the_south] = SOUTH;
            push(queue, cell_to_the_south);
        } else if (got_here_by_direction[current_cell] != EAST) {
            distances[cell_to_the_south] = distances[current_cell] + 1;
            remaining_right_turns_per_cell[cell_to_the_south] = remaining_right_turns_per_cell[current_cell];
            got_here_by_direction[cell_to_the_south] = SOUTH;
            push(queue, cell_to_the_south);
        }
    }

    

}

void breadth_first_search(int *hall_scheme, int *distances, int *remaining_right_turns_per_cell, int *got_here_by_direction, queue *queue, int start_available_right_turns, int start_cell, int hall_width, int hall_length) {
    int current_cell, k;

    distances[start_cell] = 0;
    remaining_right_turns_per_cell[start_cell] = start_available_right_turns;

    push(queue, start_cell);

    while (is_not_empty(queue)) {
        current_cell = pop(queue);
    }



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
    queue *bfs_queue;
    
    int number_of_available_right_turns, hall_width, hall_length; 
    int *hall_scheme, *distances, *remaining_right_turns_per_cell, *got_here_by_direction;
    int start_cell, finish_cell;
    int i, j;

    scanf("%d %d %d", &number_of_available_right_turns, &hall_width, &hall_length);

    hall_scheme = (int*) calloc(hall_width*hall_length, sizeof(int));
    distances = (int*) calloc(hall_width*hall_length, sizeof(int));
    got_here_by_direction = (int*) calloc(hall_length*hall_width, sizeof(int));
    remaining_right_turns_per_cell = (int*) calloc(hall_length*hall_width, sizeof(int));
    
    bfs_queue = (queue*) calloc(1, sizeof(queue));
    bfs_queue->size = 0;
    bfs_queue->head = NULL;
    bfs_queue->tail = NULL;

    for (i=0; i<hall_width*hall_length; i++) {
        distances[i] = INFINITY;
        scanf("%d", hall_scheme + i);

        if (hall_scheme[i] == 2) {
            start_cell = i;
        } else if (hall_scheme[i] == 3) {
            finish_cell = i;
        }
    }

    breadth_first_search(hall_scheme, distances, remaining_right_turns_per_cell, got_here_by_direction, bfs_queue, number_of_available_right_turns, start_cell, hall_width, hall_length);

    if (distances[finish_cell] == INFINITY) {
        printf("-1");
    } else {
        printf("%d", distances[finish_cell]);
    }

    free(hall_scheme);
    free(distances);
    free(bfs_queue);
    free(remaining_right_turns_per_cell);

    




    return 0;
}
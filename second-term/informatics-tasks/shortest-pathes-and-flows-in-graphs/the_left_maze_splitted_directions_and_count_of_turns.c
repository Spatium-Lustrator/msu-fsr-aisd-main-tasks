#include <stdio.h>
#include <stdlib.h>


#define INFINITY 2147483647
#define WEST 0
#define EAST 1
#define NORTH 2
#define SOUTH 3

typedef struct distance_and_remaining_turns {
    int distance;
    int direction;
    int remaining_turns;
    int index;

} distance_and_remaining_turns;

typedef struct queue_element {
    distance_and_remaining_turns *cell_and_direction;
    struct queue_element *next;

} queue_element;

typedef struct queue {
    queue_element *head;
    queue_element *tail;
    int size;

} queue;

void push(queue *bfs_queue, distance_and_remaining_turns *cell) {
    queue_element *new_element = (queue_element*) malloc(sizeof(queue_element));

    new_element->next = NULL;
    new_element->cell_and_direction = cell;

    if (bfs_queue->size > 0) {
        bfs_queue->tail->next = new_element;
        bfs_queue->tail = new_element;
    } else {
        bfs_queue->head = bfs_queue->tail = new_element;
    }

    bfs_queue->size += 1;
}

distance_and_remaining_turns* pop(queue *bfs_queue) {
    distance_and_remaining_turns *result = NULL;
    queue_element *head;

    if (bfs_queue->size > 0) {
        head = bfs_queue->head;

        result = head->cell_and_direction;
        if (bfs_queue->size == 1) bfs_queue->tail = NULL;
        bfs_queue->head = head->next;
        bfs_queue->size -= 1;
        
        free(head);

    }

    return result;
}

int is_not_empty(queue *bfs_queue) {
    return (bfs_queue->size > 0);
}

void update_distance_info_and_push(queue *bfs_queue, distance_and_remaining_turns *cell_to_update, distance_and_remaining_turns *cell_from_update, int turn_consumed) {
    cell_to_update->distance = cell_from_update->distance + 1;
    cell_to_update->remaining_turns = cell_from_update->remaining_turns - turn_consumed;
    push(bfs_queue, cell_to_update);
}


void update_neighbors_info(int *hall_scheme, distance_and_remaining_turns ****distances, queue *bfs_queue, distance_and_remaining_turns *current_cell, int hall_width, int hall_length) {
    int cell_to_the_west_index, cell_to_the_east_index, cell_to_the_north_index, cell_to_the_south_index;
    int current_cell_index = current_cell->index;
    int total_cell_count = hall_length*hall_width;
    int got_from = current_cell->direction;


    if (current_cell_index % hall_length == 0) {
        cell_to_the_west_index = -1;
    } else {
        cell_to_the_west_index= current_cell_index-1;
    }


    if ((current_cell_index+1) % hall_length == 0) {
        cell_to_the_east_index = -1;
    } else {
        cell_to_the_east_index = current_cell_index+1;

    }

    cell_to_the_north_index = current_cell_index-hall_length;
    cell_to_the_south_index = current_cell_index+hall_length;

    if (got_from != EAST && 0 <= cell_to_the_west_index  && cell_to_the_west_index < total_cell_count && hall_scheme[cell_to_the_west_index] != 1) {
        if (current_cell->direction == SOUTH && current_cell->remaining_turns >= 1 && (distances[WEST][current_cell->remaining_turns - 1][cell_to_the_west_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[WEST][current_cell->remaining_turns-1][cell_to_the_west_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 1);
        } else if (current_cell->direction != SOUTH && (distances[WEST][current_cell->remaining_turns][cell_to_the_west_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[WEST][current_cell->remaining_turns][cell_to_the_west_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 0);
        }
    }

    if (got_from != WEST && 0 <= cell_to_the_east_index  && cell_to_the_east_index < total_cell_count && hall_scheme[cell_to_the_east_index] != 1) {
        if (current_cell->direction == NORTH && current_cell->remaining_turns >= 1 && (distances[EAST][current_cell->remaining_turns-1][cell_to_the_east_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[EAST][current_cell->remaining_turns-1][cell_to_the_east_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 1);
        } else if (current_cell->direction != NORTH && (distances[EAST][current_cell->remaining_turns][cell_to_the_east_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[EAST][current_cell->remaining_turns][cell_to_the_east_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 0);
        }
    }

    if (got_from != SOUTH && 0 <= cell_to_the_north_index  && cell_to_the_north_index < total_cell_count && hall_scheme[cell_to_the_north_index] != 1) {
        if (current_cell->direction == WEST && current_cell->remaining_turns >= 1 && (distances[NORTH][current_cell->remaining_turns-1][cell_to_the_north_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[NORTH][current_cell->remaining_turns-1][cell_to_the_north_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 1);
        } else if (current_cell->direction != WEST && (distances[NORTH][current_cell->remaining_turns][cell_to_the_north_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[NORTH][current_cell->remaining_turns][cell_to_the_north_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 0);
        }
    }

    if (got_from != NORTH && 0 <= cell_to_the_south_index  && cell_to_the_south_index < total_cell_count && hall_scheme[cell_to_the_south_index] != 1) {
        if (current_cell->direction == EAST && current_cell->remaining_turns >= 1  && (distances[SOUTH][current_cell->remaining_turns-1][cell_to_the_south_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[SOUTH][current_cell->remaining_turns-1][cell_to_the_south_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 1);
        } else if (current_cell->direction != EAST  && (distances[SOUTH][current_cell->remaining_turns][cell_to_the_south_index]->distance == INFINITY)) {
            update_distance_info_and_push(bfs_queue, distances[SOUTH][current_cell->remaining_turns][cell_to_the_south_index], distances[current_cell->direction][current_cell->remaining_turns][current_cell_index], 0);
        }
    }


}

void breadth_first_search(int *hall_scheme, distance_and_remaining_turns ****distances, queue *bfs_queue, int start_available_right_turns, int start_cell, int hall_width, int hall_length, int number_of_available_right_turns) {
    distance_and_remaining_turns *current_cell;

    push(bfs_queue, distances[WEST][number_of_available_right_turns][start_cell]);
    push(bfs_queue, distances[EAST][number_of_available_right_turns][start_cell]);
    push(bfs_queue, distances[NORTH][number_of_available_right_turns][start_cell]);
    push(bfs_queue, distances[SOUTH][number_of_available_right_turns][start_cell]);

    while (is_not_empty(bfs_queue)) {
        current_cell = pop(bfs_queue);

        update_neighbors_info(hall_scheme, distances, bfs_queue, current_cell, hall_width, hall_length);
    }



}

int main(void) {

    distance_and_remaining_turns ****distances;

    queue *bfs_queue;

    int min_dist_to_target = INFINITY;
    int *hall_scheme;
    int start_cell, finish_cell;
    int number_of_available_right_turns, hall_width, hall_length; 
    int i, j, k;

    scanf("%d %d %d", &number_of_available_right_turns, &hall_width, &hall_length);

    distances = (distance_and_remaining_turns****) calloc(4, sizeof(distance_and_remaining_turns***));
    hall_scheme = (int*) calloc(hall_width*hall_length, sizeof(int));

    bfs_queue = (queue*) calloc(1, sizeof(queue));
    bfs_queue->size = 0;
    bfs_queue->head = NULL;
    bfs_queue->tail = NULL;

    for (i=0; i<4; i++) {
        distances[i] = (distance_and_remaining_turns***) calloc(number_of_available_right_turns+1, sizeof(distance_and_remaining_turns**));
        for (k=0; k<number_of_available_right_turns+1; k++) {
            distances[i][k] = (distance_and_remaining_turns**) calloc(hall_length*hall_width, sizeof(distance_and_remaining_turns*));
            for (j=0; j<hall_length*hall_width; j++) {
                distances[i][k][j] = (distance_and_remaining_turns*) calloc(1, sizeof(distance_and_remaining_turns));
                distances[i][k][j]->distance = INFINITY;
                distances[i][k][j]->direction = i;
                distances[i][k][j]->remaining_turns = 0;
                distances[i][k][j]->index = j;
            }

        }
    }

    for (i=0; i<hall_width*hall_length; i++) {
        scanf("%d", hall_scheme + i);

        if (hall_scheme[i] == 2) {
            start_cell = i;
        } else if (hall_scheme[i] == 3) {
            finish_cell = i;
        }
    }

    for (i=0; i<4; i++) {
        distances[i][number_of_available_right_turns][start_cell]->distance = 0;
        distances[i][number_of_available_right_turns][start_cell]->remaining_turns = number_of_available_right_turns;
    }

    breadth_first_search(hall_scheme, distances, bfs_queue, number_of_available_right_turns, start_cell, hall_width, hall_length, number_of_available_right_turns);

    for (i=0; i<4; i++) {
        printf("%d:\n", i);
        for (k=0; k<number_of_available_right_turns+1; k++) {
            printf("%d turns: ", k);
            for (j=0; j<hall_length*hall_width; j++) {
                int d = distances[i][k][j]->distance;
                if (d==INFINITY) {
                    printf("inf ");
                } else {
                    printf("%d ", d);
                }
            }
            printf("\n");
        }
    }

    for (i=0; i<4; i++) {
        for (k=0; k<number_of_available_right_turns+1; k++) {
            if (min_dist_to_target > distances[i][k][finish_cell]->distance) {
                min_dist_to_target = distances[i][k][finish_cell]->distance;
            }

        }


    }

    if (min_dist_to_target == INFINITY) {
        printf("-1");
    } else {
        printf("%d", min_dist_to_target);
    }
    
    // free(distances);
    // free(bfs_queue);
    // free(hall_scheme);




    return 0;
}
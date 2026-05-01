#include <stdio.h>
#include <stdlib.h>

#define INFINITY 10000000

typedef struct road {

    int time_to_cross;
    int allowed_mugs;

} road;

typedef struct queue_element {
    int node_index;
    int time_to_the_node;
    int cur_allowed_count_of_mugs_on_the_path;
    struct queue_element *next;

} queue_element;

typedef struct queue {
    queue_element *head;
    queue_element *tail;
    int size;

} queue;

void push(queue *queue, int node_index, int time, int mugs) {
    queue_element *new_element = (queue_element*) malloc(sizeof(queue_element));

    new_element->next = NULL;
    new_element->node_index = node_index;
    new_element->cur_allowed_count_of_mugs_on_the_path = mugs;
    new_element->time_to_the_node = time;

    if (queue->size > 0) {
        queue->tail->next = new_element;
        queue->tail = new_element;
    } else {
        queue->head = queue->tail = new_element;
    }

    queue->size += 1;
}

queue_element* pop(queue *queue) {
    queue_element *head = NULL;

    if (queue->size > 0) {
        head = queue->head;

        if (queue->size == 1) queue->tail = NULL;
        queue->head = head->next;
        queue->size -= 1;
        
    }

    return head;
}

int is_not_empty(queue *queue) {
    return (queue->size > 0);
}

int min(int num1, int num2) {
    if (num1 > num2) {
        return num2;
    } else {
        return num1;
    }
}

int max(int num1, int num2) {
    if (num1 > num2) {
        return num1;
    } else {
        return num2;
    }
}

void find_times_and_counts_of_mugs(road ***road_scheme, road **best_routes, queue *tc_queue, int count_of_nodes) {
    queue_element *current_element;
    road *cur_road;
    int i, time_in_day=24*60;

    push(tc_queue, 0, 0, 10000000);

    while(is_not_empty(tc_queue)) {
        current_element = pop(tc_queue);
        for (i=0; i<count_of_nodes; i++) {
            cur_road = road_scheme[current_element->node_index][i];
            if (cur_road != NULL && (cur_road->time_to_cross + current_element->time_to_the_node <= time_in_day)
                                 && ((min(cur_road->allowed_mugs, current_element->cur_allowed_count_of_mugs_on_the_path) > best_routes[i]->allowed_mugs))) {
            
                best_routes[i]->allowed_mugs = min(cur_road->allowed_mugs, current_element->cur_allowed_count_of_mugs_on_the_path);
                best_routes[i]->time_to_cross = cur_road->time_to_cross + current_element->time_to_the_node;

                push(tc_queue, i, cur_road->time_to_cross + current_element->time_to_the_node, min(cur_road->allowed_mugs, current_element->cur_allowed_count_of_mugs_on_the_path));
            
            }
        }

    }


}


int main(void) {

    int weight_of_empty_truck = 3*1000000, weight_mug=100, max_mug_count=10000000;
    int current_from_node, current_to_node, current_time_cost, current_allowed_weight;
    int count_of_node_points, count_of_roads;
    int i, j, result;
    
    road ***road_scheme, **best_routes, *current_road;
    queue *tc_queue;

    scanf("%d %d", &count_of_node_points, &count_of_roads);

    road_scheme = (road***) malloc(sizeof(road**)*count_of_node_points);
    best_routes = (road**) calloc(count_of_node_points, sizeof(road*));
    tc_queue = (queue*) malloc(sizeof(queue));
    tc_queue->head = NULL;
    tc_queue->tail = NULL;
    tc_queue->size = 0;

    for (i=0; i<count_of_node_points; i++) {
        road_scheme[i] = (road**) calloc(count_of_node_points, sizeof(road*));
        best_routes[i] = (road*) malloc(sizeof(road));

        best_routes[i]->allowed_mugs=0;
        best_routes[i]->time_to_cross = INFINITY;
    }

    best_routes[0]->allowed_mugs = max_mug_count;
    best_routes[0]->time_to_cross = 0;

    for (i=0; i<count_of_roads; i++) {
        scanf("%d %d %d %d", &current_from_node, &current_to_node, &current_time_cost, &current_allowed_weight);

        current_road = (road*) malloc(sizeof(road));
        current_road->time_to_cross = current_time_cost;
        current_road->allowed_mugs = max((current_allowed_weight - weight_of_empty_truck) / weight_mug, 0);

        road_scheme[current_from_node-1][current_to_node-1] = current_road;
        road_scheme[current_to_node-1][current_from_node-1] = current_road;

    }

    find_times_and_counts_of_mugs(road_scheme, best_routes, tc_queue, count_of_node_points);

    result = best_routes[count_of_node_points-1]->allowed_mugs;

    if (result > max_mug_count) {
        result = max_mug_count;
    } else if (result<0) {
        result = 0;
    }

    printf("%d", result);

    for (i=0; i<count_of_node_points; i++) {
        for (j=0; j<count_of_node_points; j++) {
            if (road_scheme[i][j]) {
                free(road_scheme[i][j]);
                road_scheme[i][j] = NULL;
                road_scheme[j][i] = NULL;
            }
        }
        free(best_routes[i]);
        free(road_scheme[i]);
    }
    
    free(road_scheme);
    free(best_routes);
    free(tc_queue);


    

    return 0;
}
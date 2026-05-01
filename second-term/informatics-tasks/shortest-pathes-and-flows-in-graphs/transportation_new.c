#include <stdio.h>
#include <stdlib.h>

#define INFINITY 2147483647

typedef struct road {

    int time_to_cross;
    int allowed_mugs;

} road;


void merge(int *arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr, *rightArr;

    leftArr = calloc(n1, sizeof(int));
    rightArr = calloc(n2, sizeof(int));

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
        
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int *arr, int left, int right) {
    if (left < right) {
      
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void update_neighbors_costs(road ***adjacency_matrix, int *distances, int current_vertex, int count_of_vertexes, int current_mugs_count_on_check) {
    int current_cost = distances[current_vertex], new_cost, l;

    for (l=0; l<count_of_vertexes; l++) {
        if (adjacency_matrix[current_vertex][l] != NULL) {
            new_cost = current_cost + adjacency_matrix[current_vertex][l]->time_to_cross;
            if (new_cost < distances[l] && adjacency_matrix[current_vertex][l]->allowed_mugs >= current_mugs_count_on_check) {
                distances[l] = new_cost;
            }

        }
    }
}

int find_node_with_lowest_cost(int *processed, int *distances, int count_of_vertexes) {
    int current_min_distance = INFINITY, result = -1, i;

    for (i=0; i<count_of_vertexes; i++) {
        if (current_min_distance > distances[i] && !processed[i]) {
            result = i;
            current_min_distance = distances[i];
        }
    }

    return result;
}

int find_shortest_path_between_vertexes(road ***adjacency_matrix, int *processed, int *distances, int count_of_vertexes, int start_index, int end_index, int current_mugs_count_on_check) {
    int current_vertex=start_index, i;

    for (i=0; i<count_of_vertexes; i++) {
        processed[i] = 0;
        distances[i] = INFINITY;
    }

    distances[0] = 0;
    

    while (current_vertex >= 0) {
        update_neighbors_costs(adjacency_matrix, distances, current_vertex, count_of_vertexes, current_mugs_count_on_check);
        processed[current_vertex] = 1;
        current_vertex = find_node_with_lowest_cost(processed, distances, count_of_vertexes);

    }
    
    if (distances[end_index] == INFINITY) return -1;
    return distances[end_index];

}


int main(void) {

    int weight_of_empty_truck = 3*1000000, weight_mug=100, time_in_day=24*60;
    int current_from_node, current_to_node, current_time_cost, current_allowed_weight;
    int count_of_node_points, count_of_roads;
    int max_mug_count = 0, search_result;
    int *possible_mug_count, *processed, *distances;
    int i, j;
    int left_range, right_range, middle_point;

    road ***road_scheme, *current_road;

    scanf("%d %d", &count_of_node_points, &count_of_roads);

    road_scheme = (road***) malloc(sizeof(road**)*count_of_node_points);
    possible_mug_count = (int*) malloc(sizeof(int)*count_of_roads);
    processed = (int*) calloc(count_of_node_points, sizeof(int));
    distances = (int*) calloc(count_of_node_points, sizeof(int));

    for (i=0; i<count_of_node_points; i++) {
        road_scheme[i] = (road**) calloc(count_of_node_points, sizeof(road*));
    }


    for (i=0; i<count_of_roads; i++) {
        scanf("%d %d %d %d", &current_from_node, &current_to_node, &current_time_cost, &current_allowed_weight);

        current_road = (road*) malloc(sizeof(road));
        current_road->time_to_cross = current_time_cost;
        current_road->allowed_mugs = (current_allowed_weight - weight_of_empty_truck) / weight_mug;

        road_scheme[current_from_node-1][current_to_node-1] = current_road;
        road_scheme[current_to_node-1][current_from_node-1] = current_road;
        possible_mug_count[i] = current_road->allowed_mugs;

    }

    mergeSort(possible_mug_count, 0, count_of_roads-1);    

    left_range = 0;
    right_range = count_of_roads-1;

    while (left_range <= right_range) {
        middle_point = (left_range + right_range)/2;

        search_result = find_shortest_path_between_vertexes(road_scheme, processed, distances, count_of_node_points, 0, count_of_node_points-1, possible_mug_count[middle_point]);
        if (search_result != -1) {
            max_mug_count = possible_mug_count[middle_point];
            left_range = middle_point + 1;
        } else {
            right_range = middle_point - 1;
        }
    }

    printf("%d", max_mug_count);

    for (i=0; i<count_of_node_points; i++) {
        for (j=0; j<count_of_node_points; j++) {
            if (road_scheme[i][j]){
                 free(road_scheme[i][j]);
                 road_scheme[i][j] = road_scheme[j][i] = NULL;
            }
        }
        free(road_scheme[i]);
    }
    free(processed);
    free(road_scheme);
    free(distances);


    return 0;
}
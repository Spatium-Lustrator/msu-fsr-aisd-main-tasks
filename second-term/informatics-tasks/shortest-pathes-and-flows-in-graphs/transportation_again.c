#include <stdio.h>
#include <stdlib.h>

#define INFINITY 100000000

typedef struct road {

    int allowed_weight;
    int time_to_cross;

} road;

void update_neighbors_costs(road ***adjacency_matrix, int *distances, int current_vertex, int count_of_vertexes, int min_weight) {
    int current_cost = distances[current_vertex], new_cost, l;

    for (l=0; l<count_of_vertexes; l++) {
        if (adjacency_matrix[current_vertex][l] != NULL) {
            new_cost = current_cost + adjacency_matrix[current_vertex][l]->time_to_cross;
            if (new_cost < distances[l] && adjacency_matrix[current_vertex][l]->allowed_weight >= min_weight) distances[l] = new_cost;
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

int find_shortest_path_between_vertexes(road ***adjacency_matrix, int *processed, int *distances, int count_of_vertexes, int start_index, int end_index, int min_weight) {
    int current_vertex=start_index;

    while (current_vertex >= 0) {
        update_neighbors_costs(adjacency_matrix, distances, current_vertex, count_of_vertexes, min_weight);
        processed[current_vertex] = 1;
        current_vertex = find_node_with_lowest_cost(processed, distances, count_of_vertexes);

    }
    
    return distances[end_index];

}

int current_mug_count_allowed(road ***road_scheme, int *processed, int *distances, int current_mug_count, int count_of_nodes) {
    int truck_weight = 3000000 + 100*current_mug_count, i;

    for (i=0; i<count_of_nodes; i++) {
        processed[i] = 0;
        distances[i] = INFINITY;
    }

    distances[0] = 0;

    return find_shortest_path_between_vertexes(road_scheme, processed, distances, count_of_nodes, 0, count_of_nodes-1, truck_weight) <= 24*60;

}

int main(void) {

    road ***road_scheme, *current_road;

    int *processed, *distances;
    int current_from, current_to, current_allowed_weight, current_time_to_cross;
    int count_of_nodes, count_of_roads;
    int min_count_of_mugs=0, max_count_of_mugs=10000000, middle_count_of_mugs, final_count_of_allowed_mugs=0;
    int i, j;

    scanf("%d %d", &count_of_nodes, &count_of_roads);

    road_scheme = (road***) calloc(count_of_nodes, sizeof(road**));
    processed = (int*) calloc(count_of_nodes, sizeof(int));
    distances = (int*) calloc(count_of_nodes, sizeof(int));

    for (i=0; i<count_of_nodes; i++) {
        road_scheme[i] = (road**) calloc(count_of_nodes, sizeof(road*));
    }

    for (i=0; i<count_of_roads; i++) {
        scanf("%d %d %d %d", &current_from, &current_to, &current_time_to_cross, &current_allowed_weight);

        current_road = (road*) calloc(1, sizeof(road));
        current_road->allowed_weight = current_allowed_weight;
        current_road->time_to_cross = current_time_to_cross;

        road_scheme[current_from-1][current_to-1] = current_road;
        road_scheme[current_to-1][current_from-1] = current_road;

    }

    while (min_count_of_mugs <= max_count_of_mugs) {
        middle_count_of_mugs = (min_count_of_mugs + max_count_of_mugs) / 2;

        if (current_mug_count_allowed(road_scheme, processed, distances, middle_count_of_mugs, count_of_nodes)) {
            final_count_of_allowed_mugs = middle_count_of_mugs;
            min_count_of_mugs = middle_count_of_mugs + 1;
        } else {
            max_count_of_mugs = middle_count_of_mugs - 1;
        }
    }

    printf("%d", final_count_of_allowed_mugs);

    for (i=0; i<count_of_nodes; i++) {
        for (j=0; j<count_of_nodes; j++) {
            if (road_scheme[i][j]){
                 free(road_scheme[i][j]);
                 road_scheme[i][j] = road_scheme[j][i] = NULL;
            }
        }
        free(road_scheme[i]);
    }

    free(road_scheme);
    free(processed);
    free(distances);



    return 0;
}
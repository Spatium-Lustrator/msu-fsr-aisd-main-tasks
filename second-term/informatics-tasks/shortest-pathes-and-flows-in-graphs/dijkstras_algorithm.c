#include <stdio.h>
#include <stdlib.h>

#define INFINITY 2147483647

void update_neighbors_costs(int **adjacency_matrix, int *distances, int current_vertex, int count_of_vertexes) {
    int current_cost = distances[current_vertex], new_cost, l;

    for (l=0; l<count_of_vertexes; l++) {
        new_cost = current_cost + adjacency_matrix[current_vertex][l];
        if (adjacency_matrix[current_vertex][l] > 0 && new_cost < distances[l]) {
            distances[l] = new_cost;
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

int find_shortest_path_between_vertexes(int **adjacency_matrix, int *processed, int *distances, int count_of_vertexes,int start_index, int end_index) {
    int current_vertex=start_index;

    while (current_vertex >= 0) {
        update_neighbors_costs(adjacency_matrix, distances, current_vertex, count_of_vertexes);
        processed[current_vertex] = 1;
        current_vertex = find_node_with_lowest_cost(processed, distances, count_of_vertexes);

    }
    
    if (distances[end_index] == INFINITY) return -1;
    return distances[end_index];

}

int main(void) {
    int count_of_vertexes, start_index, end_index;
    int **adjacency_matrix, *processed, *distances;
    int i, j;


    scanf("%d %d %d", &count_of_vertexes, &start_index, &end_index);

    adjacency_matrix = (int**) malloc(sizeof(int*)*count_of_vertexes);
    processed = (int*) calloc(count_of_vertexes, sizeof(int));
    distances = (int*) malloc(count_of_vertexes*sizeof(int));

    for(i=0; i<count_of_vertexes; i++) {
        adjacency_matrix[i] = (int*) malloc(sizeof(int)*count_of_vertexes);
        distances[i] = INFINITY;
        for (j=0; j<count_of_vertexes; j++) {
            scanf("%d", adjacency_matrix[i] + j);
        }
    }

    distances[start_index-1] = 0;

    printf("%d", find_shortest_path_between_vertexes(adjacency_matrix, processed, distances, count_of_vertexes, start_index-1, end_index-1));

    for(i=0; i<count_of_vertexes; i++) {
        free(adjacency_matrix[i]);
    }

    free(adjacency_matrix);
    free(processed);
    free(distances);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void update_neighbors_costs(double **adjacency_matrix, double *distances, int current_vertex, int count_of_vertexes) {
    int l;
    double current_cost = distances[current_vertex], new_cost;

    for (l=0; l<count_of_vertexes; l++) {
        new_cost = current_cost + adjacency_matrix[current_vertex][l];

        if (!(adjacency_matrix[current_vertex][l]+1.0<0.0000000000000000000000000000001) && new_cost < distances[l]) {
            distances[l] = new_cost;
        }
    }

}

int find_node_with_lowest_cost(double *distances, int *processed, int count_of_vertexes) {
    int result=-1, i;
    double current_min_distance = INFINITY;

    for (i=0; i<count_of_vertexes; i++) {
        if (current_min_distance > distances[i] && !processed[i]) {
            result = i;
            current_min_distance = distances[i];
        }
    }

    return result;
}

int find_vertex_with_shortest_path_weight(double **adjacency_matrix, int from_vertex, int count_of_vertexes, int count_of_vertexes_on_slice) {
    int *processed, current_vertex=from_vertex, k;
    double *distances, result; 
    double current_min_distance = INFINITY;


    processed = (int*) calloc(count_of_vertexes, sizeof(int));
    distances = (double*) malloc(sizeof(double)*count_of_vertexes);

    for (k=0; k<count_of_vertexes; k++) distances[k] = INFINITY;
    distances[from_vertex] = 0;

    while (current_vertex >= 0) {
        update_neighbors_costs(adjacency_matrix, distances, current_vertex, count_of_vertexes);
        processed[current_vertex] = 1;
        current_vertex = find_node_with_lowest_cost(distances, processed, count_of_vertexes);
    }
    

    for (k=1; k<count_of_vertexes_on_slice; k++) {
        if (current_min_distance > distances[k]) {
            result = k;
            current_min_distance = distances[k];
        }
    }

    free(processed);
    free(distances);

    return result;

}

int main(void) {
    int i, j;
    int count_of_vertexes, count_of_vertexes_on_slice, vertex_from_first_anthill, vertex_from_second_anthill;
    double **anthill1,  **anthill2;

    scanf("%d %d", &count_of_vertexes, &count_of_vertexes_on_slice);

    anthill1 = (double**) malloc(sizeof(double*)*count_of_vertexes);
    anthill2 = (double**) malloc(sizeof(double*)*count_of_vertexes);

    for (i=0; i<count_of_vertexes; i++) {
        anthill1[i] = (double*) malloc(sizeof(double)*count_of_vertexes);
        for (j=0; j<count_of_vertexes; j++)  {
            scanf("%lf", &anthill1[i][j]);
        }
    }

    for (i=0; i<count_of_vertexes; i++) {
        anthill2[i] = (double*) malloc(sizeof(double)*count_of_vertexes);
        for (j=0; j<count_of_vertexes; j++)  {
            scanf("%lf", &anthill2[i][j]);
        }
    }

    vertex_from_first_anthill = find_vertex_with_shortest_path_weight(anthill1, 0, count_of_vertexes, count_of_vertexes_on_slice);
    vertex_from_second_anthill = find_vertex_with_shortest_path_weight(anthill2, 0, count_of_vertexes, count_of_vertexes_on_slice);

    printf("%d %d", vertex_from_first_anthill, vertex_from_second_anthill);

    for (i=0; i<count_of_vertexes; i++) {
        free(anthill1[i]);
        free(anthill2[i]);
    }
    free(anthill1);
    free(anthill2);



    return 0;


}
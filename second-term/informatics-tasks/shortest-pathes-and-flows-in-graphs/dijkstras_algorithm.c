#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// only three correct tests?.....

#define INACCURACY 0.0000000000000000000001

void update_neighbors_costs(double **adjacency_matrix, double *distances, int current_vertex, int count_of_vertexes) {
    int l;
    double current_cost = distances[current_vertex], new_cost;

    for (l=0; l<count_of_vertexes; l++) {
        new_cost = current_cost + adjacency_matrix[current_vertex][l];

        if (!(adjacency_matrix[current_vertex][l]< INACCURACY) && new_cost < distances[l]) {
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

double find_shortest_path_weight(double **adjacency_matrix, int from_vertex, int to_vertex, int count_of_vertexes) {
    int *processed, current_vertex=from_vertex, k;
    double *distances, result; 

    processed = (int*) calloc(count_of_vertexes, sizeof(int));
    distances = (double*) malloc(sizeof(double)*count_of_vertexes);

    for (k=0; k<count_of_vertexes; k++) distances[k] = INFINITY;
    distances[from_vertex] = 0;

    while (current_vertex >= 0) {
        update_neighbors_costs(adjacency_matrix, distances, current_vertex, count_of_vertexes);
        processed[current_vertex] = 1;
        current_vertex = find_node_with_lowest_cost(distances, processed, count_of_vertexes);
    }
      
    result = distances[to_vertex];

    free(processed);
    free(distances);

    return result;

}

int main(void) {
    int i, j;
    int count_of_vertexes, from_vertex, to_vertex;
    double** adjacency_matrix; 

    scanf("%d %d %d", &count_of_vertexes, &from_vertex, &to_vertex);
    adjacency_matrix = (double**) malloc(sizeof(double*)*count_of_vertexes);

    for (i=0; i<count_of_vertexes; i++) {
        adjacency_matrix[i] = (double*) malloc(sizeof(double)*count_of_vertexes);
        for (j=0; j<count_of_vertexes; j++)  {
            scanf("%lf", &adjacency_matrix[i][j]);
        }
    }

    printf("%.0lf", find_shortest_path_weight(adjacency_matrix, from_vertex, to_vertex, count_of_vertexes));

    for (i=0; i<count_of_vertexes; i++) free(adjacency_matrix[i]);
    free(adjacency_matrix);



    return 0;


}
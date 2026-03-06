#include <stdio.h>
#include <stdlib.h>


int main(void) {

    int n,m,i,j;
    int from_vertex, to_vertex, weight, mst_weight=0, cur_min_weight, next_vertex_to_process, cur_vertex=0;
    int **adjacency_matrix, *visited, *distances;

    scanf("%d %d", &n, &m);

    visited = (int*) calloc(n, sizeof(int));
    distances = (int*) calloc(n, sizeof(int));
    adjacency_matrix = (int**) calloc(n, sizeof(int*));
    for (i=0; i<n; i++) adjacency_matrix[i] = (int*) calloc(n, sizeof(int));
    for (i=1; i<n; i++) distances[i] = 30001;

    for (i=0; i<m; i++) {
        scanf("%d %d %d", &from_vertex, &to_vertex, &weight);
        adjacency_matrix[from_vertex-1][to_vertex-1] = weight;
        adjacency_matrix[to_vertex-1][from_vertex-1] = weight;
    }

    for (i=0; i<n-1; i++) {
        cur_min_weight = 30001;
        visited[cur_vertex] = 1;

        for (j=0; j<n; j++) {
            if (cur_vertex != j && adjacency_matrix[cur_vertex][j] < distances[j] && adjacency_matrix[cur_vertex][j] != 0 && !visited[j] ) {
                distances[j] = adjacency_matrix[cur_vertex][j];
            }


        }

        for (j=0; j<n; j++) {
            if (distances[j] < cur_min_weight && visited[j] != 1) {
                cur_min_weight = distances[j];
                next_vertex_to_process = j;
            }
        }

        cur_vertex = next_vertex_to_process;

    }
    for (i=1; i<n; i++) {
        mst_weight += distances[i];
    }
    
    printf("%d", mst_weight);



    for (i=0; i<n; i++) free(adjacency_matrix[i]);
    free(adjacency_matrix);
    free(visited);
    free(distances);



    return 0;
}
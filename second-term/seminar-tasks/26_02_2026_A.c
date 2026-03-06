#include <stdio.h>
#include <stdlib.h>

#define infinity 2147483647

int main(void) {

    int tmp;
    int n, k, m;
    int i, j, v;
    int min_dist_i, min_dist_j, min_dist=infinity;
    int start_vertex;
    int **graph, **distances, **previous;
    scanf("%d %d %d", &n, &k, &m);

    graph = (int**) malloc(sizeof(int*)*n);
    distances = (int**) malloc(sizeof(int*)*n);
    previous = (int**) malloc(sizeof(int*)*n);

    for (i=0; i<n; i++) {
        graph[i] = (int*) malloc(sizeof(int)*n);
        distances[i] = (int*) malloc(sizeof(int)*n);
        previous[i] = (int*) malloc(sizeof(int)*n);
        for (j=0; j<n; j++) {
            scanf("%d", graph[i]+j);
            distances[i][j] = graph[i][j];
            if (i == j) {
                previous[i][j] = -1;
            } else {
                previous[i][j] = i;
            }
        }
    }


    for (v=0; v<n; v++) {
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                if (distances[i][j] > (tmp = distances[i][v] + distances[v][j])) {
                    distances[i][j] = tmp;
                    previous[i][j] = previous[v][j];
                }
            }
        }
    }

    for (i=0; i<k; i++) {
        for (j=m; j<n; j++) {
            if (distances[i][j] < min_dist) {
                min_dist = distances[i][j];
                min_dist_i = i;
                min_dist_j = j;
            }
        }
    }

    start_vertex = min_dist_i;
    
    while (previous[start_vertex][min_dist_j] != -1 && start_vertex != previous[start_vertex][min_dist_j]) {
        start_vertex = previous[start_vertex][min_dist_j];
    }

    printf("%d %d", start_vertex, min_dist_j);

    for (i=0; i<n; i++) {
        free(graph[i]);
        free(previous[i]);
        free(distances[i]);
    }

    free(graph);
    free(previous);
    free(distances);



    return 0;
}
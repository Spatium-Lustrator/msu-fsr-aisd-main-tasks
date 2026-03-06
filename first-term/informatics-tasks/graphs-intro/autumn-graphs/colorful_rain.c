#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i, j;
    int **matrix, *colors, count_v, count_of_bad_bridges=0;

    scanf("%d", &count_v);

    colors = (int*) malloc(sizeof(int)*count_v);
    matrix = (int**) malloc(sizeof(int*)*count_v);

    for (i=0; i<count_v; i++) {
        matrix[i] = (int*) malloc(sizeof(int)*count_v);
    }

    for (i=0; i<count_v; i++) {
        for (j=0; j<count_v; j++) {
            scanf("%d", matrix[i]+j);
        }
    }

    for (i=0; i<count_v; i++) {
        scanf("%d", &colors[i]);
    }

    for (i=0; i<count_v; i++) {
        for (j=0; j<count_v; j++) {
            count_of_bad_bridges += matrix[i][j] && (colors[i] != colors[j]);
        }
    }


    printf("%d", count_of_bad_bridges/2);

    for (i=0; i<count_v; i++) {
        free(matrix[i]);
    }

    free(matrix);
    free(colors);

    return 0;
}
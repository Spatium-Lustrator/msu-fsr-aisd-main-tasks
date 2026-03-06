#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i, j;
    int **matrix, count_v, count_e, flag=0, correct_count_e=0;
    int v1,v2;

    scanf("%d %d", &count_v, &count_e);

    matrix = (int**) malloc(sizeof(int*)*count_v);

    for (i=0; i<count_v; i++) {
        matrix[i] = (int*) malloc(sizeof(int)*count_v);
        for (j=0; j<count_v; j++) {
            matrix[i][j] = 0;
        }
    }

    
    for (i=0; i<count_e && !flag; i++) {
        scanf("%d%d", &v1, &v2);
        matrix[v1-1][v2-1] += 1;
        matrix[v2-1][v1-1] += 1;
        
        flag |= (matrix[v1-1][v2-1] > 1);
    }

    for (j=1; j<count_v; j++) correct_count_e += j;

    if (!flag && correct_count_e == count_e) {
        printf("YES");
    } else {
        printf("NO");
    }

    for (i=0; i<count_v; i++) {
        free(matrix[i]);
    }

    free(matrix);

    return 0;
}
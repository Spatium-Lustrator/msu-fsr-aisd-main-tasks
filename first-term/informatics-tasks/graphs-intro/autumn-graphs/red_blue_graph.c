#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {

    int n, i, j, target;
    char color, **matrix;
    bool flag=true;

    unsigned long long **red_matrix, **blue_matrix;


    scanf("%d", &n);
    scanf("%c", &color);

    red_matrix = malloc(sizeof(unsigned long long*)*n);
    blue_matrix = malloc(sizeof(unsigned long long*)*n);
    matrix = malloc(sizeof(char*)*n);

    for (i=0; i<n; i++) {
        red_matrix[i] = malloc(sizeof(unsigned long long)*80);
        blue_matrix[i] = malloc(sizeof(unsigned long long)*80);
        matrix[i] = malloc(sizeof(char)*n);
        for (j=0; j<n; j++) {
            matrix[i][j] = 'N';
        }
    }

    for (i=0; i<n-1 && flag; i++) {
        for (j=0; j<n-i-1 && flag; j++) {
            scanf("%c", &color);
            target=i+j+1;
            matrix[i][target] = color;

        }
        scanf("%c", &color);
    }

    for (i=n-2; i>=0; i--) {
        for (j=i+1; j<n; j++) {
            if (matrix[i][j] == 'R') {
                red_matrix[i][j/64] |= (1ULL << (j%64));
                red_matrix[i][j/64] |= red_matrix[j][j/64];
            } else if (matrix[i][j] == 'B') {
                blue_matrix[i][j/64] |= (1ULL << (j%64));
                blue_matrix[i][j/64] |= blue_matrix[j][j/64];
            }
        }
    }

    for (i=0; i<n && flag; i++) {
        for (j=i+1; j<n && flag; j++) {
            if ((red_matrix[i][j/64] & (1ULL << (j%64))) && (blue_matrix[i][j/64] & (1ULL << (j%64)))) {
                flag = false;
            }
            
        }
    }

    if (flag) {
        printf("YES");
    } else {
        printf("NO");
    }

    for (i=0; i<n; i++) {
        free(red_matrix[i]);
        free(blue_matrix[i]);
        free(matrix[i]);
    }

    free(red_matrix);
    free(blue_matrix);
    free(matrix);


    return 0;

}
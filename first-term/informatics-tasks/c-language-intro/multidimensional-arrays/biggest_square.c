#include <stdio.h>

int min(int x1, int x2, int x3) {
    int minim = x1;

    if (x2<minim) {minim = x2;}

    if (x3<minim) {minim = x3;}

    return minim;
}

int main() {

    int n=0, m=0, side=0, i=0, j=0, result_x=0, result_y=0;
    int matrix[1000][1000];
    scanf("%d%d", &n, &m);

    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            // printf("%d %d\n", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    for (i=1; i<n; i++) {
        for (j=1; j<m; j++) {
            if (matrix[i][j] == 1) {
                matrix[i][j] = min(matrix[i][j-1], matrix[i-1][j], matrix[i-1][j-1]) + 1;
            }

            if (matrix[i][j]>side) {
                side = matrix[i][j];
                result_x = i;
                result_y = j;
            }

        }
    }

    if (n*m == 1) {
        printf("%d \n%d %d", 1, 1, 1);
    } else {
        printf("%d \n%d %d", side, result_x+1-side+1, result_y+1-side+1);

    }



    return 0;
}
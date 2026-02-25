#include <stdio.h>


int check_cords(int x, int y, int n, int m) {
    if ((0<=x && x<=n) && (0<=y && y<=m)) {
        return 1;
    } else {
        return 0;
    }
}

void increase_in_ring(int map[10][10], int x, int y, int n, int m) {


    for (int i=-1; i<2; i++) {
        for (int j=-1; j<2; j++) {
            if (check_cords(x+i, y+j, n, m) && map[x+i][y+j]!=-1) {
                map[x+i][y+j]++;
            }

        }
    }
    
}



int main() {

    int n=0, m=0, k=0, i=0, j=0, cx=0, cy=0;
    int map[10][10] = {0};

    

    scanf("%d%d%d", &n, &m, &k);

    for (i; i<k; i++) {
        scanf("%d%d", &cx, &cy);
        map[cx-1][cy-1] = -1;
        increase_in_ring(map, cx-1, cy-1, n, m);
    }

    for (i=0; i<n; i++) {
        for (j=0; j<m; j++) {
            if (map[i][j] == -1) {
                printf("* ");
            } else if(map[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", map[i][j]);
            }
        }
        printf("\n");
    }


    return 0;
}
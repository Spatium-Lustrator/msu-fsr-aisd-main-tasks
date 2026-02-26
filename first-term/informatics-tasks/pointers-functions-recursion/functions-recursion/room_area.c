#include <stdio.h>

int recursion(int x, int y, char arr[][10]) {
    if (arr[x][y] == '.') {
        arr[x][y] = '*';
        return 1 + recursion(x-1, y, arr) + recursion(x+1, y, arr) + recursion(x, y-1, arr) + recursion(x, y+1, arr);
    }

    return 0;
}

int main(void) {

    char arr[10][10] = {{'*'}}, temp='0';
    int r = 0, n=0, x0=0, y0=0, i=0, j=0;
    scanf("%d", &n);

    for (i = 0; i<n; i++) {
        for (j = 0; j<n; j++) {
            arr[i][j] = '*';
        }
    }
    scanf("%c", &temp);
    
    for (i = 0; i<n; i++) {
        for (j = 0; j<n; j++) {
            scanf("%c", &arr[i][j]);
        }
        scanf("%c", &temp); 
    }

    scanf("%d", &x0);
    scanf("%d", &y0);
    r = recursion(x0-1, y0-1, arr);

    printf("%d", r);



    return 0;
}
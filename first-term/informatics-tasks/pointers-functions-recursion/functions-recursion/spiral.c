#include <stdio.h>


int singular_spiral(int top_range, int right_range, int bottom_range, int left_range, int array[][51]) {
    if (bottom_range >= top_range || left_range >= right_range) {return 0;}
    
    int i = 0;

    for (i = left_range; i < right_range; ++i){
            if (array[bottom_range][i+1]!=0) {
                right_range--;
            } else {
                array[bottom_range][i] = 1;

            }
        }
        bottom_range++;

        for (i = bottom_range; i < top_range; ++i){
            if (array[i+1][right_range-1]) {
                top_range--;
            } else {
                array[i][right_range-1] = 1;    
            }
        }
        right_range--;

        if (bottom_range < top_range)
        {
            for (i = right_range-1; i >= left_range; --i){
                if (array[top_range-1][i-1]!=0) {
                    left_range++;
                } else {
                    array[top_range-1][i] = 1;

                }
            }
            top_range--;
        }

        if (left_range < right_range)
        {
            for (i = top_range-1; i >= bottom_range; --i){
                if(array[i-1][left_range]!=0){
                    bottom_range++;
                } else {
                    array[i][left_range] = 1;
                }
            }
            left_range++;
        }
    
    return singular_spiral(top_range, right_range, bottom_range, left_range, array);
}

void print_arr(int array[][51], int m, int n) {
    int i=0, j=0;
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            printf("%d",array[i][j]);
        }
        printf("\n");
    }
}

void fill_arr_with_zeros(int array[][51]) {
    int i=0, j=0;
    for (i=0; i<51; i++) {
        for (j=0; j<51; j++) {
            array[i][j] = 0;
        }
    }
}

int main(void) {
    int m = 7, n = 7;
    int array[51][51];

    scanf("%d", &n);
    m=n;

    fill_arr_with_zeros(array);
    singular_spiral(m, n, 0, 0, array);
    print_arr(array, m, n);
    
    return 0;
}
#include <stdio.h>

void recursion(int sum, int prefix[], int last_index) {
    int i = 1, j=0;

    if (!sum) {
        for (j=0; j<=last_index; j++) {
            printf("%d ", prefix[j]);
        }
        printf("\n");
    } else {
        for (i = 1; i<sum+1; i++) {
            if (last_index==-1 || prefix[last_index] >= i) {
                prefix[last_index + 1] = i;
                recursion(sum-i, prefix, last_index+1);
            }
        }
    }

}


int main(void) {

    int arr[60] = {0}, num=0;
    scanf("%d", &num);
    recursion(num, arr, -1);



    return 0;
}
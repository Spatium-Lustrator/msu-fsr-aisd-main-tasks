#include <stdio.h>

int main(void) {

    int arr[100] = {0};
    int n=0, count=0;

    int *n_p = &n, *count_p = &count, *i_p, *j_p;

    scanf("%d", n_p);

    for (i_p=arr; i_p<(arr + *n_p); i_p += 1) { 
        scanf("%d", i_p);
    }
    
    for (j_p=arr+1; j_p<arr+*n_p-1; j_p += 1) {
        if (*(j_p) > *(j_p - 1) && *(j_p) > *(j_p + 1)) {
            *count_p += 1;
        }
    }

    printf("%d", *count_p);
    return 0;
}
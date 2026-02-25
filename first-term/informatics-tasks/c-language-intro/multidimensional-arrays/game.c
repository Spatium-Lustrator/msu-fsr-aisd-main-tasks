#include <stdio.h>

int main() {
    int n, i=0, main_sum=0, add_sum=0;
    int arr[400];
    scanf("%d", &n);
    for (i; i<n*n; i++) scanf("%d", &arr[i]);

    for (i=0; i<n; i++) {
        main_sum += arr[i*n + i];
        add_sum += arr[i*n + (n-1-i)];
    }

    if (main_sum == add_sum) {
        printf("0");
    } else if (main_sum > add_sum) {
        printf("1");
    } else {
        printf("2");
    }




    return 0;
}
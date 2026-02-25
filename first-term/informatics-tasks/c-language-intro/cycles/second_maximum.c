#include <stdio.h>

int main() {

    int first_max=0, second_max=0;
    int n;

    scanf("%d", &n);

    while (n!=0) {
        if (n>first_max) {
            second_max = first_max;
            first_max = n;
        } else if (n>second_max && n<first_max) {
            second_max = n;
        }

        scanf("%d", &n);
    }

    printf("%d", second_max);





    return 0;
}
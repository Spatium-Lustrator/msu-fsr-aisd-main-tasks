#include <stdio.h>

int recursion(int value) {
    int tmp=0;

    if (!value) {
        printf("0\n");
        return 0;
    }

    scanf("%d", &tmp);
    recursion(tmp);
    printf("%d\n", value);
    return 0;



}

int main(void) {


    int t=0;
    scanf("%d", &t);
    recursion(t);



    return 0;
}
#include <stdio.h>

int product_nums(int num) {
    int r = 1;

    while (num>0) {
        r *= num%10;
        num /= 10;
    }

    return r;
}

int main() {
    
    for (int i=11; i<100; i++) {

        if (2*product_nums(i) == i) {
            printf("%d ", i);
        }
    }
    return 0;
}
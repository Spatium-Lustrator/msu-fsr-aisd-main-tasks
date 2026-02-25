#include <stdio.h>

int main() {

    int sum=0, prev_is_two=0, n=0, counted_marks=0;

    for (int i=0; i<10; i++) {
        scanf("%d", &n);
        sum += n;
        counted_marks++;
        if (prev_is_two && n!=2) { 
            sum -= 2;
            counted_marks -= 1;
         }
        prev_is_two = 0;
        if (n==2) { prev_is_two = 1; }

    }

    printf("%d", sum/counted_marks);


    return 0;
}
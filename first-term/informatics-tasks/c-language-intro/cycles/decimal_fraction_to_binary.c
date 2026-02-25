#include <stdio.h>

int main() {

    double n;
    int integer_part, accuracy = 0, curr_int_part;
    double float_part;

    int index = 129; 
    int int_part_yo[130];

    scanf("%lf", &n);
    integer_part = n;
    float_part = n - integer_part;

    do {
        int_part_yo[index] = integer_part%2;
        index--;
        integer_part/=2;
    } while (integer_part>0);

    index++;

    for (index; index<130; index++) {
        printf("%d", int_part_yo[index]);
    }


    printf(".");

    do {
        float_part *= 2;
        curr_int_part = float_part;
        float_part -= curr_int_part;

        printf("%d", curr_int_part);
        accuracy+=1;

    } while (accuracy <= 32 && float_part > 0.0);



    return 0;
}
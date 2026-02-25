#include <stdio.h>

char swap_case(char symb) {
    int lower_a = 'a';
    int lower_z = 'z';
    int upper_a = 'A';
    int upper_z = 'Z';
    char result;

    if ((lower_a <= symb) && (lower_z >= symb)) {
        result = upper_a+(symb-lower_a);
    } else if ((upper_a <= symb) && (upper_z >= symb)) {
        result = lower_a+(symb-upper_a);
    } else {
        result = symb;
    }


    return result;
}

int main() {

    
    char symb;

    scanf("%c", &symb);

    printf("%c", swap_case(symb));

    



    return 0;
}
#include <stdio.h>

int del_message(int forum[1000005], int number) {

    int index = 0, z=0;

    for (; index<1000005; index++) {
        if (forum[index] == number) {
            z += del_message(forum, index);
        }
    }

    return 1 + z;

}



int main(void) {

    int forum[1000005] = {0}, n=0, k=0, current_message=0, r=0;

    scanf("%d", &n);

    for (; k<n; k++) {
        scanf("%d", &current_message);
        scanf("%d", &forum[current_message]);
    }

    scanf("%d", &current_message);


    r = del_message(forum, current_message);

    printf("%d", r);

    



    return 0;
}
#include <stdio.h>

int main() {

    int count = 0;
    int prev_num, cur_num;

    scanf("%d", &prev_num);

    while (prev_num != 0) {

        scanf("%d", &cur_num);
        count += cur_num>prev_num;
        prev_num = cur_num;

    }

    printf("%d", count);





    return 0;
}
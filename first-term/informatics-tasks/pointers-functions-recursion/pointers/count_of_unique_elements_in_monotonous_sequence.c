#include <stdio.h>

int main(void) {

    int n=0, count=1, prev_n=0, cur_n=0, i=0;
    int *n_p=&n, *count_p=&count, *prev_n_p=&prev_n, *cur_n_p=&cur_n, *i_p=&i;
    scanf("%d%d", n_p, prev_n_p);

    for (; *i_p<*n_p-1; *(i_p) += 1) {
        scanf("%d", cur_n_p);
        if (*cur_n_p>*prev_n_p) {*count_p += 1;}
        *prev_n_p = *cur_n_p;
    }

    printf("%d", *count_p);

    return 0;
}
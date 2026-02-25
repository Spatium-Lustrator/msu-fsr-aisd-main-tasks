#include <stdio.h>

int main(void) {

    int arr[35] = {0}, n=0, temp=0, i=0, j=0, k=0;
    int *n_p=&n, *temp_p=&temp, *i_p=&i, *j_p=&j, *k_p=&k;

    scanf("%d", n_p);
    for (; *i_p<*n_p; *i_p += 1) {scanf("%d", arr + *i_p);}

    for (; *j_p<(*n_p/2); *j_p += 1) {
        *temp_p = *(arr + *j_p);
        *(arr + *j_p) = *(arr + *n_p - 1 - *j_p);
        *(arr + *n_p - 1 - *j_p) = *temp_p;

    }

    for (; *k_p<*n_p; *k_p += 1) {
        printf("%d ", *(arr + *k_p));
    }



    return 0;
}
#include <stdio.h>

int main() {

    int n, count=0, cur_el=1, cur_el_c=0;
    scanf("%d", &n);

    while (count < n) {
        printf("%d ", cur_el);
        cur_el_c++;
        count++;
        if (cur_el==cur_el_c) {
            cur_el++;
            cur_el_c=0;
        }
    }

    return 0;
}
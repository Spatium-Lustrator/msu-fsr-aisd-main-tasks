#include <stdio.h>

int main() {

    int k, m, n;

    scanf("%d", &k);
    scanf("%d", &m);
    scanf("%d", &n);

    if (n<=k) {
        printf("%d", 2*m);
    } else {
        int h = (2*n)/k;
        if (h*k==2*n) {
            printf("%d", h*m);
        } else {
            printf("%d", (h+1)*m);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {

    int h1, h2, a1, a2;

    scanf("%d", &h1);
    scanf("%d", &h2);
    scanf("%d", &a1);
    scanf("%d", &a2);

    int d1,d2;

    d1 = abs(h1 - a1);
    d2 = abs(h2 - a2);

    if ((d1==2 & d2==1) | (d1==1 & d2==2)) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
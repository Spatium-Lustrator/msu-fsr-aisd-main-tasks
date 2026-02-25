#include <stdio.h>

int main() {
    int x,y, n=0;
    double p;

    scanf("%d %lf %d", &x, &p, &y);

    x*=100;
    y*=100;
    p /= 100;

    while (x<y) {
        x += x*p;
        n+=1;
    }

    printf("%d", n);




    return 0;
}
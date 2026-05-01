#include <stdio.h>
#include <math.h>

int main(void) {

    double a, b, c, r;
    double new_c;

    scanf("%lf %lf %lf %lf", &a, &b, &c, &r);

    new_c = (-1)*r*(sqrt(pow(a, 2) + pow(b, 2))) + c;

    printf("%lf %lf %lf", a, b, new_c);

    return 0;
}
#include <stdio.h>

double recursion(double num, int deg) {

    if (deg == 1) return num;

    return num*(recursion(num, deg-1));

}

int main(void) {

    double a = 0.0;
    int n =0;
    double z =  1/ 2.0;

    scanf("%lf%d", &a, &n);


    if (n<0) {
        z = recursion(a, n*(-1));
        printf("%lf", 1/z);
    } else if (n>0) {
        printf("%lf", recursion(a, n));
    } else {
        printf("1");
    }



    return 0;
}
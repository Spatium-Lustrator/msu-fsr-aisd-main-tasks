#include <stdio.h>


int main() {

    int n, i=0, j=1, r=0;
    int trains[100];
    scanf("%d", &n);
    
    for (i; i<n; i++) scanf("%d", &trains[i]);

    for (j; j<n; j++) {
        if (trains[j] != (trains[j-1] + 1)) {r++;}
    } 
    printf("%d", r);




    return 0;
}
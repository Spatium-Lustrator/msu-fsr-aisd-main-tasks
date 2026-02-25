#include <stdio.h>

int main() {
    int m,n,k, lower_floor, upper_floor, up_cost, down_cost;
    scanf("%d%d%d", &m, &n, &k);

    if (n%k==1) {
        printf("0");
    } else {
        if (n%k==0) {
            lower_floor = n+1-k, upper_floor = n+1;
        } else {
            lower_floor = ((n/k)*k + 1), upper_floor = ((n/k)+1)*k+1;
        }

        up_cost = (n - lower_floor)*200, down_cost = (upper_floor-n)*100;



        if (upper_floor <= m) {
            if (up_cost>down_cost) {
                printf("%d", down_cost);
            } else {
                printf("%d", up_cost);
            }
        } else {
            printf("%d", up_cost);
        }
    }
    
    return 0;
}
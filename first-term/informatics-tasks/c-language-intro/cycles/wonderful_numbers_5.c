#include <stdio.h>

int dupicated(int num) {
    int count_of_num_in_int[10] = {0};
    int flag = 0;

    while (num>0) {
        count_of_num_in_int[num%10]++;
        num/=10;
    }

    for (int i=0; i<10; i++) {
        if (count_of_num_in_int[i] == 3) {flag=1;}
    }

    return flag==1;

    
}

int main() {

    int lr, rr; 

    scanf("%d", &lr);
    scanf("%d", &rr);

    for (lr; lr<=rr; lr++) {
        if (dupicated(lr)) {printf("%d\n", lr);}
    }
    
    return 0;
}
#include <stdio.h>

void show_state_of_scales_if_its_ok(int taken_weights_from_set[], int weights_set[], int count_of_weights) {
    int left_flag=0, right_flag=0, i=0;

    for (i=0; i<count_of_weights; i++) {
        if (taken_weights_from_set[i]==1) {
            left_flag=1;
            printf("%d ", weights_set[i]);
        }
    }

    if (left_flag==0) {
        printf("0");
    }
    
    printf("\n");

    right_flag=0;
    for (i=0; i<count_of_weights; i++) {
        if (taken_weights_from_set[i]==2) {
            right_flag=1;
            printf("%d ", weights_set[i]);
        }
    }

    if (right_flag==0) {
        printf("0");
    }

    printf("\n");

}

int calculating_state_of_scales(int step, int preexisted_weight_on_left_cup, int count_of_weights, int taken_weights_from_set[], int weights_set[]) {

    int sum_weight_in_left_cup = preexisted_weight_on_left_cup, sum_weight_in_right_cup = 0, i=0, j=0;

    if (step==count_of_weights) {

        for (i = 0; i < count_of_weights; i++) {
            if (taken_weights_from_set[i] == 1) {

                sum_weight_in_left_cup += weights_set[i];

            } else if (taken_weights_from_set[i] == 2) {

                sum_weight_in_right_cup += weights_set[i];

            }
        }

        return sum_weight_in_left_cup == sum_weight_in_right_cup;
    }

    for (j=0; j<=2; j++) {

        taken_weights_from_set[step] = j;

        if (calculating_state_of_scales(step+1, preexisted_weight_on_left_cup, count_of_weights, taken_weights_from_set, weights_set)) {

            return 1;
        }
    }
    return 0;
}



int main(void) {

    int preexisted_weight_on_left_cup=0, count_of_weights=0, weights_set[10]={0}, taken_weights_from_set[10]={0}, i=0;

    scanf("%d %d", &preexisted_weight_on_left_cup, &count_of_weights);

    for (i=0; i<count_of_weights; i++) {

        scanf("%d", weights_set+i);

    }

    if (calculating_state_of_scales(0, preexisted_weight_on_left_cup, count_of_weights, taken_weights_from_set, weights_set) == 0) {

        printf("-1");

    } else {

        show_state_of_scales_if_its_ok(taken_weights_from_set, weights_set, count_of_weights);
    }
}
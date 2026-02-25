#include <stdio.h>

int main() {

    int balls_arr[1001] = {0};
    int count_of_deleted=0, count_of_in_a_row=1, count_of_balls =0, i=0, j=0, k=0, stindex=0;

    scanf("%d", &count_of_balls);
    
    for (i; i<count_of_balls; i++){ scanf("%d", (balls_arr+i)); }
    for (i=0; i<count_of_balls; i++) {balls_arr[i]++;}


    for (k; k<count_of_balls+1; k++) {
        stindex = 0;
        for (i=1; i<count_of_balls+1; i++) {
            if ( (balls_arr[i]==balls_arr[stindex]) && (balls_arr[i]!=0)) {count_of_in_a_row++;}

            if ( ( ((balls_arr[i]!=balls_arr[stindex]) && (balls_arr[i]!=0)) || (i==(count_of_balls))) ) {
                if ((count_of_in_a_row>=3)) {
                    // count_of_deleted += count_of_in_a_row;
                    for (j=stindex; j<i; j++) {
                        if (balls_arr[j]!=0) {
                            balls_arr[j] = 0;
                            count_of_deleted++;
                        }
                    }
                }
                
                count_of_in_a_row = 1;
                stindex = i;
            }
        }
    }

    printf("%d", count_of_deleted);


    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct apple_area {

    int center_height;
    int x,y,r;

} apple_area;

apple_area* create_new_area(int x, int y, int z, int r) {
    apple_area *new_area = malloc(sizeof(apple_area));

    new_area->center_height = z-r;

    new_area->x = x;
    new_area->y = y;
    new_area->r = r;

    return new_area;
}

int intersection(int x1, int y1, int r1, int x2, int y2, int r2) {
    return ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) <= (r1+r2)*(r1+r2) ;
}

int hitted(apple_area *area_of_falling, apple_area *area_of_probably_hitted) {

    return (area_of_probably_hitted->center_height < area_of_falling->center_height && intersection(area_of_falling->x, area_of_falling->y, area_of_falling->r, area_of_probably_hitted->x, area_of_probably_hitted->y, area_of_probably_hitted->r));

}

int already_hitted(int *hitted_arr, int apple, int count_of_hitted) {
    int i, flag=0;
    for (i=0; i<count_of_hitted; i++) {
        flag |= (hitted_arr[i] == apple);
    }

    return flag;
}

int main(void) {

    int n, i, j, count_of_fallen_apples=0;
    int apple_x, apple_y, apple_z, apple_r;
    int fallen_apples[200];
    apple_area *hitted_areas[200], *all_areas[200], *cur_area;

    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%d %d %d %d", &apple_x, &apple_y, &apple_z, &apple_r);
        cur_area = create_new_area(apple_x, apple_y, apple_z, apple_r);
        all_areas[i] = cur_area;
    }

    fallen_apples[0] = 1;
    hitted_areas[0] = all_areas[0];
    count_of_fallen_apples++;

    for (i=0; i<count_of_fallen_apples; i++) {
        for (j=0; j<n; j++) {
            if (fallen_apples[i] != j+1 && !(already_hitted(fallen_apples, j+1, count_of_fallen_apples)) && hitted(hitted_areas[i], all_areas[j])) {
                fallen_apples[count_of_fallen_apples] = j+1;
                hitted_areas[count_of_fallen_apples] = all_areas[j];
                count_of_fallen_apples++;
            }
        }
    }

    printf("%d\n", count_of_fallen_apples);

    for (i=0; i<count_of_fallen_apples; i++) {
        printf("%d ", fallen_apples[i]);
    }

    for(i=0; i<n; i++) {
        free(all_areas[i]);
    }



    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define SHIFT_START 0
#define SHIFT_END 1

typedef struct point {

    int type_of_point;
    int box_office_number;
    int time;

} point;

void create_point_in_schedule(point **points, int index_in_array, int type_of_point, int time, int box_office) {
    points[index_in_array] = (point*) malloc(sizeof(point));
    points[index_in_array]->type_of_point = type_of_point;
    points[index_in_array]->box_office_number = box_office;
    points[index_in_array]->time = time;
}

void merge(point **array, int left, int middle, int right) {

    int count_in_left_part = middle-left+1;
    int count_in_right_part = right-middle;
    int i, j, k;

    point **left_array, **right_array;

    left_array = (point**) calloc(count_in_left_part, sizeof(point*));
    right_array = (point**) calloc(count_in_right_part, sizeof(point*));

    for (i=0; i<count_in_left_part; i++) left_array[i] = array[left+i];
    for (j=0; j<count_in_right_part; j++) right_array[j] = array[middle+j+1];

    i=0;
    j=0; 
    k=left;

    while (i<count_in_left_part && j<count_in_right_part) {

        if ((left_array[i]->time < right_array[j]->time) || (left_array[i]->time == right_array[j]->time && left_array[i]->type_of_point == SHIFT_END)) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }

        k++;
    }

    while (i<count_in_left_part) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j<count_in_right_part) {
        array[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}

void merge_sort(point **array, int left, int right) {
    if (left < right) {
      
        int middle = left + (right-left)/2;

        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);

        merge(array, left, middle, right);
    }
}

int get_time_of_all_box_offices_working_together(point **points_in_schedule, int *active, int count_of_points, int count_of_box_offices) {
    int result = 0, last_processed_time=-1;
    int current_max_start_time=0, count_of_active_box_offices=0;
    int i, j;

    for (i=0; i<count_of_box_offices; i++) active[i] = -1;

    for (i=0; i<count_of_points; i++) {
        current_max_start_time = 0;

        if (points_in_schedule[i]->type_of_point == SHIFT_START) {

            active[points_in_schedule[i]->box_office_number] = points_in_schedule[i]->time;
            count_of_active_box_offices++;
        } else if (points_in_schedule[i]->type_of_point == SHIFT_END) {
            if (count_of_active_box_offices == count_of_box_offices) {
                result += points_in_schedule[i]->time - last_processed_time;
            }
            count_of_active_box_offices--;

            active[points_in_schedule[i]->box_office_number] = -1;
        }
        last_processed_time = points_in_schedule[i]->time;
    }

    return result;
}


int main(void) {

    point **points_in_schedule;

    int *active;
    int count_of_box_offices;
    int current_start_hour, current_start_minute, current_start_second;
    int current_end_hour, current_end_minute, current_end_second;
    int current_start_time, current_end_time;
    int i, j=0;

    scanf("%d", &count_of_box_offices);

    points_in_schedule = (point**) calloc(4*count_of_box_offices, sizeof(point*));

    for (i=0; i<count_of_box_offices; i++) {
        scanf("%d %d %d %d %d %d", &current_start_hour, &current_start_minute, &current_start_second, &current_end_hour, &current_end_minute, &current_end_second);

        current_start_time = current_start_hour*3600 + current_start_minute*60 + current_start_second;
        current_end_time = current_end_hour*3600 + current_end_minute*60 + current_end_second;

        if (current_start_time < current_end_time) {
            create_point_in_schedule(points_in_schedule, j, SHIFT_START, current_start_time, i);
            j++;

            create_point_in_schedule(points_in_schedule, j, SHIFT_END, current_end_time, i);
            j++;

        } else if (current_start_time == current_end_time) {
            create_point_in_schedule(points_in_schedule, j, SHIFT_START, 0, i);
            j++;

            create_point_in_schedule(points_in_schedule, j, SHIFT_END, 24*60*60, i);
            j++;
        } else if (current_start_time > current_end_time) {

            create_point_in_schedule(points_in_schedule, j, SHIFT_START, 0, i);
            j++;

            create_point_in_schedule(points_in_schedule, j, SHIFT_END, current_end_time, i);
            j++;

            create_point_in_schedule(points_in_schedule, j, SHIFT_START, current_start_time, i);
            j++;

            create_point_in_schedule(points_in_schedule, j, SHIFT_END, 24*60*60, i);
            j++;
        }
    }

    points_in_schedule = realloc(points_in_schedule, sizeof(point*)*j);
    active = (int*) calloc(count_of_box_offices, sizeof(int));

    merge_sort(points_in_schedule, 0, j-1);

    printf("%d", get_time_of_all_box_offices_working_together(points_in_schedule, active, j, count_of_box_offices));

    for (i=0; i<j; i++) {
        free(points_in_schedule[i]);
    }

    free(points_in_schedule);
    free(active);





    return 0;
}
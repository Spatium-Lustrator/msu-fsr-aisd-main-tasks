#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define diff 1e-6

typedef struct point {
    double x;
    double y;

} point;

typedef struct polyangle {

    int count_of_points;
    int not_invaded;
    
    double square;

    point **array_of_points;

} polyangle;

double shoelace_summand(point *first_point, point *second_point) {
    return (first_point->x)*(second_point->y) - (second_point->x)*(first_point->y);
}

void calculate_polyangle_square(polyangle *polyangle_to_calculate_the_square) {

    point **array_of_points = polyangle_to_calculate_the_square->array_of_points;

    int count_of_points = polyangle_to_calculate_the_square->count_of_points;
    int i;
    
    double square = shoelace_summand(array_of_points[count_of_points-1], array_of_points[0]);

    for (i=1; i<count_of_points; i++) {
        square += shoelace_summand(array_of_points[i-1], array_of_points[i]);
    }

    polyangle_to_calculate_the_square->square = fabs(square/2);

}

void merge(polyangle **array, int left, int middle, int right) {

    int count_in_left_part = middle-left+1;
    int count_in_right_part = right-middle;
    int turn;
    int i, j, k;

    polyangle **left_array, **right_array;

    left_array = (polyangle**) calloc(count_in_left_part, sizeof(polyangle*));
    right_array = (polyangle**) calloc(count_in_right_part, sizeof(polyangle*));

    for (i=0; i<count_in_left_part; i++) left_array[i] = array[left+i];
    for (j=0; j<count_in_right_part; j++) right_array[j] = array[middle+j+1];

    i=0;
    j=0; 
    k=left;

    while (i<count_in_left_part && j<count_in_right_part) {

        if (left_array[i]->square < right_array[j]->square) {
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

void merge_sort(polyangle **array, int left, int right) {
    if (left < right) {
      
        int middle = left + (right-left)/2;

        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);

        merge(array, left, middle, right);
    }
}

int rotation_predicate(point *p1, point *p2, point *p3) {
    double value = (p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x);
    if (value > diff) {
        return 1;
    } else if (value < -diff) {
        return -1;
    } else {
        return 0;
    }
}

int is_point_out_of_polyangle(point **array_of_all_vertexes, point *point_to_check, int count_of_vertexes) {
    int middle, left=0, right=count_of_vertexes-1;

    if (rotation_predicate(point_to_check, array_of_all_vertexes[0], array_of_all_vertexes[1]) == -1) return 1;
    if (rotation_predicate(point_to_check, array_of_all_vertexes[0], array_of_all_vertexes[count_of_vertexes-1]) == 1) return 1;

    while (right - left > 1) {
        middle = left + ((right-left)/2);

        if (rotation_predicate(point_to_check, array_of_all_vertexes[0], array_of_all_vertexes[middle]) >= 0) {
            left = middle;
        } else {
            right = middle;
        }
    }

    return rotation_predicate(point_to_check, array_of_all_vertexes[left], array_of_all_vertexes[right]) == -1;
}

int binary_search_of_smallest_to_contain_invader(polyangle **array_of_polyangles, point *invader, int count_of_polyangles) {
    int middle, left=0, right=count_of_polyangles-1;
    int min_index_of_polyangle_containing_invader = count_of_polyangles+1;

    while (left <= right) {
        middle = left + ((right-left)/2);

        if (!(is_point_out_of_polyangle(array_of_polyangles[middle]->array_of_points, invader, array_of_polyangles[middle]->count_of_points))) {
            min_index_of_polyangle_containing_invader = middle;
            right = middle - 1;
        } else {
            left = middle + 1;
        }

    }

    return min_index_of_polyangle_containing_invader;

}

double get_invaded_square(polyangle **array_of_polyangles, int count_of_polyangles, point **invaders, int count_of_invaders) {

    int index;
    int i;

    double square = 0.0;

    for (i=0; i<count_of_invaders; i++) {
        if (!(is_point_out_of_polyangle(array_of_polyangles[count_of_polyangles-1]->array_of_points, invaders[i], array_of_polyangles[count_of_polyangles-1]->count_of_points))) {
            if (!(is_point_out_of_polyangle(array_of_polyangles[0]->array_of_points, invaders[i], array_of_polyangles[0]->count_of_points))) {
                square += (array_of_polyangles[0]->square)*(array_of_polyangles[0]->not_invaded);
                array_of_polyangles[0]->not_invaded = 0;
            } else {
                index = binary_search_of_smallest_to_contain_invader(array_of_polyangles, invaders[i], count_of_polyangles);
                square += (array_of_polyangles[index]->square - array_of_polyangles[index-1]->square)*(array_of_polyangles[index]->not_invaded);
                array_of_polyangles[index]->not_invaded = 0;
            }
        }
    }

    return square;
}

int main(void) {

    polyangle **array_of_polyangles;

    point **invaders;

    int count_of_polyangles, count_of_invaders;
    int current_count_of_points;
    int i, j;

    double current_x, current_y;

    scanf("%d", &count_of_polyangles);

    array_of_polyangles = (polyangle**) calloc(count_of_polyangles, sizeof(polyangle*));

    for (i=0; i<count_of_polyangles; i++) {
        scanf("%d", &current_count_of_points);

        array_of_polyangles[i] = (polyangle*) malloc(sizeof(polyangle));
        array_of_polyangles[i]->count_of_points = current_count_of_points;
        array_of_polyangles[i]->not_invaded = 1;
        array_of_polyangles[i]->array_of_points = (point**) calloc(current_count_of_points, sizeof(point*));

        for (j=0; j<current_count_of_points; j++) {
            scanf("%lf %lf", &current_x, &current_y);

            (array_of_polyangles[i]->array_of_points)[j] = (point*) malloc(sizeof(point));
            (array_of_polyangles[i]->array_of_points)[j]->x = current_x;
            (array_of_polyangles[i]->array_of_points)[j]->y = current_y;
        }

        calculate_polyangle_square(array_of_polyangles[i]);

    }

    scanf("%d", &count_of_invaders);

    invaders = (point**) calloc(count_of_invaders, sizeof(point*));

    for (i=0; i<count_of_invaders; i++) {
        scanf("%lf %lf", &current_x, &current_y);
        
        invaders[i] = (point*) malloc(sizeof(point));
        invaders[i]->x = current_x;
        invaders[i]->y = current_y;
    }

    merge_sort(array_of_polyangles, 0, count_of_polyangles-1);

    printf("%lf", get_invaded_square(array_of_polyangles, count_of_polyangles, invaders, count_of_invaders));

    for (i=0; i<count_of_polyangles; i++) {

        for (j=0; j<array_of_polyangles[i]->count_of_points; j++) free((array_of_polyangles[i]->array_of_points)[j]);

        free(array_of_polyangles[i]->array_of_points);
        free(array_of_polyangles[i]);
    }

    free(array_of_polyangles);

    for (i=0; i<count_of_invaders; i++) free(invaders[i]);
    
    free(invaders);


    return 0;
}
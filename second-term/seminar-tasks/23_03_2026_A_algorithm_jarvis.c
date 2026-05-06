#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define diff 0.000000001

typedef struct point {
    double x;
    double y;

} point;

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

int find_rightest_lowest_point(point **array, int count_of_points) {
    point *current_rightest_lowest_point = array[0];
    int i, result=0;

    for (i=1; i<count_of_points; i++) {
        if (current_rightest_lowest_point->x < array[i]->x || (current_rightest_lowest_point->x-array[i]->x<diff && current_rightest_lowest_point->y > array[i]->y)) {
            current_rightest_lowest_point = array[i];
            result = i;
        }
    }

    return result;

}

void get_convex_hull(point **array_of_all_points, point **convex_hull, int count_of_points) {

    int current_point_index, temp_point_index;
    int pivot_point_index;
    int count_of_points_in_hull=0, i;

    pivot_point_index = find_rightest_lowest_point(array_of_all_points, count_of_points);

    current_point_index = pivot_point_index; 

    do {

        convex_hull[count_of_points_in_hull] = array_of_all_points[current_point_index];
        count_of_points_in_hull++;

        temp_point_index = (current_point_index+1)%count_of_points;

        for (i=0; i<count_of_points; i++) {
            if (rotation_predicate(array_of_all_points[current_point_index], array_of_all_points[i], array_of_all_points[temp_point_index]) == -1) temp_point_index = i;
        }

        current_point_index = temp_point_index;

    } while (current_point_index != pivot_point_index);

}

void print_convex_hull(point **hull_array, int count_of_points) {

    int i;

    printf("%lf %lf\n", hull_array[0]->x, hull_array[0]->y);

    for (i=count_of_points-1; i>0; i--) {
        if (hull_array[i] != NULL) printf("%lf %lf\n", hull_array[i]->x, hull_array[i]->y);;
    }

}

int main(void) {

    point **points, **hull;

    double current_x, current_y;

    int count_of_points;
    int i;

    scanf("%d", &count_of_points);

    points = (point**) malloc(count_of_points*sizeof(point*));
    hull = (point**) calloc(count_of_points, sizeof(point*));

    for (i=0; i<count_of_points; i++) {
        scanf("%lf %lf", &current_x, &current_y);

        points[i] = (point*) malloc(sizeof(point));
        points[i]->x = current_x;
        points[i]->y = current_y;        

    }

    get_convex_hull(points, hull, count_of_points);
    print_convex_hull(hull, count_of_points);

    for (i=0; i<count_of_points; i++) {
        free(points[i]);
    }

    free(points);
    free(hull);


    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define diff 0.000000001

typedef struct point {
    int x;
    int y;

} point;

int min(int first_value, int second_value) {
    if (first_value < second_value) {
        return first_value;
    } else {
        return second_value;
    }
}

int max(int first_value, int second_value) {
    if (first_value > second_value) {
        return first_value;
    } else {
        return second_value;
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

int is_point_out_of_polyangle(point **array_of_all_points, point *point_to_check, int count_of_points) {
    point *point_a, *point_b;
    
    double intersection_x, part_of_calculations;

    int count_of_intersections=0, flag_is_on_edge=0;
    int i;

    for (i=1; i<count_of_points && !flag_is_on_edge; i++) {
        point_a = array_of_all_points[i-1];
        point_b = array_of_all_points[i];

        if ((rotation_predicate(point_to_check, point_a, point_b) == 0) && (min(point_a->x, point_b->x) <= point_to_check->x) &&
         (max(point_a->x, point_b->x) >= point_to_check->x) && (min(point_a->y, point_b->y) <= point_to_check->y) && 
         (max(point_a->y, point_b->y) >= point_to_check->y)) {
            flag_is_on_edge = 1;
        }

        if ((min(point_a->y, point_b->y) <= point_to_check->y) && (max(point_a->y, point_b->y) > point_to_check->y)) {
            part_of_calculations = (point_to_check->y - point_a->y)*(point_b->x - point_a->x); 
            intersection_x = ((part_of_calculations)/(point_b->y - point_a->y)) + point_a->x;

            if (intersection_x >= point_to_check->x) count_of_intersections++;
        }   

    }

    point_a = array_of_all_points[count_of_points-1];
    point_b = array_of_all_points[0];

    if ((min(point_a->y, point_b->y) <= point_to_check->y) && (max(point_a->y, point_b->y) > point_to_check->y)) {
        part_of_calculations = (point_to_check->y - point_a->y)*(point_b->x - point_a->x); 
        intersection_x = ((part_of_calculations)/(point_b->y - point_a->y)) + point_a->x;

        if (intersection_x >= point_to_check->x) count_of_intersections++;
    }

    if (flag_is_on_edge) return 0;
    
    return (count_of_intersections+1)%2;

}

int main(void) {

    point **all_points_of_polyangle;
    point *point_to_check;

    int count_of_points;
    int current_x, current_y;
    int i;

    
    
    scanf("%d %d %d", &count_of_points, &current_x, &current_y);
    
    all_points_of_polyangle = (point**) calloc(count_of_points, sizeof(point*));
    
    point_to_check = (point*) malloc(sizeof(point));
    point_to_check->x = current_x;
    point_to_check->y = current_y;
    
    for (i=0; i<count_of_points; i++) {
        scanf("%d %d", &current_x, &current_y);
        
        all_points_of_polyangle[i] = (point*) malloc(sizeof(point));
        all_points_of_polyangle[i]->x = current_x;
        all_points_of_polyangle[i]->y = current_y;
        
    }
    
    printf("%s", is_point_out_of_polyangle(all_points_of_polyangle, point_to_check, count_of_points) ? "NO": "YES");

    for (i=0; i<count_of_points; i++) {
        free(all_points_of_polyangle[i]);
    }

    free(all_points_of_polyangle);
    free(point_to_check);




    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define diff 0.000000001

typedef struct point {
    double x;
    double y;

} point;

typedef struct stack_node {
    point *point_in_stack; 
    struct stack_node *next;

} stack_node;

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

void push(stack_node **top_element, point *point_to_push) {
    struct stack_node *new_element_to_push = (stack_node*) malloc(sizeof(stack_node)); 
    
    new_element_to_push->point_in_stack = point_to_push;
    new_element_to_push->next = *top_element;
    (*top_element) = new_element_to_push;
    
}

point* top(stack_node *top_element) {
    return top_element->point_in_stack;
}

point* second_at_top(stack_node *top_element) {
    return top_element->next->point_in_stack;
}

void clear(struct stack_node **top_element) {
    stack_node *current = *top_element;
    stack_node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *top_element = NULL;
}

void pop(stack_node **top_element) {

    stack_node *tmp = (*top_element);
    if (tmp) {
        (*top_element) = (*top_element)->next;
        free(tmp);
    }
    
}


point* find_rightest_lowest_point(point **array, int count_of_points) {
    point *current_rightest_lowest_point = array[0];
    int i;

    for (i=1; i<count_of_points; i++) {
        if (current_rightest_lowest_point->x < array[i]->x || (current_rightest_lowest_point->x-array[i]->x<diff && current_rightest_lowest_point->y > array[i]->y)) {
            current_rightest_lowest_point = array[i];
        }
    }

    return current_rightest_lowest_point;

}

double get_polar_angle(point *pivot_point, point *point_to_calculate_angle) {
    return -atan2((point_to_calculate_angle->y-pivot_point->y),(pivot_point->x-point_to_calculate_angle->x));
}

double get_squared_dist_to_pivot(point *pivot_point, point *point_to_calc_dist) {
    return pow(pivot_point->x - point_to_calc_dist->x, 2) + pow(pivot_point->y - point_to_calc_dist->y, 2);
}

void swap(point **arr, int j) {
    point *tmp = arr[j];
    arr[j] = arr[j-1];
    arr[j-1] = tmp;
}

point** sort_except_of_pivot(point **array_of_all_points, point *pivot_point, int count_of_points, int *count_of_null_output) {
    int count_of_null = 0;
    int i, j, k=0;

    double angle_pivot_first;
    double angle_pivot_second;
    double dist_to_pivot_first;
    double dist_to_pivot_second;

    point **array_of_all_points_except_pivot = (point**) calloc(count_of_points-1, sizeof(point*));
    point **array_of_all_points_except_pivot_and_collinear;
    for (i=0; i<count_of_points; i++) {
        if (fabs(array_of_all_points[i]->x - pivot_point->x ) > diff || fabs(array_of_all_points[i]->y - pivot_point->y) > diff) {
            array_of_all_points_except_pivot[k] = array_of_all_points[i];
            k++;
        }
    }

    for (i=0; i<count_of_points; i++) {
        for (j=1; j<count_of_points-1; j++) {
            angle_pivot_first = get_polar_angle(pivot_point, array_of_all_points_except_pivot[j-1]);
            angle_pivot_second = get_polar_angle(pivot_point, array_of_all_points_except_pivot[j]);
            dist_to_pivot_first = get_squared_dist_to_pivot(pivot_point, array_of_all_points_except_pivot[j-1]);
            dist_to_pivot_second = get_squared_dist_to_pivot(pivot_point, array_of_all_points_except_pivot[j]);

            if (angle_pivot_first > angle_pivot_second) {
                swap(array_of_all_points_except_pivot, j);
            }

            if (fabs(angle_pivot_first - angle_pivot_second) < diff && dist_to_pivot_first > dist_to_pivot_second) {
                swap(array_of_all_points_except_pivot, j);
            }
        }
    }

    for (i=1; i<count_of_points-1; i++) {
        angle_pivot_first = get_polar_angle(pivot_point, array_of_all_points_except_pivot[i-1]);
        angle_pivot_second = get_polar_angle(pivot_point, array_of_all_points_except_pivot[i]);
        if (array_of_all_points_except_pivot != NULL && fabs(angle_pivot_first - angle_pivot_second) < diff) {
            array_of_all_points_except_pivot[i-1] = NULL;
            count_of_null++;
        }
    }

    array_of_all_points_except_pivot_and_collinear = (point**) calloc(count_of_points-1-count_of_null, sizeof(point*));
    k=0;

    for (i=0; i<count_of_points-1; i++) {
        if (array_of_all_points_except_pivot[i] != NULL) {
            array_of_all_points_except_pivot_and_collinear[k] = array_of_all_points_except_pivot[i];
            k++;
        }
    }

    free(array_of_all_points_except_pivot);
    (*count_of_null_output) = count_of_null;
    return array_of_all_points_except_pivot_and_collinear;



}

stack_node* get_convex_hull(point **array_of_all_points, int count_of_points) {

    stack_node *top_element = NULL;
    point *pivot_point, **array_of_all_points_except_pivot;

    int predicate_value, count_of_null;
    int i;
    
    pivot_point = find_rightest_lowest_point(array_of_all_points, count_of_points);
    array_of_all_points_except_pivot = sort_except_of_pivot(array_of_all_points, pivot_point, count_of_points, &count_of_null);

    if (count_of_points < 3) {
        push(&top_element, pivot_point);
        if (count_of_points == 2) push(&top_element, array_of_all_points_except_pivot[0]);
        return top_element;
    }

    push(&top_element, pivot_point);
    push(&top_element, array_of_all_points_except_pivot[0]);
    push(&top_element, array_of_all_points_except_pivot[1]);

    for (i=2; i<count_of_points-1-count_of_null; i++) {
        while (rotation_predicate(second_at_top(top_element), top(top_element), array_of_all_points_except_pivot[i]) != 1) {
            pop(&top_element);
        }
        push(&top_element, array_of_all_points_except_pivot[i]);
    }

    return top_element;

}

void print_convex_hull(stack_node *element) {

    if (element) {
        print_convex_hull(element->next);
        printf("%lf %lf\n", element->point_in_stack->x, element->point_in_stack->y);
        free(element);
    }

}


int main(void) {

    stack_node *top_stack_point = NULL;
    point **points, *pivot_point;

    double current_x, current_y;

    int count_of_points;
    int i;


    scanf("%d", &count_of_points);

    points = (point**) malloc(count_of_points*sizeof(point*));

    for (i=0; i<count_of_points; i++) {
        scanf("%lf %lf", &current_x, &current_y);

        points[i] = (point*) malloc(sizeof(point));
        points[i]->x = current_x;
        points[i]->y = current_y;        

    }

    top_stack_point = get_convex_hull(points, count_of_points);
    print_convex_hull(top_stack_point);

    for (i=0; i<count_of_points; i++) {
        free(points[i]);
    }

    free(points);

    return 0;
}

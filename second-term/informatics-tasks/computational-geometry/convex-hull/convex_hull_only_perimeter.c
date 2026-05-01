#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define diff 1e-6

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

void pop(stack_node **top_element) {

    stack_node *tmp = (*top_element);
    if (tmp) {
        (*top_element) = (*top_element)->next;
        free(tmp);
    }
    
}


int find_rightest_lowest_point_index(point **array, int count_of_points) {
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

double get_dist_between_points(point *first_point_to_calc_dist, point *second_point_to_calc_dist) {
    return sqrt(pow(first_point_to_calc_dist->x - second_point_to_calc_dist->x, 2) + pow(first_point_to_calc_dist->y - second_point_to_calc_dist->y, 2));
}



void merge(point **array, point *pivot_point, int left, int middle, int right) {

    int count_in_left_part = middle-left+1;
    int count_in_right_part = right-middle;
    int turn;
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

        turn = rotation_predicate(pivot_point, left_array[i], right_array[j]);

        if (turn == 1 || (turn == 0 && get_dist_between_points(pivot_point, left_array[i]) < get_dist_between_points(pivot_point, right_array[j]))) {
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

void merge_sort(point **array, point *pivot_point, int left, int right) {
    if (left < right) {
      
        int middle = left + (right-left)/2;

        merge_sort(array, pivot_point, left, middle);
        merge_sort(array, pivot_point, middle+1, right);

        merge(array, pivot_point, left, middle, right);
    }
}

stack_node* get_convex_hull(point **array_of_all_points, int count_of_points, int *convex_hull_count_of_points) {

    stack_node *top_element = NULL;
    point *pivot_point, *tmp;

    int pivot_point_index;
    int i;
    
    pivot_point_index = find_rightest_lowest_point_index(array_of_all_points, count_of_points);
    tmp = array_of_all_points[pivot_point_index];
    array_of_all_points[pivot_point_index] = array_of_all_points[0];
    array_of_all_points[0] = tmp;


    pivot_point = array_of_all_points[0];
    merge_sort(array_of_all_points, pivot_point, 1, count_of_points-1);


    push(&top_element, pivot_point);
    push(&top_element, array_of_all_points[1]);

    (*convex_hull_count_of_points) += 2;

    for (i=2; i<count_of_points; i++) {
        while (top_element->next->next != NULL && rotation_predicate(second_at_top(top_element), top(top_element), array_of_all_points[i]) != 1) {
            pop(&top_element);
            (*convex_hull_count_of_points) -= 1;
        }

        if (rotation_predicate(second_at_top(top_element), top(top_element), array_of_all_points[i]) == 1) {
            push(&top_element, array_of_all_points[i]);
            (*convex_hull_count_of_points) += 1;
        } else if (rotation_predicate(second_at_top(top_element), top(top_element), array_of_all_points[i]) == 0) {
            pop(&top_element);
            push(&top_element, array_of_all_points[i]);
        }
    }

    return top_element;

}

void put_convex_hull_in_array(point **array_to_put_into, stack_node *element, int count_of_points_in_hull) {
    stack_node *tmp, *current_element = element;

    int i = count_of_points_in_hull - 1;

    while (current_element) {
        array_to_put_into[i] = current_element->point_in_stack;
        tmp = current_element;
        current_element = current_element->next;
        free(tmp);
        i--;
    }

}

void get_perimeter_by_convex_hull(point **array_of_points_in_convex_hull, int count_of_points_in_convex_hull, double *perimeter_out) {

    double perimeter, square;
    
    int i;

    perimeter = get_dist_between_points(array_of_points_in_convex_hull[count_of_points_in_convex_hull-1], array_of_points_in_convex_hull[0]);

    for (i=1; i<count_of_points_in_convex_hull; i++) {
        perimeter += get_dist_between_points(array_of_points_in_convex_hull[i-1], array_of_points_in_convex_hull[i]);
    }

    (*perimeter_out) = perimeter;


}

int main(void) {

    point **array_of_all_points, **array_of_points_in_convex_hull;

    stack_node *top_element;

    double current_x, current_y;
    double perimeter;

    int count_of_points, count_of_points_in_convex_hull=0;
    int i;

    scanf("%d", &count_of_points);

    if (count_of_points == 1) {
        printf("%lf\n%lf", 0.0, 0.0);
        return 0;
    }

    array_of_all_points = (point**) calloc(count_of_points, sizeof(point*));

    for (i=0; i<count_of_points; i++) {
        scanf("%lf %lf", &current_x, &current_y);

        array_of_all_points[i] = (point*) malloc(sizeof(point));
        array_of_all_points[i]->x = current_x;
        array_of_all_points[i]->y = current_y;
    }

    top_element = get_convex_hull(array_of_all_points, count_of_points, &count_of_points_in_convex_hull);
    
    array_of_points_in_convex_hull = (point**) calloc(count_of_points_in_convex_hull, sizeof(point*));
    
    put_convex_hull_in_array(array_of_points_in_convex_hull, top_element, count_of_points_in_convex_hull);
    get_perimeter_by_convex_hull(array_of_points_in_convex_hull, count_of_points_in_convex_hull, &perimeter);

    printf("%lf\n", perimeter);

    for (i=0; i<count_of_points; i++) free(array_of_all_points[i]);
    free(array_of_all_points);
    free(array_of_points_in_convex_hull);

    return 0;
}
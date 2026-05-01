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

double get_squared_dist_to_pivot(point *pivot_point, point *point_to_calc_dist) {
    return pow(pivot_point->x - point_to_calc_dist->x, 2) + pow(pivot_point->y - point_to_calc_dist->y, 2);
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

        if (turn == 1 || (turn == 0 && get_squared_dist_to_pivot(pivot_point, left_array[i]) < get_squared_dist_to_pivot(pivot_point, right_array[j]))) {
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

stack_node* get_convex_hull(point **array_of_all_points, int count_of_points) {

    stack_node *top_element = NULL;
    point *pivot_point, *tmp;

    int predicate_value, pivot_point_index;
    int i;
    
    pivot_point_index = find_rightest_lowest_point_index(array_of_all_points, count_of_points);
    tmp = array_of_all_points[pivot_point_index];
    array_of_all_points[pivot_point_index] = array_of_all_points[0];
    array_of_all_points[0] = tmp;


    pivot_point = array_of_all_points[0];
    merge_sort(array_of_all_points, pivot_point, 1, count_of_points-1);


    push(&top_element, pivot_point);
    push(&top_element, array_of_all_points[1]);

    for (i=2; i<count_of_points; i++) {
        while (top_element->next->next != NULL && rotation_predicate(second_at_top(top_element), top(top_element), array_of_all_points[i]) != 1) {
            pop(&top_element);
        }

        if (rotation_predicate(second_at_top(top_element), top(top_element), array_of_all_points[i]) == 1) {
            push(&top_element, array_of_all_points[i]);
        } else if (rotation_predicate(second_at_top(top_element), top(top_element), array_of_all_points[i]) == 0) {
            pop(&top_element);
            push(&top_element, array_of_all_points[i]);
        }
    }

    return top_element;

}

int get_count_of_good_positions(stack_node *stack_element, double mass_center_x, double mass_center_y) {

    point *first_point, *second_point, *first_point_remembered;

    double first_scalar_product, second_scalar_product;
    double first_vector_x, first_vector_y, first_length;
    double second_vector_x, second_vector_y, second_length;
    double third_vector_x, third_vector_y, third_length;
    double first_angle, second_angle;

    int result = 0;

    first_point_remembered = top(stack_element);    

    while (stack_element->next != NULL) {
        first_point = top(stack_element);
        second_point = second_at_top(stack_element);
        
        first_vector_x = mass_center_x - first_point->x;
        first_vector_y = mass_center_y - first_point->y;
        first_length = sqrt(pow(first_vector_x, 2) + pow(first_vector_y, 2));

        second_vector_x = second_point->x - first_point->x;
        second_vector_y = second_point->y - first_point->y;
        second_length = sqrt(pow(second_vector_x, 2) + pow(second_vector_y, 2));

        third_vector_x = mass_center_x - second_point->x;
        third_vector_y = mass_center_y - second_point->y;
        third_length = sqrt(pow(third_vector_x, 2) + pow(third_vector_y, 2));

        first_scalar_product = first_vector_x*second_vector_x + first_vector_y*second_vector_y;
        second_scalar_product = third_vector_x*(-1)*second_vector_x + third_vector_y*(-1)*second_vector_y;

        first_angle = acos(first_scalar_product / (first_length*second_length));
        second_angle = acos(second_scalar_product / (third_length*second_length));

        if (first_angle < acos(0) && second_angle < acos(0)) result++;

        pop(&stack_element);

    }

    first_point = first_point_remembered;
    second_point = stack_element->point_in_stack;

    first_vector_x = mass_center_x - first_point->x;
    first_vector_y = mass_center_y - first_point->y;
    first_length = sqrt(pow(first_vector_x, 2) + pow(first_vector_y, 2));

    second_vector_x = second_point->x - first_point->x;
    second_vector_y = second_point->y - first_point->y;
    second_length = sqrt(pow(second_vector_x, 2) + pow(second_vector_y, 2));

    third_vector_x = mass_center_x - second_point->x;
    third_vector_y = mass_center_y - second_point->y;
    third_length = sqrt(pow(third_vector_x, 2) + pow(third_vector_y, 2));

    first_scalar_product = first_vector_x*second_vector_x + first_vector_y*second_vector_y;
    second_scalar_product = third_vector_x*(-1)*second_vector_x + third_vector_y*(-1)*second_vector_y;

    first_angle = acos(first_scalar_product / (first_length*second_length));
    second_angle = acos(second_scalar_product / (third_length*second_length));

    if (first_angle < acos(0) && second_angle < acos(0)) result++;

    return result;
}

int main(void) {

    stack_node *top_element;

    point **array_of_points;

    int count_of_vertexes; 
    double mass_center_x, mass_center_y;
    int current_x, current_y;
    int i;

    scanf("%d %lf %lf", &count_of_vertexes, &mass_center_x, &mass_center_y);
 
    array_of_points = (point**) calloc(count_of_vertexes, sizeof(point*));

    for (i=0; i<count_of_vertexes; i++) {
        scanf("%d %d", &current_x, &current_y);

        array_of_points[i] = malloc(sizeof(point));
        array_of_points[i]->x = current_x;
        array_of_points[i]->y = current_y;

    }

    top_element = get_convex_hull(array_of_points, count_of_vertexes);
    printf("%d", get_count_of_good_positions(top_element, mass_center_x, mass_center_y));

    for (i=0; i<count_of_vertexes; i++) {
        free(array_of_points[i]);
    }

    free(array_of_points);


    return 0;
}
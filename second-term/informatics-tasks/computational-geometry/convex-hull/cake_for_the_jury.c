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



double shoelace_summand(point *first_point, point *second_point) {
    return (first_point->x)*(second_point->y) - (second_point->x)*(first_point->y);
}

double calculate_square_of_whole_polygon(point **array_of_points, int count_of_points) {
    
    double square = shoelace_summand(array_of_points[count_of_points-1], array_of_points[0]);

    int i;

    for (i=1; i<count_of_points; i++) square += shoelace_summand(array_of_points[i-1], array_of_points[i]);

    return fabs(square/2);

}

double calculate_square_of_triangle(point *p1, point *p2, point *p3) {
    return (0.5)*(fabs((p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x)));
}

void get_ends_of_cuts(point **array_of_points, point **cut_ends, stack_node *stack_element, double square_per_jury, int count_of_points, int count_of_jury) {

    
    double current_square_accumulated, current_triangle_square;
    double square_needed;
    double triangle_part_to_cut_ratio;

    double current_cut_end_x, current_cut_end_y;
    
    int i;
    
    point *new_point;
    point *pivot_point = top(stack_element);
    
    pop(&stack_element);

    for (i=0; i<count_of_jury-1; i++) {
        current_square_accumulated = 0.0;
        while (fabs(current_square_accumulated - square_per_jury) > diff) {
            current_triangle_square = calculate_square_of_triangle(pivot_point, top(stack_element), second_at_top(stack_element));

            if (current_square_accumulated + current_triangle_square - square_per_jury < diff) {
                cut_ends[i] = second_at_top(stack_element);
                current_square_accumulated += current_triangle_square;
                pop(&stack_element);

            } else if (current_square_accumulated + current_triangle_square > square_per_jury) {
                square_needed = square_per_jury - current_square_accumulated;
                triangle_part_to_cut_ratio = square_needed / current_triangle_square;
                
                current_cut_end_x = (top(stack_element)->x + (second_at_top(stack_element)->x - top(stack_element)->x)*triangle_part_to_cut_ratio);
                current_cut_end_y = (top(stack_element)->y + (second_at_top(stack_element)->y - top(stack_element)->y)*triangle_part_to_cut_ratio);

                new_point = (point*) malloc(sizeof(point));
                new_point->x = current_cut_end_x;
                new_point->y = current_cut_end_y;

                cut_ends[i] = new_point;

                pop(&stack_element);
                push(&stack_element, new_point);

                current_square_accumulated += square_needed;

            } 
            
            
        }

    }
}

void print_cuts(point **cut_ends, point *pivot_point, int count_of_cuts) {
    int i;

    for (i=0; i<count_of_cuts; i++) {
        printf("%.10lf %.10lf %.10lf %.10lf\n", pivot_point->x, pivot_point->y, cut_ends[i]->x, cut_ends[i]->y);
    }
}

int main(void) {

    stack_node *top_element = NULL;

    point **array_of_points, **cut_ends;

    double current_x, current_y;
    double square_per_jury;

    int count_of_jury, count_of_points;
    int i;

    scanf("%d %d", &count_of_jury, &count_of_points);

    array_of_points = (point**) calloc(count_of_points, sizeof(point*));
    cut_ends = (point**) calloc(count_of_jury-1, sizeof(point*));

    for (i=0; i<count_of_points; i++) {
        scanf("%lf %lf", &current_x, &current_y);
        
        array_of_points[i] = (point*) malloc(sizeof(point));
        array_of_points[i]->x = current_x;
        array_of_points[i]->y = current_y;

        push(&top_element, array_of_points[i]);
        
    }

    square_per_jury = calculate_square_of_whole_polygon(array_of_points, count_of_points) / count_of_jury;
    get_ends_of_cuts(array_of_points, cut_ends, top_element, square_per_jury, count_of_points, count_of_jury);
    print_cuts(cut_ends, array_of_points[count_of_points-1], count_of_jury-1);


    for (i=0; i<count_of_points; i++) free(array_of_points[i]);
    free(array_of_points);


    return 0;
}
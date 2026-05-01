#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define DIFF 1e-9
#define PI 3.14159265358979323846

typedef struct point {
    double x;
    double y;
} point;

typedef struct line_equation {
    double a;
    double b;
    double c;
} line_equation; 

double calculate_dist_between_points(point *p1, point *p2) {
    return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

void get_normal_to_edge(point *first_point, point *second_point, point *normal) {
    double diff_on_x, diff_on_y, distance;

    diff_on_x = second_point->x - first_point->x;
    diff_on_y = second_point->y - first_point->y;
    distance = calculate_dist_between_points(first_point, second_point);
    
    normal->x = diff_on_y / distance;
    normal->y = -diff_on_x / distance;
}

void build_new_polyangle(point **input_array, point **output_array, int count_of_points, int *new_count_of_points, double radius) {

    line_equation **shifted_edges;
    line_equation *first_line, *second_line;

    point *first_point, *second_point, *normal;

    double a, b, c;
    double determinant, putting_point_in_line_equation_value;
    double new_x, new_y;

    int flag_is_point_inside_of_input_polyangle;
    int new_polyangle_size = 0;
    int i, j, k;

    shifted_edges = (line_equation**) calloc(count_of_points, sizeof(line_equation*));
    normal = (point*) malloc(sizeof(point));

    for (i=0; i<count_of_points; i++) {
        first_point = input_array[i];
        second_point = input_array[(i+1) % count_of_points];

        get_normal_to_edge(first_point, second_point, normal);

        a = normal->x;
        b = normal->y;

        c = -(a*(first_point->x + a*radius) + b*(first_point->y + b*radius));

        shifted_edges[i] = (line_equation*) malloc(sizeof(line_equation));
        shifted_edges[i]->a = a;
        shifted_edges[i]->b = b;
        shifted_edges[i]->c = c;

    }

    for (i=0; i<count_of_points; i++) {
       
        for (j=i+1; j<count_of_points; j++) {
            
            first_line = shifted_edges[i];
            second_line = shifted_edges[j];   

            determinant = (first_line->a)*(second_line->b) - (second_line->a)*(first_line->b);

            if (fabs(determinant) >= DIFF) {

                flag_is_point_inside_of_input_polyangle = 1;

                new_x = ((first_line->b)*(second_line->c) - (second_line->b)*(first_line->c)) / determinant;
                new_y = ((second_line->a)*(first_line->c) - (first_line->a)*(second_line->c)) / determinant;

                for (k=0; k<count_of_points && flag_is_point_inside_of_input_polyangle; k++) {
                    putting_point_in_line_equation_value = (shifted_edges[k]->a)*(new_x) + (shifted_edges[k]->b)*(new_y) + shifted_edges[k]->c;
                    if (putting_point_in_line_equation_value < -DIFF) flag_is_point_inside_of_input_polyangle = 0;
                }

                if (flag_is_point_inside_of_input_polyangle) {
                    
                    output_array[new_polyangle_size] = (point*) malloc(sizeof(point));
                    output_array[new_polyangle_size]->x = new_x;
                    output_array[new_polyangle_size]->y = new_y;

                    new_polyangle_size++;
                }
            }
        }
    }

    (*new_count_of_points) = new_polyangle_size;

    for (i=0; i<count_of_points; i++) free(shifted_edges[i]);
    free(shifted_edges);
    free(normal);

}

void find_most_distanced_points_of_polyangle(point **points_in_polyangle, point **first_output_point, point **second_output_point, int count_of_points_in_polyangle) {
    
    double max_dist_between_points = -1.0;
    double current_distance;
    point *first_point, *second_point;
    
    int i, j;

    for (i=0; i<count_of_points_in_polyangle; i++) {
        for (j=i+1; j<count_of_points_in_polyangle; j++) {
            current_distance = calculate_dist_between_points(points_in_polyangle[i], points_in_polyangle[j]);
            if (current_distance > max_dist_between_points) {
                max_dist_between_points = current_distance;

                first_point = points_in_polyangle[i];
                second_point = points_in_polyangle[j];
            }
        }
    }


    (*first_output_point) = first_point;
    (*second_output_point) = second_point;
}


int main(void) {

    point **array_of_points, **new_array_of_points;
    point *first_carpet_center_point=NULL, *second_carpet_center_point=NULL;

    int count_of_points, new_count_of_points;
    int i;

    double current_x, current_y;
    double square_of_two_carpets; 
    double radius;

    scanf("%d %lf", &count_of_points, &radius);

    array_of_points = (point**) calloc(count_of_points, sizeof(point*));
    new_array_of_points = (point**) calloc(count_of_points, sizeof(point*));

    square_of_two_carpets = 2*PI*pow(radius, 2);

    for (i=0; i<count_of_points; i++) {
        scanf("%lf %lf", &current_x, &current_y);

        array_of_points[i] = (point*) malloc(sizeof(point));
        array_of_points[i]->x = current_x;
        array_of_points[i]->y = current_y;

    }

    build_new_polyangle(array_of_points, new_array_of_points, count_of_points, &new_count_of_points, radius);
    find_most_distanced_points_of_polyangle(new_array_of_points, &first_carpet_center_point, &second_carpet_center_point, new_count_of_points);

    printf("%.5lf %.5lf %.5lf %.5lf", first_carpet_center_point->x, first_carpet_center_point->y, second_carpet_center_point->x, second_carpet_center_point->y);


    for (i=0; i<count_of_points; i++) free(array_of_points[i]);
    for (i=0; i<new_count_of_points; i++) free(new_array_of_points[i]);

    free(array_of_points);
    free(new_array_of_points);


    return 0;
}
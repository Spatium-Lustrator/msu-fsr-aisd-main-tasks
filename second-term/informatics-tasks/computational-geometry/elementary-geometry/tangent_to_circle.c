#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define diff 1e-6

typedef struct tangent_point {

    double x;
    double y;

} tangent_point;

void get_tangent_points(tangent_point **t_points, int *result_count, double point_x, double point_y, double center_x, double center_y, double radius) {

    double shifted_a, shifted_b, shifted_c, shifted_discriminant_root;
    double first_tan_point_x, first_tan_point_y;
    double second_tan_point_x, second_tan_point_y;


    if (fabs(pow(radius, 2) - pow(point_x-center_x, 2) - pow(point_y-center_y, 2)) < diff) {
        (*result_count) = 1;

        t_points[0]->x = point_x;
        t_points[0]->y = point_y;
    } else if (fabs(pow(radius, 2) > pow(point_x-center_x, 2) + pow(point_y-center_y, 2))) {
        (*result_count) = 0;
    } else {
        (*result_count) = 2;

        shifted_a = pow(point_x-center_x, 2) + pow(point_y-center_y, 2);
        shifted_b = (-2)*(pow(radius, 2))*(point_x - center_x);
        shifted_c = pow(radius, 4) - (pow(radius, 2))*(pow(point_y-center_y, 2));

        shifted_discriminant_root = sqrt(pow(shifted_b, 2) - 4*shifted_a*shifted_c);

        first_tan_point_x = (((-1)*shifted_b + shifted_discriminant_root)) / (2*shifted_a) + center_x;
        second_tan_point_x = (((-1)*shifted_b - shifted_discriminant_root) / (2*shifted_a)) + center_x;

        first_tan_point_y = (((pow(radius, 2)) - (point_x-center_x)*(first_tan_point_x - center_x)) / (point_y-center_y)) + center_y;
        second_tan_point_y = (((pow(radius, 2)) - (point_x-center_x)*(second_tan_point_x - center_x)) / (point_y-center_y)) + center_y;

        t_points[0]->x = first_tan_point_x;
        t_points[0]->y = first_tan_point_y;

        t_points[1]->x = second_tan_point_x;
        t_points[1]->y = second_tan_point_y;
        
    }

}


int main(void) {

    tangent_point **tangent_points;

    int result_count_of_tangent_points;
    int i;

    double center_x, center_y, radius;
    double point_x, point_y;

    tangent_points = (tangent_point**) calloc(2, sizeof(tangent_point*));
    tangent_points[0] = (tangent_point*) malloc(sizeof(tangent_point));
    tangent_points[1] = (tangent_point*) malloc(sizeof(tangent_point));

    scanf("%lf %lf %lf", &center_x, &center_y, &radius);
    scanf("%lf %lf", &point_x, &point_y);

    get_tangent_points(tangent_points, &result_count_of_tangent_points, point_x, point_y, center_x, center_y, radius);

    printf("%d\n", result_count_of_tangent_points);

    for (i=0; i<result_count_of_tangent_points; i++) {
        printf("%lf %lf\n", tangent_points[i]->x, tangent_points[i]->y);
    }


    free(tangent_points[0]);
    free(tangent_points[1]);
    free(tangent_points);




    return 0;
}
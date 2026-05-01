#include <stdio.h>
#include <math.h>

#define diff 1e-6

double min(double val1, double val2) {
    return val1>val2 ? val2: val1;
}

double max(double val1, double val2) {
    return val1<val2 ? val2: val1;
}

int does_point_belong_to_a_segment(double p_x, double p_y, double segm_s_x, double segm_s_y, double segm_e_x, double segm_e_y) {
    
    double start_to_point_x, start_to_point_y;
    double start_to_end_x, start_to_end_y;
    double cross_product;
    
    start_to_point_x = p_x - segm_s_x;
    start_to_point_y = p_y - segm_s_y;

    start_to_end_x = segm_e_x - segm_s_x;
    start_to_end_y = segm_e_y - segm_s_y;
    
    cross_product = start_to_point_x*start_to_end_y - start_to_point_y*start_to_end_x;

    return ((fabs(cross_product) < diff) && (min(segm_s_x, segm_e_x) <= p_x) && (p_x <= max(segm_e_x, segm_s_x)) && (min(segm_s_y, segm_e_y) <= p_y) && (p_y <= max(segm_e_y, segm_s_y)));

}


int main(void) {

    double point_x, point_y;
    double segment_start_x, segment_start_y;
    double segment_end_x, segment_end_y;

    scanf("%lf %lf %lf %lf %lf %lf", &point_x, &point_y, &segment_start_x, &segment_start_y, &segment_end_x, &segment_end_y); 

    printf("%s", does_point_belong_to_a_segment(point_x, point_y, segment_start_x, segment_start_y, segment_end_x, segment_end_y) ? "YES": "NO");

    return 0;
}
#include <stdio.h>
#include <math.h>

#define diff 1e-6

double min(double val1, double val2) {
    return val1>val2 ? val2: val1;
}

double max(double val1, double val2) {
    return val1<val2 ? val2: val1;
}

double direction(double p1_x, double p1_y, double p2_x, double p2_y, double p3_x, double p3_y) {
    
    double vector_from_p1_to_p2_x, vector_from_p1_to_p2_y;
    double vector_from_p1_to_p3_x, vector_from_p1_to_p3_y;

    vector_from_p1_to_p2_x = p2_x - p1_x;
    vector_from_p1_to_p2_y = p2_y - p1_y;

    vector_from_p1_to_p3_x = p3_x - p1_x;
    vector_from_p1_to_p3_y = p3_y - p1_y;

    return vector_from_p1_to_p2_x*vector_from_p1_to_p3_y - vector_from_p1_to_p2_y*vector_from_p1_to_p3_x;

}

int on_segment(double p1_x, double p1_y, double p2_x, double p2_y, double p3_x, double p3_y) {
    return (min(p1_x, p2_x) <= p3_x) && (p3_x <= max(p1_x, p2_x)) && (min(p1_y, p2_y) <= p3_y) && (p3_y <= max(p1_y, p2_y));
}


int does_segments_intersect(double first_segment_start_x, double first_segment_start_y, double first_segment_end_x, double first_segment_end_y, double second_segment_start_x, double second_segment_start_y, double second_segment_end_x, double second_segment_end_y) {

    double d1, d2, d3, d4;

    d1 = direction(second_segment_start_x, second_segment_start_y, second_segment_end_x, second_segment_end_y, first_segment_start_x, first_segment_start_y);
    d2 = direction(second_segment_start_x, second_segment_start_y, second_segment_end_x, second_segment_end_y, first_segment_end_x, first_segment_end_y);
    d3 = direction(first_segment_start_x, first_segment_start_y, first_segment_end_x, first_segment_end_y, second_segment_start_x, second_segment_start_y);
    d4 = direction(first_segment_start_x, first_segment_start_y, first_segment_end_x, first_segment_end_y, second_segment_end_x, second_segment_end_y);

    if (((d1 > diff && d2 < -diff) || (d1 < -diff && d2 > diff)) && ((d3 > diff && d4 < -diff) || (d3 < -diff && d4 > diff))) {
        return 1;
    } else if (fabs(d1) < diff && on_segment(second_segment_start_x, second_segment_start_y, second_segment_end_x, second_segment_end_y, first_segment_start_x, first_segment_start_y)) {
        return 1;
    } else if (fabs(d2) < diff && on_segment(second_segment_start_x, second_segment_start_y, second_segment_end_x, second_segment_end_y, first_segment_end_x, first_segment_end_y)) {
        return 1;
    } else if (fabs(d3) < diff && on_segment(first_segment_start_x, first_segment_start_y, first_segment_end_x, first_segment_end_y, second_segment_start_x, second_segment_start_y)) {
        return 1;
    } else if (fabs(d4) < diff && on_segment(first_segment_start_x, first_segment_start_y, first_segment_end_x, first_segment_end_y, second_segment_end_x, second_segment_end_y)) {
        return 1;
    } else {
        return 0;
    }


}


int main(void) {

    double first_segment_start_x, first_segment_start_y;
    double first_segment_end_x, first_segment_end_y;
    double second_segment_start_x, second_segment_start_y;
    double second_segment_end_x, second_segment_end_y;

    scanf("%lf %lf %lf %lf", &first_segment_start_x, &first_segment_start_y, &first_segment_end_x, &first_segment_end_y);
    scanf("%lf %lf %lf %lf", &second_segment_start_x, &second_segment_start_y, &second_segment_end_x, &second_segment_end_y);

    printf("%s", does_segments_intersect(first_segment_start_x, first_segment_start_y, first_segment_end_x, first_segment_end_y, second_segment_start_x, second_segment_start_y, second_segment_end_x, second_segment_end_y) ? "YES": "NO");

    return 0;
}
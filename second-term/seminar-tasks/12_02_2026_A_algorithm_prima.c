#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point_of_interest {
    double x; 
    double y;
};


double calc_distance(struct point_of_interest *point1, struct point_of_interest *point2) {
    double x1, y1, x2, y2; 

    x1 = point1->x;
    y1 = point1->y;
    x2 = point2->x;
    y2 = point2->y;

    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}


int main(void) {
    int width, height, num, i, j, *visited;
    int cur_vertex=0, cur_vertex_with_min_dist;
    struct point_of_interest **p_o_is, *cur_point;
    double **adjacency_matrix, *distances;
    double cur_x, cur_y, cur_dist, mst_w=0.0, max_dist=0.0, cur_min_dist; 


    scanf("%d %d %d", &height, &width, &num);
    num++;

    p_o_is = (struct point_of_interest**) malloc(sizeof(struct point_of_interest*)*num);
    adjacency_matrix = (double**) malloc(sizeof(double*)*num);
    visited = (int*) calloc(num, sizeof(int));
    distances = (double*) calloc(num, sizeof(double));

    for (i=0; i<num-1; i++) { 
        scanf("%lf %lf", &cur_y, &cur_x);
        cur_point = (struct point_of_interest*) malloc(sizeof(struct point_of_interest*));
        cur_point->x = cur_x;
        cur_point->y = cur_y;

        p_o_is[i] = cur_point;
        adjacency_matrix[i] = (double*) malloc(sizeof(double)*num);
    }

    cur_point = (struct point_of_interest*) malloc(sizeof(struct point_of_interest*));
    cur_point->x = width/2;
    cur_point->y = 0;

    p_o_is[i] = cur_point;
    adjacency_matrix[i] = (double*) malloc(sizeof(double)*num);

    for (i=0; i<num; i++) {
        for (j=i+1; j<num; j++) {
            cur_dist = calc_distance(p_o_is[i], p_o_is[j]);
            adjacency_matrix[i][j] = cur_dist;
            adjacency_matrix[j][i] = cur_dist;

            if (max_dist < cur_dist) max_dist = cur_dist;
        }
    }

    for (i=1; i<num; i++) distances[i] = max_dist*2;

    for (i=0; i<num-1; i++) {
        visited[cur_vertex] = 1;
        cur_min_dist = max_dist*2;
        for (j=0; j<num; j++) {
            cur_dist = adjacency_matrix[cur_vertex][j];
            if (distances[j] > cur_dist && cur_vertex != j) {
                distances[j] = cur_dist;
            }

            if (cur_min_dist > cur_dist && visited[j] != 1) {
                cur_min_dist = cur_dist;
                cur_vertex_with_min_dist = j;
            }
        }
        cur_vertex = cur_vertex_with_min_dist;
    }

    for (i=0; i<num; i++) {
        mst_w += distances[i];
    }
    
   
    printf("%lf", mst_w);


    for (i=0; i<num; i++) { 
        free(p_o_is[i]);
        free(adjacency_matrix[i]);
    }
    free(p_o_is);
    free(adjacency_matrix);
    free(visited);
    free(distances);

    return 0;
}
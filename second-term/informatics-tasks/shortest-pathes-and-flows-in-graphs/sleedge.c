// So, yeah... Here can be edges with zero weight

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct city {
    int time_of_preparation;
    int speed;

} city;

void update_neighbors_costs(double **adjacency_matrix, double *distances, int *previous,int current_vertex, int count_of_vertexes) {
    double current_cost = distances[current_vertex], new_cost;
    int l;

    for (l=0; l<count_of_vertexes; l++) {
        new_cost = current_cost + adjacency_matrix[current_vertex][l];
        if (adjacency_matrix[current_vertex][l] > -0.95 && new_cost < distances[l]) {
            // printf("cost%lf %lf", new_cost, distances[l]);
            previous[l] = (current_vertex-1) % count_of_vertexes;
            distances[l] = new_cost;
        }
    }
}

int find_node_with_lowest_cost(int *processed, double *distances, int count_of_vertexes) {
    double current_min_distance = INFINITY;
    int result = -1, i;

    for (i=0; i<count_of_vertexes; i++) {
        if (current_min_distance > distances[i] && !processed[i]) {
            result = i;
            current_min_distance = distances[i];
        }
    }

    return result;
}

void find_shortest_path_between_vertexes(double **adjacency_matrix, int *processed, double *distances, int *previous,int count_of_vertexes,int start_index) {
    int current_vertex=start_index;
    // printf("^!%d ", current_vertex);
    while (current_vertex >= 0) {
        // printf("^^^%d ", current_vertex);
        update_neighbors_costs(adjacency_matrix, distances, previous, current_vertex, count_of_vertexes);
        processed[current_vertex] = 1;
        current_vertex = find_node_with_lowest_cost(processed, distances, count_of_vertexes);
        // printf("NEW CURRENT VERTEX %d", current_vertex);

    }
    
}


int main(void) {

    city **cities;

    double **adjacency_matrix, *distances, **raw_matrix;
    double current_length;
    int *processed, *previous;
    int count_of_cities;
    int total_vertexes;
    int current_time_of_preparation, current_speed;
    int current_from, current_to;
    int i, j, k;
    int cur_speed, cur_time_smenit;

    scanf("%d", &count_of_cities);

    total_vertexes = 1 + count_of_cities*count_of_cities;
    cities = (city**) calloc(count_of_cities, sizeof(city*));
    adjacency_matrix = (double**) malloc(sizeof(double*)*(total_vertexes));
    raw_matrix = (double**) malloc(sizeof(double*)*count_of_cities);
    processed = (int*) calloc(total_vertexes, sizeof(int));
    distances = (double*) calloc(total_vertexes, sizeof(double));
    previous = (int*) calloc(total_vertexes, sizeof(int));

    for (i=1; i<total_vertexes; i++) distances[i] = INFINITY;

    for (i=0; i<total_vertexes; i++) {
        adjacency_matrix[i] = (double*) calloc(total_vertexes, sizeof(double));
        for (j=0; j<total_vertexes; j++) {
            adjacency_matrix[i][j] = -1.0;
        }
    }


    for (i=0; i<count_of_cities; i++) {
        raw_matrix[i] = calloc(count_of_cities, sizeof(double));
        previous[i] = -1;
        scanf("%d %d", &current_time_of_preparation, &current_speed);
        
        cities[i] = (city*) malloc(sizeof(city));

        cities[i]->speed = current_speed;
        cities[i]->time_of_preparation = current_time_of_preparation;

    }

    for (i=0; i<count_of_cities-1; i++) {
        scanf("%d %d %lf", &current_from, &current_to, &current_length);
        raw_matrix[current_from-1][current_to-1] = current_length;
        raw_matrix[current_to-1][current_from-1] = current_length;
    }



    for (i=0; i<count_of_cities; i++) {
        cur_speed = cities[i]->speed;
        cur_time_smenit = cities[i]->time_of_preparation;

        for (k=0; k<count_of_cities; k++) {
            for (j=0; j<count_of_cities; j++) {
                if (raw_matrix[k][j]) {
                    // printf("!!%lf %d %d!\n", raw_matrix[k][j]/cur_speed, k, j);
                    adjacency_matrix[k+1+i*count_of_cities][j+1+i*count_of_cities] = raw_matrix[k][j] / cur_speed;
                    
                }
                
            }

            if (i!=k) {
                printf("!%d %d %d %d %d\n", cities[k]->time_of_preparation, k+1+i*count_of_cities, k+1+k*count_of_cities, k, i);
                // Вот тут расчет был неправильный, у нас должна быть не диагональ/ Да не, вроде норм, но я не понимаю, почему диагональ нулями заводится
                // adjacency_matrix[k+1+i*count_of_cities][k+1+k*count_of_cities] = cur_time_smenit;
                adjacency_matrix[k+1+i*count_of_cities][k+1+k*count_of_cities] = cities[k]->time_of_preparation;
                adjacency_matrix[k+1+k*count_of_cities][k+1+i*count_of_cities] = cities[k]->time_of_preparation;
                // k=1 i=0
            }
        }

        adjacency_matrix[0][1+i*count_of_cities] = 0.0;
        adjacency_matrix[1+i*count_of_cities][0] = 0.0;
    }

    for (int j=0; j<total_vertexes; j++) {
        for (int k=0; k<total_vertexes; k++) {
            printf("%lf ", adjacency_matrix[j][k]);

        }
        printf("\n");
    }

    find_shortest_path_between_vertexes(adjacency_matrix, processed, distances, previous, total_vertexes, 0);

    for (j=0; j<total_vertexes; j++) {
        if (distances[j] == INFINITY) {
            printf("INF ");
        } else {
            printf("%lf ", distances[j]);

        }
    }

    // Надо это самое, прогнать дейкстру в ручную

    // for (i=0; i<total_vertexes; i++) {
    //     free(adjacency_matrix[i]);
    // }

    // for (i=0; i<count_of_cities; i++) {
    //     free(raw_matrix[i]);
    //     // free(cities[i]);
    // }


    // free(adjacency_matrix);
    // // free(raw_matrix);
    // free(cities);
    // free(previous);
    // free(distances);
    // free(processed);





    return 0;
}
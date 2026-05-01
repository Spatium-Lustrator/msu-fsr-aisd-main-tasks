#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct city {
    int time_of_preparation;
    int speed;

} city;

double min(double n1, double n2) {
    if (n1 > n2) {
        return n2;
    } else {
        return n1;
    }
}

int calc_time_with_no_transfer(int **adjacency_matrix, city **cities, int vertex_from, int vertex_to) {
    return cities[vertex_to]->time_of_preparation + (adjacency_matrix[vertex_from][vertex_to] / cities[vertex_to]->speed);
}

void update_neighbors_costs(int **adjacency_matrix, int *previous, double *distances, city **cities, int current_vertex, int count_of_vertexes) {
    double current_cost = distances[current_vertex], new_cost;
    int l, v;

    for (l=0; l<count_of_vertexes; l++) {
        if (adjacency_matrix[current_vertex][l] > 0 && previous[l] == -1) {
            previous[l] = current_vertex;
            new_cost = calc_time_with_no_transfer(adjacency_matrix, cities, current_vertex, l);
            for (v=previous[l]; v>=0 && previous[v]>=0; v=previous[v]) {
                new_cost += min(distances[v], (adjacency_matrix[previous[v]][v] / cities[l]->speed)+cities[l]->time_of_preparation);
            }

            if (new_cost < distances[l]) {
                distances[l] = new_cost;
            }
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

void find_shortest_path_between_vertexes(int **adjacency_matrix, city **cities, int *previous, int *processed, double *distances, int count_of_vertexes,int start_index) {
    int current_vertex=start_index;

    while (current_vertex >= 0) {
        update_neighbors_costs(adjacency_matrix, previous, distances, cities, current_vertex, count_of_vertexes);
        processed[current_vertex] = 1;
        current_vertex = find_node_with_lowest_cost(processed, distances, count_of_vertexes);

    }
    

}

double find_max_time_in_shortest(double *distances, int *vertex_with_bad_time, int count_of_vertexes) {
    double max_time = 0;
    int i;

    for (i=0; i<count_of_vertexes; i++) {
        if (max_time < distances[i]) {
            max_time = distances[i];
            (*vertex_with_bad_time) = i;
        }
    }

    return max_time;
}



int main(void) {

    city **cities;

    double *distances;
    int **adjacency_matrix, *processed, *previous;
    int current_time_of_preparation, current_speed;
    int current_from, current_to, current_length;
    int count_of_cities, bad_vertex; 
    int i;

    scanf("%d", &count_of_cities);

    cities = (city**) calloc(count_of_cities, sizeof(city*));
    adjacency_matrix = (int**) calloc(count_of_cities, sizeof(int*));
    processed = (int*) calloc(count_of_cities, sizeof(int));
    distances = (double*) calloc(count_of_cities, sizeof(double));
    previous = (int*) calloc(count_of_cities, sizeof(int));

    for (i=1; i<count_of_cities; i++) distances[i] = INFINITY;

    for (i=0; i<count_of_cities; i++) {
        adjacency_matrix[i] = calloc(count_of_cities, sizeof(int));
        previous[i] = -1;

        scanf("%d %d", &current_time_of_preparation, &current_speed);
        cities[i] = (city*) malloc(sizeof(city));

        cities[i]->speed = current_speed;
        cities[i]->time_of_preparation = current_time_of_preparation;

    }

    for (i=0; i<count_of_cities-1; i++) {
        scanf("%d %d %d", &current_from, &current_to, &current_length);
        adjacency_matrix[current_from-1][current_to-1] = current_length;
        // adjacency_matrix[current_to-1][current_from-1] = current_length;

    }

    find_shortest_path_between_vertexes(adjacency_matrix, cities, previous, processed, distances, count_of_cities, 0);
    printf("%.10lf\n", find_max_time_in_shortest(distances, &bad_vertex, count_of_cities));

    for (i=bad_vertex; i>=0; i=previous[i]) {
        printf("%d ", i+1);
    }

    for (i=0; i<count_of_cities; i++) {
        free(adjacency_matrix[i]);
        free(cities[i]);
    }
    free(adjacency_matrix);
    free(cities);
    free(processed);
    free(distances);
    free(previous);




    return 0;
}
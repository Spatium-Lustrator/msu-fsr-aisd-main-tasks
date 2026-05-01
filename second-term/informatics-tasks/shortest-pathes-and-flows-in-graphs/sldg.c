#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct city {
    double time_to_achieve;
    int previous_city;       
    int start;

} city;

void depth_search(int **adjacency_matrix, int **distances, int start, int current_vertex, int previous, int count_of_vertexes){
    int i;

    for (i=0; i<count_of_vertexes; i++){
        if (i != previous && adjacency_matrix[current_vertex][i] > 0){
            distances[start][i] = distances[start][current_vertex] + adjacency_matrix[current_vertex][i];
            depth_search(adjacency_matrix, distances, start, i, current_vertex, count_of_vertexes);
        }
    }
}

int find_node_with_lowest_cost(city *cities, int* processed, int count_of_vertexes){
    double current_min_distances = INFINITY;
    int result = -1, i;
    
    for (i=0; i<count_of_vertexes; i++){
        if (processed[i] == 0 && cities[i].time_to_achieve < current_min_distances){
            current_min_distances = cities[i].time_to_achieve;
            result = i;
        }
    }

    return result;
}

void find_path_between_vertexes(city *cities, int *processed, int **distances, int *times_array, int *speeds_array, int count_of_vertexes){
    double current_distance, speed, current_time;
    int i, current_vertex;

    current_vertex = find_node_with_lowest_cost(cities, processed, count_of_vertexes);

    while (current_vertex >= 0) {
        processed[current_vertex] = -1;
        for (i=0; i<count_of_vertexes; i++) {
            if (distances[i][current_vertex] != -1) {
                current_distance = distances[i][current_vertex];
                speed = speeds_array[i];
                current_time = times_array[i] + current_distance/speed;

                if (cities[current_vertex].time_to_achieve + current_time < cities[i].time_to_achieve){
                        cities[i].time_to_achieve = cities[current_vertex].time_to_achieve + current_time;
                        cities[i].previous_city = current_vertex; 
                        cities[i].start = cities[current_vertex].start; 
                    }
            }
        }
    }
    
}

int find_maximum_time_to_achieve_city(city *cities, int count_of_vertexes){
    double maximum_time_to_achieve = -1.0; 
    int bad_city_index = 0, i;
    
    for (i=0; i<count_of_vertexes; i++){
        if (cities[i].time_to_achieve > maximum_time_to_achieve){
            maximum_time_to_achieve = cities[i].time_to_achieve;
            bad_city_index = i;
        }
    }

    return bad_city_index;
}

int* rebuild_way(city *cities, int bad_city_index, int *len, int n){
    int current_city_index = bad_city_index, *way;


    *len = 0;
    way = (int*)malloc(n*sizeof(int));
    
    while (current_city_index != -1){
        way[*len] = current_city_index;       
        (*len)++;       
        
        if (current_city_index == 0){
            current_city_index = -1;
        } else { 
            current_city_index = cities[current_city_index].previous_city;
        }
    }
    
    return way;
}

int main(void) {
    double maximimum_time_to_achieve_city;

    city *cities;

    int count_of_cities, count_of_cities_in_result_path;
    int i, j;
    int *processed, *cities_path;
    int bad_city_index;
    int *times_array, *speeds_array, **adjacency_matrix, **distances;
    int current_from, current_to, current_length;

    scanf("%d", &count_of_cities);

    times_array = (int*) malloc(count_of_cities*sizeof(int));        
    speeds_array = (int*) malloc(count_of_cities*sizeof(int));       
    adjacency_matrix = (int**) malloc(count_of_cities*sizeof(int*));
    distances = (int**) malloc(count_of_cities*sizeof(int*));
    cities = (city*) malloc(count_of_cities*sizeof(city));
    processed = (int*) calloc(count_of_cities, sizeof(int));

    for (i=0; i<count_of_cities; i++){
        adjacency_matrix[i] = (int*)calloc(count_of_cities, sizeof(int));
    }
    
    for (i=0; i<count_of_cities; i++){
        distances[i] = (int*) malloc(count_of_cities*sizeof(int));
        for (j=0; j<count_of_cities; j++){
            if (i == j){
                distances[i][j] = 0;
            } else{
                distances[i][j] = -1;       
            }
        }
    }
    
    for (i=0; i<count_of_cities; i++){
        scanf("%d %d", times_array+i, speeds_array+i);
    }

    for (i=0; i < count_of_cities-1; i++){
        scanf("%d %d %d", &current_from, &current_to, &current_length);
        adjacency_matrix[current_from-1][current_to-1] = current_length;
        adjacency_matrix[current_to-1][current_from-1] = current_length;
    }

    for (i=0; i<count_of_cities; i++){
        depth_search(adjacency_matrix, distances, i, i, -1, count_of_cities);
    }

    for (i=0; i<count_of_cities; i++){
        cities[i].time_to_achieve = INFINITY;    
        cities[i].previous_city = -1;      
        cities[i].start = i;     
    }

    cities[0].time_to_achieve = 0;           
    cities[0].previous_city = -1;
    cities[0].start = 0;
    
    find_path_between_vertexes(cities, processed, distances, times_array, speeds_array, count_of_cities);
    
    bad_city_index = find_maximum_time_to_achieve_city(cities, count_of_cities);
    maximimum_time_to_achieve_city = cities[bad_city_index].time_to_achieve;
    
    cities_path = rebuild_way(cities, bad_city_index, &count_of_cities_in_result_path, count_of_cities);

    printf("%.10f\n", maximimum_time_to_achieve_city);

    for (i=0; i<count_of_cities_in_result_path; i++) {
        printf("%d ", cities_path[i] + 1);
    }

    free(times_array);
    free(speeds_array);
    free(cities);
    free(processed);
    free(cities_path);
    for (i=0; i<count_of_cities; i++){
        free(adjacency_matrix[i]);
        free(distances[i]);
    }
    free(adjacency_matrix);
    free(distances);
    
    return 0;
}
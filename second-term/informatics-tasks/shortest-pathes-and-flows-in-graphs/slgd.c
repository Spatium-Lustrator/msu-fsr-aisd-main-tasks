#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct city{
    double time;
    int prev;       
    int start;

} city;

void depth_search(int start, int cur, int par, int **distances, int **g, int n){
    int i;
    for (i=0; i<n; i++){
        if (i != par && g[cur][i] > 0){
            distances[start][i] = distances[start][cur] + g[cur][i];
            depth_search(start, i, cur, distances, g, n);
        }
    }
}

int find_vertex_with_minimum_distances_index(city *cities, int *processed, int n){
    double min = INFINITY;
    int min_idx = -1, i;
    
    for (i=0; i<n; i++){
        if (processed[i] == 0 && cities[i].time < min){
            min = cities[i].time;
            min_idx = i;
        }
    }
    return min_idx;
}

void find_good_pathes_between_vertexes(city *cities, int *processed, int **distances, int *times_array, int *speeds_array, int n){
    int i, u, v;
    double d, speed, time;
    for (i=0; i<n; i++){
        u = find_vertex_with_minimum_distances_index(cities, processed, n);

        if (u != -1){
            processed[u] = 1;
            for (v=0; v<n; v++){
                if (distances[v][u] != -1){
                    d = distances[v][u];
                    speed = speeds_array[v];
                    time = times_array[v] + d / speed;
                    
                    if (cities[u].time + time < cities[v].time){
                        cities[v].time = cities[u].time + time;
                        cities[v].prev = u; 
                        cities[v].start = cities[u].start; 
                    }
                }
            }
        }
    }
}

int get_bad_city_index(city *cities, int n){
    double max_time_to_the_city = -1; 
    int bad_city_index = 0, i;
    
    for (i=0; i<n; i++){
        if (cities[i].time > max_time_to_the_city){
            max_time_to_the_city = cities[i].time;
            bad_city_index = i;
        }
    }
    return bad_city_index;
}

int* restore_path(city *cities, int bad_city_index, int *len, int n){
    int* way = (int*)malloc(n*sizeof(int));
    *len = 0;
    int cur = bad_city_index;
    
    while (cur != -1){
        way[*len] = cur;       
        (*len)++;       
        
        if (cur == 0)
            cur = -1;
        else 
            cur = cities[cur].prev;
    }
    
    return way;
}

int main(void) {
    int current_from, current_to, current_length;
    int len;
    int count_of_cities;
    int i, j;
    int bad_city_index;
    int *way;

    scanf("%d", &count_of_cities);

    int* times_array = (int*)malloc(count_of_cities*sizeof(int));        
    int* speeds_array = (int*)malloc(count_of_cities*sizeof(int));       
    int** adjacency_matrix = (int**)malloc(count_of_cities*sizeof(int*));
    int** distances = (int**)malloc(count_of_cities*sizeof(int*));
    city* cities = (city*)malloc(count_of_cities*sizeof(city));
    int* processed = (int*)calloc(count_of_cities, sizeof(int));


    for (i=0; i<count_of_cities; i++){
        adjacency_matrix[i] = (int*)calloc(count_of_cities, sizeof(int));
    }
    
    for (i=0; i<count_of_cities; i++){
        distances[i] = (int*)malloc(count_of_cities*sizeof(int));
        for (j=0; j<count_of_cities; j++){
            if (i == j)
                distances[i][j] = 0;     
            else
                distances[i][j] = -1;       
        }
    }
    
    
    
    for (i=0; i<count_of_cities; i++){
        scanf("%d %d", times_array + i, speeds_array + i);
    }

    for (i=0; i < count_of_cities-1; i++){
        scanf("%d %d %d", &current_from, &current_to, &current_length);
        adjacency_matrix[current_from-1][current_to-1] = current_length;
        adjacency_matrix[current_to-1][current_from-1] = current_length;
    }

    for (i=0; i<count_of_cities; i++){
        depth_search(i, i, -1, distances, adjacency_matrix, count_of_cities);
    }

    for (i=0; i<count_of_cities; i++){
        cities[i].time = INFINITY;    
        cities[i].prev = -1;      
        cities[i].start = i;     
    }
    cities[0].time = 0;           
    cities[0].prev = -1;
    cities[0].start = 0;
    
    find_good_pathes_between_vertexes(cities, processed, distances, times_array, speeds_array, count_of_cities);
    
    bad_city_index = get_bad_city_index(cities, count_of_cities);
    double max_time_to_the_city = cities[bad_city_index].time;
    
    
    way = restore_path(cities, bad_city_index, &len, count_of_cities);

    printf("%.10f\n", max_time_to_the_city);
    for (i=0; i<len; i++) {
        printf("%d ", way[i] + 1);
    }

    free(times_array);
    free(speeds_array);
    free(cities);
    free(processed);
    free(way);
    for (i=0; i<count_of_cities; i++){
        free(adjacency_matrix[i]);
        free(distances[i]);
    }
    free(adjacency_matrix);
    free(distances);
    
    return 0;
}
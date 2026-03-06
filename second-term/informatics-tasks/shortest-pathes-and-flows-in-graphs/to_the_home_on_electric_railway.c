#include <stdio.h>
#include <stdlib.h>

#define INFINITY 2147483647

typedef struct flight {
    int time_of_departure; 
    int time_of_arriving_to_the_new_station;
    int target_station;

    struct flight *next;

} flight;

void find_minimum_distances_to_stations(flight **flights_from_stations, int *minimum_arriving_time, int *processed, int count_of_stations) {
    flight *current_flight;
    int minimum_station, minimum_time, flag=1;
    int k;

    while (flag) {
        minimum_station = -1;
        minimum_time = INFINITY;

        for (k=0; k<count_of_stations; k++) {
            if (!processed[k] && minimum_arriving_time[k] < minimum_time) {
                minimum_time = minimum_arriving_time[k];
                minimum_station = k;
            }
        }

        if (minimum_time == INFINITY || minimum_station == -1) {
            flag = 0;
        } else {
            processed[minimum_station] = 1;
            current_flight = flights_from_stations[minimum_station];
            while (current_flight != NULL) {
                if (current_flight->time_of_departure >= minimum_arriving_time[minimum_station] && current_flight->time_of_arriving_to_the_new_station < minimum_arriving_time[current_flight->target_station]) {
                    minimum_arriving_time[current_flight->target_station] = current_flight->time_of_arriving_to_the_new_station;
                }

                current_flight = current_flight->next;
            }
        }
    }
}


int main(void) {
    int *minimum_arriving_time, *processed;
    int count_of_stations, target_station_index, count_of_trains, count_of_flights;
    int previous_station, previous_time, current_station, current_time;
    int i, j;
    flight **flights_from_stations, *current_flight, *next_flight;

    scanf("%d %d %d", &count_of_stations, &target_station_index, &count_of_trains);

    flights_from_stations = (flight**) calloc(count_of_stations, sizeof(flight*));
    minimum_arriving_time = (int*) calloc(count_of_stations, sizeof(int));
    processed = (int*) calloc(count_of_stations, sizeof(int));

    for (i=1; i<count_of_stations; i++) minimum_arriving_time[i] = INFINITY;

    for (i=0; i<count_of_trains; i++) {
        scanf("%d %d %d", &count_of_flights, &previous_station, &previous_time);
        previous_station--;
        for (j=1; j<count_of_flights; j++) {
            scanf("%d %d", &current_station, &current_time);
            current_flight = (flight*) malloc(sizeof(flight));
            current_flight->target_station = current_station-1;
            current_flight->time_of_departure = previous_time;
            current_flight->time_of_arriving_to_the_new_station = current_time;
            current_flight->next = flights_from_stations[previous_station];

            flights_from_stations[previous_station] = current_flight;

            previous_time = current_time;
            previous_station = current_station-1;
        }
        
    }

    find_minimum_distances_to_stations(flights_from_stations, minimum_arriving_time, processed, count_of_stations);

    if (minimum_arriving_time[target_station_index-1] == INFINITY) {
        printf("-1");
    } else {
        printf("%d", minimum_arriving_time[target_station_index-1]);
    }

    for (i=0; i<count_of_stations; i++) {
    
        current_flight = flights_from_stations[i];
        while (current_flight) {
            next_flight = current_flight->next;
            free(current_flight);
            current_flight = next_flight;
        }

    }

    free(flights_from_stations);
    free(minimum_arriving_time);
    free(processed);







    return 0;
}
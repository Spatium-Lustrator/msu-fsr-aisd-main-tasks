#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_out_of_three(int v1, int v2, int v3) {
    int min = v1;

    if (v2 < min) min = v2;
    if (v3 < min) min = v3;

    return min;
}

int levenshtein_distance(int **matrix, char *first_string, char *second_string, int first_string_length, int second_string_length, int insert_cost, int delete_cost, int replace_cost) {
    int i, j;

    for (i=1; i<first_string_length+1; i++) matrix[i][0] = matrix[i-1][0] + delete_cost;
    for (i=1; i<second_string_length+1; i++) matrix[0][i] = matrix[0][i-1] + insert_cost;

    for (i=1; i<first_string_length+1; i++) {
        for (j=1; j<second_string_length+1; j++) {
            if (first_string[i-1] == second_string[j-1]) {
                matrix[i][j] = matrix[i-1][j-1];
            } else {
                matrix[i][j] = min_out_of_three(matrix[i-1][j]+insert_cost, matrix[i][j-1]+delete_cost, matrix[i-1][j-1]+replace_cost);
            }
        }
    }

    return matrix[first_string_length][second_string_length];
}


int main(void) {

    int **levenshtein_distance_matrix;
    int insert_cost=2, delete_cost=1, replace_cost=1;
    int first_string_length, second_string_length;
    int i;

    char first_string[42], second_string[42];

    scanf("%s", &first_string);
    scanf("%s", &second_string);

    first_string_length = strlen(first_string);
    second_string_length = strlen(second_string);

    levenshtein_distance_matrix = (int**) calloc(first_string_length+1, sizeof(int*));
    for (i=0; i<first_string_length+1; i++) levenshtein_distance_matrix[i] = (int*) calloc(second_string_length+1, sizeof(int));

    printf("%d", levenshtein_distance(levenshtein_distance_matrix, first_string, second_string, first_string_length, second_string_length, insert_cost, delete_cost, replace_cost));

    for (i=0; i<first_string_length+1; i++) free(levenshtein_distance_matrix[i]);
    free(levenshtein_distance_matrix);

    return 0;
}
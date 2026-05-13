#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int v1, int v2) {
    return (v1>v2) ? v1: v2;
}

int min(int v1, int v2) {
    return (v1<v2) ? v1: v2;
}

void z_function(int *result, char *string) {
    int left=0, right=0;
    int i;

    for (i=1; i<strlen(string); i++) {
        
        result[i] = max(0, min(right-i, result[i-left]));

        while (i+result[i]<strlen(string) && string[result[i]] == string[i+result[i]]) result[i]++;

        if (i+result[i]>right) {
            left = i;
            right = i+result[i];
        }
    }
}

void read_string(char **output, int *current_max_length, int *current_actual_length) {

    char currenet_char = getchar();

    while (currenet_char != '\n' && currenet_char != EOF) {
        (*output)[(*current_actual_length)] = currenet_char;

        currenet_char = getchar();
        (*current_actual_length) += 1;

        if ((*current_actual_length) >= (*current_max_length)) {
            (*output) = realloc(*output, (*current_max_length)*2);
            (*current_max_length) = (*current_max_length)*2;
        }
    }

}

void build_up_string_for_searching(char *output, char *pattern, char *processed, int pattern_length, int procesed_length) {

    int i, j;

    for (i=0; i<pattern_length; i++) output[i] = pattern[i];

    output[i] = '#';
    i++;

    for (j=0; j<procesed_length; j++, i++) output[i] = processed[j];
    for (j=0; j<procesed_length; j++, i++) output[i] = processed[j];
    

}

int find_index_of_pattern(int *z_function_result, int z_function_result_length, int pattern_length) {
    int flag_found=0;
    int i;

    for (i=0; i<z_function_result_length && !flag_found; i++) flag_found = flag_found || (z_function_result[i] == pattern_length);

    return (flag_found) ? i-1 : -1;
}

int main(void) {

    int *z_function_result;

    int max_pattern_length=100, current_pattern_length=0; 
    int max_processed_length=100, current_processed_length=0;
    int result_of_finding_pattern;
    int i;

    char *pattern, *processed;
    char *string_to_z_function;

    pattern = (char*) calloc(max_pattern_length, sizeof(char));
    processed = (char*) calloc(max_processed_length, sizeof(char));

    read_string(&pattern, &max_pattern_length, &current_pattern_length);
    read_string(&processed, &max_processed_length, &current_processed_length);

    string_to_z_function = (char*) calloc(current_pattern_length+current_processed_length*2+1, sizeof(char));
    z_function_result = (int*) calloc(current_pattern_length+current_processed_length*2+1, sizeof(int));

    build_up_string_for_searching(string_to_z_function, pattern, processed, current_pattern_length, current_processed_length);

    z_function(z_function_result, string_to_z_function);

    result_of_finding_pattern = find_index_of_pattern(z_function_result, current_pattern_length+current_processed_length*2+1, current_pattern_length);

    printf("%d", (result_of_finding_pattern>=0) ? result_of_finding_pattern-current_pattern_length-1: result_of_finding_pattern);

    free(pattern);
    free(processed);
    free(string_to_z_function);
    free(z_function_result);

    return 0;
}
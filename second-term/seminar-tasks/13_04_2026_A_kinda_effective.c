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

int main(void) {
    char string[100] = {0};
    int *z_function_result;
    int j;

    scanf("%s", string);

    z_function_result = (int*) calloc(strlen(string), sizeof(int));

    z_function(z_function_result, string);

    for (j=0; j<strlen(string); j++) {
        printf("%d ", z_function_result[j]);
    }

    free(z_function_result);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void z_function(int *result, char *string) {
    int current_result;
    int i, j;

    for (i=1; i<strlen(string); i++) {
        current_result = 0;
        j = 0;
        while (string[i+j]==string[j] && j<strlen(string)) {
            current_result++;
            j++;
        }

        result[i] = current_result;
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
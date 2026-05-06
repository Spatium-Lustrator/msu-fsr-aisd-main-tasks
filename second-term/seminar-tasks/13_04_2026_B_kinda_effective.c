#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefix_function(int *result, char *string) {

    int i, k;

    for (i=1; i<strlen(string); i++) {
        
        k = result[i-1];

        while (k>0 && string[i] != string[k]) k = result[k-1];
        
        if (string[i] == string[k]) k++;

        result[i] = k;
    }


}

int main(void) {

    char string[1000] = {0};
    int *prefix_function_result;
    int j;

    scanf("%s", string);

    prefix_function_result = (int*) calloc(strlen(string), sizeof(int));

    prefix_function(prefix_function_result, string);

    for (j=0; j<strlen(string); j++) {
        printf("%d ", prefix_function_result[j]);
    }

    free(prefix_function_result);
    
    return 0;
}
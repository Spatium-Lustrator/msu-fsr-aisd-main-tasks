#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prefix_function(char *string, int position) {
    int k, j, flag=1;

    for (k=position; k>=0 && flag; k--) {
        flag = 0;
        for (j=1; j<=k; j++) {
            if (string[position-j+1] != string[k-j]) flag = 1;
        }
    }

    return k+1;
}

void prefix_function_whole_string(int *result, char *string) {
    int i;

    for (i=0; i<strlen(string); i++) result[i] = prefix_function(string, i);

}

int main(void) {

    char string[1000] = {0};
    int *prefix_function_result;
    int j;


    scanf("%s", string);

    prefix_function_result = (int*) calloc(strlen(string), sizeof(int));

    prefix_function_whole_string(prefix_function_result, string);

    for (j=0; j<strlen(string); j++) {
        printf("%d ", prefix_function_result[j]);
    }

    free(prefix_function_result);
    
    return 0;
}
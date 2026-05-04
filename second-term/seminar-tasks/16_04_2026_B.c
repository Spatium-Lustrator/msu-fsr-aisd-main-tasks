#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prefix_function(char *string, int position) {
    int k, j, flag=1;

    for (k=position; k>=0 && flag; k--) {
        flag = 0;
        for (j=1; j<=k && !flag; j++) {
        	flag = flag || (string[position-j+1] != string[k-j]);
        }
    }

    return k+1;
}

void prefix_function_whole_string(int *result, char *string) {
    int i;

    for (i=0; i<strlen(string); i++) result[i] = prefix_function(string, i);

}

int find_first_entry(int *prefix_function_result, int whole_string_length, int pattern_length) {
    int result = -1;
    int i;

    for (i=0; i<whole_string_length && prefix_function_result[i] != pattern_length; i++);
    if (i<whole_string_length) result = i-pattern_length*2;

    return result;
}

int main(void) {

    int *prefix_function_result;
    int pattern_length, text_length;
    int i;

    char current_char;
    char *whole_string;

    scanf("%d %d%c", &pattern_length, &text_length, &current_char);

    whole_string = (char*) calloc(pattern_length+text_length+1, sizeof(char));
    prefix_function_result = (int*) calloc(pattern_length+text_length+1, sizeof(int));

    for (i=0; i<pattern_length; i++) {
        scanf("%c", &current_char);

        whole_string[i] = current_char;
    }

    scanf("%c", &current_char);

    whole_string[i] = '#';
    i++;

    for (; i<pattern_length+1+text_length; i++) {
        scanf("%c", &current_char);

        whole_string[i] = current_char;
    }

    prefix_function_whole_string(prefix_function_result, whole_string);
    printf("%d", find_first_entry(prefix_function_result, pattern_length+text_length+1, pattern_length));

    free(whole_string);
    free(prefix_function_result);





    return 0;
}
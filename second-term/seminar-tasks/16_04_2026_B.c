#include <stdio.h>
#include <stdlib.h>

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

int main(void) {

    int pattern_length, 



    return 0;
}
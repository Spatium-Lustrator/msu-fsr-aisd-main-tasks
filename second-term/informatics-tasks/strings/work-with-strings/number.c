
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compare_two_strings(char string1[], char string2[]) {
    char string1_string2[201];
    char string2_string1[201];

    strcpy(string1_string2, string1); 
    strcpy(string2_string1, string2); 

    strcat(string1_string2, string2);
    strcat(string2_string1, string1);

    return strcmp(string2_string1, string1_string2) >= 0; 
}

void merge(char array[100][101], int left, int middle, int right) {

    int i, j, k;
    int count_in_left_part = middle - left + 1;
    int count_in_right_part = right - middle;

    char left_array[100][101], right_array[100][101];

    for (i = 0; i<count_in_left_part; i++) strcpy(left_array[i], array[left + i]);
    for (j = 0; j<count_in_right_part; j++) strcpy(right_array[j], array[middle + 1 + j]);

    i=0;
    j=0; 
    k=left;

    while (i<count_in_left_part && j<count_in_right_part) {
        if (compare_two_strings(left_array[i], right_array[j])) {
            strcpy(array[k], left_array[i]);
            i++;
        } else {
            strcpy(array[k], right_array[j]);
            j++;
        }

        k++;
    }

    while (i<count_in_left_part) {
        strcpy(array[k], left_array[i]);
        i++;
        k++;
    }

    while (j<count_in_right_part) {
        strcpy(array[k], right_array[j]);
        j++;
        k++;
    }

}

void merge_sort(char array[100][101], int left, int right) {
    if (left < right) {
      
        int middle = left + (right-left)/2;

        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);

        merge(array, left, middle, right);
    }
}


int main(void) {

    char nums[100][101];
    char current_num[101];

    int count_of_nums=0;
    int i;

    while (scanf("%s", current_num) != EOF && strlen(current_num) != 0) {
        strcpy(nums[count_of_nums], current_num);
        count_of_nums++;
    }

    merge_sort(nums, 0, count_of_nums-1);

    for (i=count_of_nums-1; i>=0; i--) printf("%s", nums[i]);

    return 0;
}
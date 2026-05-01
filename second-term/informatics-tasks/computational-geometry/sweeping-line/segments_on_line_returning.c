#include <stdio.h>
#include <stdlib.h>

typedef struct segment {
    long start;
    long end;
    int index;

} segment;

typedef struct stack_node {
    segment *segment_in_stack; 
    struct stack_node *next;

} stack_node;

void push(stack_node **top_element, segment *segment_to_push) {
    struct stack_node *new_element_to_push = (stack_node*) malloc(sizeof(stack_node)); 
    
    new_element_to_push->segment_in_stack = segment_to_push;
    new_element_to_push->next = *top_element;
    (*top_element) = new_element_to_push;
    
}

segment* top(stack_node *top_element) {
    return top_element->segment_in_stack;
}

void pop(stack_node **top_element) {

    stack_node *tmp = (*top_element);
    if (tmp) {
        (*top_element) = (*top_element)->next;
        free(tmp);
    }
    
}

void merge(segment **array, int left, int middle, int right) {

    int count_in_left_part = middle-left+1;
    int count_in_right_part = right-middle;
    int i, j, k;

    segment **left_array, **right_array;

    left_array = (segment**) calloc(count_in_left_part, sizeof(segment*));
    right_array = (segment**) calloc(count_in_right_part, sizeof(segment*));

    for (i=0; i<count_in_left_part; i++) left_array[i] = array[left+i];
    for (j=0; j<count_in_right_part; j++) right_array[j] = array[middle+j+1];

    i=0;
    j=0; 
    k=left;

    while (i<count_in_left_part && j<count_in_right_part) {

        if (left_array[i]->start < right_array[j]->start || (left_array[i]->start == right_array[j]->start && left_array[i]->end > right_array[j]->end)) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }

        k++;
    }

    while (i<count_in_left_part) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j<count_in_right_part) {
        array[k] = right_array[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}

void merge_sort(segment **array, int left, int right) {
    if (left < right) {
      
        int middle = left + (right-left)/2;

        merge_sort(array, left, middle);
        merge_sort(array, middle+1, right);

        merge(array, left, middle, right);
    }
}

void find_containing_segments_for_each(segment **segments, int *containers, int count_of_segments) {

    stack_node *top_element = NULL;

    int i;

    for (i=0; i<count_of_segments; i++) {
        while (top_element != NULL && top(top_element)->end < segments[i]->end) pop(&top_element);
        
        if (top_element != NULL && top(top_element)->end >= segments[i]->end) containers[segments[i]->index-1] = top(top_element)->index;

        push(&top_element, segments[i]);

    }

}

int main(void) {

    segment **segments;

    long current_start, current_end;

    int *containers;
    int count_of_segments;
    int i;

    scanf("%d", &count_of_segments);

    segments = (segment**) calloc(count_of_segments, sizeof(segment*));
    containers = (int*) calloc(count_of_segments, sizeof(int));

    for (i=0; i<count_of_segments; i++) {
        scanf("%ld %ld", &current_start, &current_end);

        segments[i] = (segment*) malloc(sizeof(segment));
        segments[i]->start = current_start;
        segments[i]->end = current_end;
        segments[i]->index = i+1;

    }

    merge_sort(segments, 0, count_of_segments-1);
    find_containing_segments_for_each(segments, containers, count_of_segments);

    for (i=0; i<count_of_segments; i++) printf("%d ", containers[i]);

    for (i=0; i<count_of_segments; i++) free(segments[i]);
    free(segments);
    free(containers);



    return 0;
}
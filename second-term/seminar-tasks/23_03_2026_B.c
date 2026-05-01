#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node {
    int value; 
    struct stack_node *next;

} stack_node;

void push(stack_node **top_element, int *value_to_push) {
    struct stack_node *new_element_to_push = (stack_node*) malloc(sizeof(stack_node)); 
    
    new_element_to_push->value = value_to_push;
    new_element_to_push->next = *top_element;
    (*top_element) = new_element_to_push;
    
}

int top(stack_node *top_element) {
    return top_element->value;
}

int* second_at_top(stack_node *top_element) {
    return top_element->next->value;
}

void clear(struct stack_node **top_element) {
    stack_node *current = *top_element;
    stack_node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *top_element = NULL;
}

void pop(stack_node **top_element) {

    stack_node *tmp = (*top_element);
    if (tmp) {
        (*top_element) = (*top_element)->next;
        free(tmp);
    }
    
}

int main(void) {

    int command = 1;

    while (command) {
        scanf("%d", &comm)


    }



    return 0;
}
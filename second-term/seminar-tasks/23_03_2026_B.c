#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node {
    int value; 
    struct stack_node *next;

} stack_node;

void push(stack_node **top_element, int value_to_push) {
    struct stack_node *new_element_to_push = (stack_node*) malloc(sizeof(stack_node)); 
    
    new_element_to_push->value = value_to_push;
    new_element_to_push->next = *top_element;
    (*top_element) = new_element_to_push;
    
}

int top(stack_node *top_element) {
    if (top_element) return top_element->value;
    return -1;
}

int second_at_top(stack_node *top_element) {
    if (top_element && top_element->next) return top_element->next->value;
    return -1;
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

int is_empty(stack_node *top_element) {
    if (top_element) return 0;
    return 1;
}

int main(void) {

    stack_node *top_element = NULL;

    int command = 1;
    int current_value;

    while (command) {
        scanf("%d", &command);

        switch (command) {
        case 1:
            scanf("%d", &current_value);
            push(&top_element, current_value);
            break;

        case 2:
            printf("%d\n", top(top_element));
            break;

        case 3:
            printf("%d\n", second_at_top(top_element));
            break;
        
        case 4:
            if (!is_empty(top_element)) {
                pop(&top_element);
            } else {
                printf("-1\n");
            }
            break;

        case 5:
            printf("%d\n", is_empty(top_element));
            break;

        case 6:
            clear(&top_element);
            break;
        
        default:
            break;
        }


    }



    return 0;
}
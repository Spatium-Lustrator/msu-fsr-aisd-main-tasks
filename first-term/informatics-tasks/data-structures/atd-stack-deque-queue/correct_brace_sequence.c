#include <stdio.h>
#include <stdlib.h>

struct list_node {
    char value;
    struct list_node *next; 

};

int is_it_open_brace(char symb) {
    if (symb == '{' || symb == '(' || symb == '[') {
        return 1;
    } else {
        return 0;
    }
}

int is_it_close_brace(char symb) {
    if (symb == '}' || symb == ')'|| symb == ']') {
        return 1;
    } else {
        return 0;
    }
}

char get_close_brace_for_current(char symb) {
    if (symb == '(') {
        return ')';
    } else if (symb == '{') {
        return '}';
    } else {
        return ']';
    }
}

void push(struct list_node **a, int *size, char val) {
    struct list_node *new_element_to_push = malloc(sizeof(struct list_node)); 
    
    new_element_to_push->value = val;
    new_element_to_push->next = *a;
    (*a) = new_element_to_push;
    
    (*size)++;

}

char top(struct list_node *a, int size) {
    if (size==0) {
        return '-';
    } else {
        return a->value;
    }
}

void clear(int *size, struct list_node **a) {
    struct list_node *current = *a;
    struct list_node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *a = NULL;
    *size = 0;
}

void pop(int *size, struct list_node **a) {
    if ((*size)>0) {
        (*size)--;
        (*a) = (*a)->next;
    }
}


int main(void) {

    char symbol;
    int size=0, bad_flag=0;
    struct list_node *sequence = NULL; 

    scanf("%c", &symbol);


    while ((is_it_open_brace(symbol) || is_it_close_brace(symbol)) && (!bad_flag)) {
        if (is_it_open_brace(symbol)) {
            push(&sequence, &size, symbol);
        } else if (is_it_close_brace(symbol)) {
            if (get_close_brace_for_current(top(sequence, size)) != symbol || size==0) {
                bad_flag = 1;
            } else {
                pop(&size, &sequence);
            }
        }

        scanf("%c", &symbol);
    }

    if (!bad_flag  && size==0) {
        printf("yes");
    } else {
        printf("no");
    }

    
    clear(&size, &sequence);

    return 0;
}
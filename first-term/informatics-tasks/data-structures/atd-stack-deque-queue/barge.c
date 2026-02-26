#include <stdio.h>
#include <stdlib.h>

struct stack_node {
    int value;
    struct stack_node *next; 

};


void push(struct stack_node **a, int val) {
    struct stack_node *new_element_to_push = malloc(sizeof(struct stack_node)); 
    
    new_element_to_push->value = val;
    new_element_to_push->next = *a;
    (*a) = new_element_to_push;
    
}

int top(struct stack_node *a) {
    return a->value;
}

void clear(struct stack_node **a) {
    struct stack_node *current = *a;
    struct stack_node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *a = NULL;
}

void pop( struct stack_node **a) {
    struct stack_node *tmp = (*a);
    (*a) = (*a)->next;
    free(tmp);
    
}


int main(void) {

    int n,k,p,i,j,block,fuel_type, total_count_of_barrels=0, no_error=1, max_barrel_count=0;
    char action;
    scanf("%d%d%d", &n, &k, &p);
    
    struct stack_node **barge = malloc(sizeof(struct stack_node)*k);
    for (j=0; j<k; j++) {
        barge[j] = NULL;
    }
    


    for (i=0; i<n && no_error; i++) {
        scanf(" %c%d%d", &action, &block, &fuel_type);
        if (action == '+') {
            if (total_count_of_barrels < p) {
                push(barge+block-1, fuel_type);
                total_count_of_barrels += 1;
            } else {
                no_error = 0;
            }
            
        } else if (action == '-') {
            if (barge[block-1] != NULL && top(barge[block-1]) == fuel_type) {
                pop(barge + block - 1);
                total_count_of_barrels -= 1;
            } else {
                no_error = 0;
            }
        }

        if (total_count_of_barrels > max_barrel_count) {
            max_barrel_count = total_count_of_barrels;
        }
    }

    if (no_error && total_count_of_barrels==0) {
        printf("%d", max_barrel_count);
    } else {
        printf("Error");
    }

    for (j=0; j<k; j++) {
        clear(barge + j);
    }

    free(barge);



    return 0;
}
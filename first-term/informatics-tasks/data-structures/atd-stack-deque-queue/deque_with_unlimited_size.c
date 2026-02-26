#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct deque_element {
    int value;
    struct deque_element *next;
};

void push_back(struct deque_element **first_element, struct deque_element **last_element, int *size, int val) {

    struct deque_element *new_element_to_push = malloc(sizeof(struct deque_element));

    new_element_to_push->value = val;
    new_element_to_push->next = NULL;

    if (*last_element != NULL) {
        (*last_element)->next = new_element_to_push;   
    } 
    (*last_element) = new_element_to_push;
    
    (*size)++;

    if (*size == 1) {
        (*first_element) = new_element_to_push;
    }

    printf("ok\n");
}

void push_front(struct deque_element **first_element, struct deque_element **last_element, int *size, int val) {

    struct deque_element *new_element_to_push = malloc(sizeof(struct deque_element));

    new_element_to_push->value = val;
    new_element_to_push->next = *first_element;

    (*first_element) = new_element_to_push;

    (*size)++;

    if ((*size) == 1) {
        (*last_element) = new_element_to_push;
    }

    printf("ok\n");
}



void front(struct deque_element **first_element, int *size) {
    if ((*size)==0) {
        printf("error\n");
    } else {
        printf("%d\n", (*first_element)->value);
    }
}

void back(struct deque_element **last_element, int *size) {
    if ((*size)==0) {
        printf("error\n");
    } else {
        printf("%d\n", (*last_element)->value);
    }
}

void pop_front(struct deque_element **first_element, struct deque_element **last_element, int *size) {
    if ((*size)==0) {
        printf("error\n");
    } else {
        front(first_element, size);
        struct deque_element *tmp = (*first_element);
        (*first_element) = (*first_element)->next;
        free(tmp);

        if ((*size) == 1) {
            *last_element = NULL;
            *first_element = NULL;
        }
        (*size)--;
    }
}

void pop_back(struct deque_element **first_element, struct deque_element **last_element, int *size) {
    if ((*size)==0) {
        printf("error\n");
    } else {
        back(last_element, size);
        struct deque_element *tmp = (*first_element);
        while (tmp->next != (*last_element) && tmp->next != NULL) tmp = tmp->next;
        tmp->next = NULL;
        free(*last_element);
        (*last_element) = tmp;

        if ((*size) == 1) {
            *last_element = NULL;
            *first_element = NULL;
        }

        (*size)--;
    }
}


void get_size(int *size) {
    printf("%d\n", (*size));
}

void clear(struct deque_element **first_element, struct deque_element **last_element, int *size, int *running_flag) {
    struct deque_element *current = *first_element;
    struct deque_element *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    *first_element = NULL;
    *last_element = NULL;
    *size = 0;

    if ((*running_flag)) {
        printf("ok\n");
    }
}

void exitututu(int *running_flag) {
    *running_flag = 0;
    printf("bye\n");
}


int main(void) {

    int running_flag = 1, size=0, val;
    char command[20];

    struct deque_element *first_one = NULL;
    struct deque_element *last_one = NULL;

    while (running_flag) {
        scanf(" %s", command);

        if (!strcmp(command, "push_front")) {
            scanf(" %d", &val);
            push_front(&first_one, &last_one, &size, val);
        } else if (!strcmp(command, "push_back")) {
            scanf(" %d", &val);
            push_back(&first_one, &last_one, &size, val);
        } else if (!strcmp(command, "front")) {
            front(&first_one, &size);
        } else if (!strcmp(command, "back")) {
            back(&last_one, &size);
        } else if (!strcmp(command, "size")) {
            get_size(&size);
        } else if (!strcmp(command, "clear")) {
            clear(&first_one, &last_one, &size, &running_flag);
        } else if (!strcmp(command, "pop_front")) {
            pop_front(&first_one, &last_one, &size);
        } else if (!strcmp(command, "pop_back")) {
            pop_back(&first_one, &last_one, &size);
        } else if (!strcmp(command, "clear")) {
            clear(&first_one, &last_one, &size, &running_flag);
        } else if (!strcmp(command, "exit")) {
            exitututu(&running_flag);
        }


    }

    clear(&first_one, &last_one, &size, &running_flag);

    
    



    return 0;
}
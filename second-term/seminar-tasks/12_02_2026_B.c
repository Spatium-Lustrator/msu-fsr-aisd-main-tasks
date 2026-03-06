#include <stdio.h>
#include <stdlib.h>

struct heap_node {
    int key; 
    double priority;
};

void swap(struct heap_node **heap, int index1, int index2) {
    struct heap_node *tmp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = tmp;
}

void sift_up(struct heap_node **heap, int index, int size) {
    int parent_index;
    if (index > 0) {
        parent_index = (index-1) / 2;
        if (heap[index]->priority < heap[parent_index]->priority) {
            swap(heap, parent_index, index);
            sift_up(heap, parent_index, size);
        }
    }
}

void sift_down(struct heap_node **heap, int index, int size) {
    int right_child=2*index+2, left_child=2*index+1, index_of_smallest=index;

    if (left_child<size && heap[left_child]->priority < heap[index_of_smallest]->priority) {
        index_of_smallest = left_child;
    }

    if (right_child<size && heap[right_child]->priority < heap[index_of_smallest]->priority) {
        index_of_smallest = right_child;
    }

    if (index_of_smallest != index) {
        swap(heap, index, index_of_smallest);
        sift_down(heap, index_of_smallest, size);
    }

}


void insert_element(struct heap_node ***heap, int *size, int *capacity, int key, double value) {
    if ((*size) >= (*capacity)) {
        (*capacity) *= 2;
        (*heap) = realloc((*heap), (sizeof(struct heap_node*))*(*capacity));
    }

    if ( (*heap)[(*size)] == NULL) {
        (*heap)[(*size)] = malloc(sizeof(struct heap_node));
    }
    ((*heap)[(*size)])->priority = value;
    ((*heap)[(*size)])->key = key;
    (*size) += 1;
    sift_up((*heap), (*size)-1, *size);

}


void change_element(struct heap_node **heap, int size, int key, double new_value) {
    int i, f=1;
    double old_value;

    for (i=0; i<size && f; i++) {
        if (heap[i]->key == key) {
            f=0;
            old_value = heap[i]->priority;
            heap[i]->priority = new_value;
            if (old_value < new_value) {
                sift_down(heap, i, size);
            } else {
                sift_up(heap, i, size);
            }
        }
    }

    

}

void view_minimum(struct heap_node **heap, int size) {
    if (size > 0) {
        printf("%d %lf\n", heap[0]->key, heap[0]->priority);
    } else {
        printf("The P_queue is empty\n");
    }
}


void get_minimum(struct heap_node **heap, int *size) {
    int key;
    double priority;

    if ((*size)>0) {

        priority = heap[(*size)-1]->priority;
        key = heap[(*size)-1]->key;

        free(heap[(*size)-1]);

        heap[0]->key = key;
        heap[0]->priority = priority;

        (*size) -= 1;   
        sift_down(heap, 0, (*size));

    }
}

void is_empty(int size) {
    printf("%d\n", size==0);
}

int main(void) {

    int capacity=3, size=0, command, key, i;
    double value;
    struct heap_node **heap = calloc(capacity,sizeof(struct heap_node*));

    scanf("%d", &command);

    while (command) {
        switch (command) {
            case 1:
                scanf("%d %lf", &key, &value);
                insert_element(&heap, &size, &capacity, key, value);
                break;

            case 2:
                view_minimum(heap, size);
                get_minimum(heap, &size);
                break;

            case 3:
                is_empty(size);
                break;

            case 4:
                scanf("%d %lf", &key, &value);
                change_element(heap, size, key, value);
                break;
            
            default:
                break;
        }
        scanf("%d", &command);
    }

    for (i=0; i<size; i++) if (heap[i]) free(heap[i]);
    free(heap);



    return 0;
}
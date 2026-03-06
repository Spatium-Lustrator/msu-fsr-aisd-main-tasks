#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *array;
    int size;
    int capacity;
} Heap;

Heap *create_heap(int capacity) {
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (int *)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sift_down(Heap *heap, int i) {
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if (left < heap->size && heap->array[left] < heap->array[largest]) {
        largest = left;
    }


    if (right < heap->size && heap->array[right] < heap->array[largest]) {
        largest = right;
    }

    if (largest != i){
        swap(&heap->array[i], &heap->array[largest]);
        sift_down(heap, largest);
    }
}

void sift_up(Heap *heap, int i) {
    while (i != 0 && heap->array[(i-1)/2] > heap->array[i]) {
            swap(&heap->array[i], &heap->array[(i-1)/2]);
            i = (i-1) / 2;
    }
}

void insert_to_heap(Heap *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
    } else {
        heap->size++;
        int i = heap->size - 1;
        heap->array[i] = value;

        sift_up(heap, i);

        
    }
}

void view_min(Heap *heap) {
    if (heap->size <= 0) {
        printf("CANNOT\n");
    } else {
        printf("%d\n", heap->array[0]);
    }
}

void get_min(Heap *heap) {
    if (heap->size <= 0) {
        printf("CANNOT\n");
    } else if (heap->size == 1) {
        view_min(heap);
        heap->size--;  
    } else {
        view_min(heap);
        heap->array[0] = heap->array[heap->size - 1];
        heap->size--;
        sift_down(heap, 0);
    }

}

void clear_heap(Heap *heap) {
    heap->size=0;
}


int main(void) {
    Heap *heap = create_heap(200000);

    int value;
    char command[10];
    
    while (scanf("%s", command) == 1) {
        if (command[0] == 'E') {
            get_min(heap);
        } else if (command[0] == 'A') {
            scanf("%d", &value);
            insert_to_heap(heap, value);
        } else if (command[0] == 'C') {
            clear_heap(heap);
        }
        
    }

    free(heap->array);
    free(heap);
    return 0;
}
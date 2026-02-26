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

int sift_down(Heap *heap, int i) {
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    int final_index;

    if (right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }

    if (left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }


    if (largest != i){
        swap(&heap->array[i], &heap->array[largest]);
        final_index = sift_down(heap, largest);
    } else {
        final_index = i;
    }

    return final_index;
}

void insert_to_heap(Heap *heap, int value) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
    } else {
        heap->size++;
        int i = heap->size - 1;
        heap->array[i] = value;

        
    }

    
}

int decrease_value(Heap *heap, int index, int newValue) {
    heap->array[index] -= newValue;
    return sift_down(heap, index);
}

void print_heap(Heap *heap) {
    for (int i = 0; i < heap->size; ++i)
        printf("%d ", heap->array[i]);
    printf("\n");
}

int main(void) {

    int n, i, value, index;
    scanf("%d", &n);
    Heap *heap = create_heap(n);

    for (i=0; i<n; i++) {
        scanf("%d", &value);
        insert_to_heap(heap, value);
    }

    scanf("%d", &n);

    for (i=0; i<n; i++) {
        scanf("%d%d", &index, &value);
        printf("%d\n", decrease_value(heap, index-1, value)+1);
    }
    
    print_heap(heap);

    

    free(heap->array);
    free(heap);
    return 0;
}
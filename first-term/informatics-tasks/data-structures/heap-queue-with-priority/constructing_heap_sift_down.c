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
    if (left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }


    if (largest != i){
        swap(&heap->array[i], &heap->array[largest]);
        sift_down(heap, largest);
    } 
}

void build_heap(Heap *heap) {
    int n = heap->size, i;
    for (i = (n-1)/2; i >= 0; i--) {
        sift_down(heap, i);
    }
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

void print_heap(Heap *heap) {
    for (int i = 0; i < heap->size; ++i)
        printf("%d ", heap->array[i]);
    printf("\n");
}

int main(void) {

    int n, i, value;
    scanf("%d", &n);
    Heap *heap = create_heap(n);

    for (i=0; i<n; i++) {
        scanf("%d", &value);
        insert_to_heap(heap, value);
        
    }
    
    build_heap(heap);
    print_heap(heap);

    

    free(heap->array);
    free(heap);
    return 0;
}
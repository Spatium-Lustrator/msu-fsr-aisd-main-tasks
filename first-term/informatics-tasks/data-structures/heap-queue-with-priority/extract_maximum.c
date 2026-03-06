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
    if (left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
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


int view_max(Heap *heap) {
    if (heap->size <= 0) {
        return -1;
    } else {
        return heap->array[0];  
    }
}

int get_max(Heap *heap) {
    if (heap->size <= 0) {
        return -1;
    } else if (heap->size == 1) {
        view_max(heap);
        heap->size--;  
        return 0;
    } else {
        heap->array[0] = heap->array[heap->size - 1];
        heap->size--;
        return sift_down(heap, 0);

    }

    
}


int main(void) {
    int n, value, i, index, max_val;
    scanf("%d", &n);
    
    Heap *heap = create_heap(n);

    for (i=0; i<n; i++) {
        scanf("%d", &value);
        insert_to_heap(heap, value);
    }

    for (i=0; i<n-1; i++) {
        max_val = view_max(heap);
        index = get_max(heap);
        printf("%d %d\n", index+1, max_val);
    }

    
    free(heap->array);
    free(heap);
    return 0;
}
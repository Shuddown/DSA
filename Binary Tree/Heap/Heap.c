#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *data;
    int size;
    int capacity;
} Heap;

Heap* new_heap(size_t capacity){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

size_t heap_left(size_t i){
    return 2 * i + 1;
}

size_t heap_right(size_t i){
    return 2 * i + 2;
}

size_t heap_parent(size_t i){
    return (i - 1) / 2;
}

void swap(Heap* heap, size_t i, size_t j){
    int temp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = temp;
}

void bubble_up(Heap* heap, size_t i){
    while(i > 0){
        if(heap->data[heap_parent(i)] > heap->data[i]){
            swap(heap, heap_parent(i), i);
            i = heap_parent(i);
        }
    }
}

void insert(Heap* heap, int val){
    if(heap->size == heap->capacity) return;

    heap->data[heap->size] = val;
    bubble_up(heap, heap->size);
    heap->size++;
}

bool has_left(Heap* heap, size_t i){
    return heap_left(i) < heap->size; 
}


bool has_right(Heap* heap, size_t i){
    return heap_right(i) < heap->size; 
}

size_t min_index(Heap* heap, size_t i, size_t j){
    return heap->data[i] <= heap->data[j] ? i : j;
}

void heapify(Heap* heap, size_t index){
    if(!has_left(heap, index)) return;
    size_t min = index;
    if(has_right(heap, index)) min = min_index(heap, heap_right(index), min_index(heap, index, heap_left(index)));
    else min = min_index(heap, index, heap_left(index));
    if(min == index) return;
    swap(heap, min, index);
    heapify(heap, min);
}

int extract_min(Heap* heap){
    int val = heap->data[0];
    swap(heap, 0, --heap->size);
    heapify(heap, 0);
    return val;
}

void print_heap(Heap* heap){
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main(){
    Heap* heap = new_heap(10);
    insert(heap, 10);
    insert(heap, 9);
    insert(heap, 8);
    insert(heap, 7);
    insert(heap, 6);
    insert(heap, 5);
    insert(heap, 4);
    insert(heap, 3);
    insert(heap, 2);
    insert(heap, 1);
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    printf("%d\n", extract_min(heap));
    print_heap(heap);
    return 0;
}
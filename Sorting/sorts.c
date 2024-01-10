#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void insertion_sort(int* arr, size_t size, size_t step, size_t start){
    for(size_t i = start, j; i<size; i+=step){
        int key = arr[i];
        for(j = i; j>start && arr[j-step] > key ; j-=step){
            arr[j] = arr[j-step];
        }
        arr[j] = key;
    }
}

void shell_sort(int* arr, size_t size){
    for(size_t step = size/2; step>0; step/=2){
        for(size_t start = 0; start<step; start++){
            insertion_sort(arr, size, step, start);
        }
    }
}

int main(){
    int arr[] = {5, 4, 3, 2, 1};
    insertion_sort(arr, 5, 1, 0);
    for(int i = 0; i<5; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    arr[0] = 5;
    arr[1] = 4;
    shell_sort(arr, 5);
    for(int i = 0; i<5; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
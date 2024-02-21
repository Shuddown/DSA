#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define SIZE(arr) sizeof(arr)/sizeof(arr[0])

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

int array_max(int* arr, size_t size){
    int max = arr[0];
    for(size_t i = 1; i<size; i++){
        if(max < arr[i]) max = arr[i];
    }
    return max;
}

size_t nth_digit(int num, size_t n, size_t radix){
    int next = (int) (num / pow((double) radix, (double) n));
    int val = next % (int) radix;
    return (size_t) (num < 0 ? ((int) radix) + val - 1: (int) val);
}

void count_sort(int arr[], size_t size, size_t n, size_t radix){
    size_t counts[radix];
    memset(counts, 0, radix * sizeof(size_t));

    int sorted[size];

    for(size_t i = 0; i<size; i++){
        counts[nth_digit(arr[i], n, radix)]++;
    }

    for(size_t i = 1; i<radix; i++){
        counts[i]+=counts[i-1];
    }

    for(size_t i = size-1;i < size; i--){
        sorted[--counts[nth_digit(arr[i], n, radix)]] = arr[i];
    }

    memcpy(arr, sorted, size * sizeof(int));
}

void count_sign_sort(int arr[], size_t size){
    size_t counts[2] = {0};
    int sorted[size];

    for(size_t i = 0; i<size; i++){
        counts[(arr[i] > 0)]++;
    }

    counts[1] += counts[0];

    for(size_t i = size - 1; i < size; i--){
        sorted[--counts[(arr[i] > 0)]] = arr[i];
    }

    memcpy(arr, sorted, size * sizeof(int));
}

void radix_sort(int arr[], size_t size, size_t radix){
    double max_num_digit = log(abs(array_max(arr, size))) / log((double) radix) + 1;

    for(size_t i = 0; i<max_num_digit; i++){
        count_sort(arr, size, i, radix);
    }

    count_sign_sort(arr, size);
}

void print_array(int arr[], size_t size){
    for(size_t i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[] = {1, 4, -9, 16, 25, -36, 49, -64};
    radix_sort(arr, SIZE(arr), 7);
    for(size_t i = 0; i<SIZE(arr); i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
    
}
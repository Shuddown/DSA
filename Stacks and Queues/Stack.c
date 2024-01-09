#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int* arr;
    size_t top;
    size_t capacity;
}Stack;

Stack* new_stack(size_t capacity){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->arr = (int*) malloc(sizeof(int) * capacity);
    stack->top = -1;
    return stack;    
}

bool is_empty(Stack* stack){
    return stack->top == -1;
}

void push(Stack* stack, int val){
    if(stack->top == stack->capacity - 1) return;
    stack->arr[++stack->top] = val;
}

int peek(Stack* stack){
    if(is_empty(stack)) return -1;
    return stack->arr[stack->top];
}

int pop(Stack* stack){
    if(is_empty(stack)) return -1;
    int del_val = peek(stack);
    stack->top--;
    return del_val;
}

void print_stack(Stack* stack){
    for(int i = 0; i<=stack->top; i++){
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main(){
    Stack* stack = new_stack(10);
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    print_stack(stack);
    printf("%d\n", pop(stack));
    printf("%d\n", pop(stack));
    print_stack(stack);
    printf("%d\n", peek(stack));
    return 0;
}



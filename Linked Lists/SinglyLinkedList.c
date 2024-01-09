#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* next;
}ListNode;

ListNode* create_node(int val, ListNode* next){
    ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
    new_node->data = val;
    new_node->next = next;
    return new_node;
}


ListNode** new_linked_list(){
    ListNode** head = (ListNode**) malloc(sizeof(ListNode*));
    *head = NULL;
    return head;
}

void insert_begin(ListNode** head, int data){
    *head = create_node(data, *head);
}

void insert_middle(ListNode** head, size_t index, int data){
    ListNode** tracer = head;
    for(size_t i = 0; i<index && *tracer; i++){
        tracer = &(*tracer)->next;
    }
    *tracer = create_node(data, *tracer);
}

void insert_end(ListNode** head, int data){
    ListNode** tracer = head;
    while(*tracer != NULL){
        tracer = &(*tracer)->next;
    }
    *tracer = create_node(data, *tracer);
}

void print(ListNode** head){
    ListNode* curr = *head;
    while(curr != NULL){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void del_head(ListNode** head){
    if(*head == NULL) return;

    ListNode* old_head = *head;
    *head = head[0]->next;
    free(old_head);
}

void del_middle(ListNode** head, size_t index){
    if(*head == NULL) return;

    ListNode** tracer = head;
    for(size_t i = 0; i<index && *tracer; i++){
        tracer = &(*tracer)->next;
    }        
    ListNode* old_node = *tracer;
    *tracer = (*tracer)->next;
    free(old_node);
}

void del_end(ListNode** head){
    if(*head == NULL) return;    

    ListNode** tracer = head;
    while((*tracer)->next != NULL){
        tracer = &(*tracer)->next;
    }
    ListNode* old_node = *tracer;
    *tracer = NULL;
    free(old_node);
}

void del_list(ListNode** head){
    ListNode* curr = *head;
    while(curr != NULL){
        ListNode* next = curr->next;
        free(curr);
        curr = next;
    }
    free(head);
}

int main(){
    ListNode** head = new_linked_list();
    insert_begin(head, 1);
    insert_begin(head, 2);
    insert_middle(head, 2, 3);
    insert_middle(head, 2, 3);
    insert_middle(head, 2, 3);
    insert_middle(head, 3, 3);
    insert_middle(head, 3, 3);
    insert_end(head, 8);
    insert_end(head, 9);
    insert_end(head, 10);
    insert_end(head, 11);
    insert_end(head, 12);
    print(head);
    del_head(head);
    print(head);
    del_middle(head, 5);
    print(head);
    del_end(head);
    print(head);
    del_list(head);
    return 0;
}

    

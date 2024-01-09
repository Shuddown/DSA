#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

typedef struct node{
    int data;
    struct node* next;
    struct node* prev;
}ListNode;

ListNode* create_node(int data, ListNode* next, ListNode* prev){
    ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
    new_node->data = data;
    new_node->next = next;
    new_node->prev = prev;
    return new_node;
}

ListNode* new_list(){
    ListNode* head = create_node(-1, NULL, NULL);
    ListNode* tail = create_node(-1, NULL, head);
    head->next = tail;
    return head;
}

void insert_at(ListNode* node, int data){
    ListNode* new_node = create_node(data, node->next, node);
    node->next = new_node;
    new_node->next->prev = new_node;
}

void insert_begin(ListNode* head, int data){
    insert_at(head, data);
}

void insert_middle(ListNode* head, size_t index, int data){
    ListNode* curr = head;
    while(curr->next->next != NULL && index--){
        curr = curr->next;
    }
    insert_at(curr, data);
}

void insert_end(ListNode* head, int data){
    ListNode* curr = head;
    while(curr->next->next != NULL){
        curr = curr->next;
    }
    insert_at(curr, data);
}

void print_list(ListNode* head){
    ListNode* curr = head->next;
    while(curr->next != NULL){
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int delete_at(ListNode* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
    int data = node->data;
    free(node);
    return data;
}

int delete_begin(ListNode* head){
    return delete_at(head->next);
}

int delete_middle(ListNode* head, size_t index){
    ListNode* curr = head->next;
    while(curr->next->next != NULL && index--){
        curr = curr->next;
    }
    return delete_at(curr);
}

int delete_end(ListNode* head){
    ListNode* curr = head;
    while(curr->next->next != NULL){
        curr = curr->next;
    }
    return delete_at(curr);
}

int search_list_index(ListNode* head, int data){
    ListNode* curr = head->next;
    size_t index = 0;
    while(curr->next != NULL){
        if(curr->data == data) return index;
        curr = curr->next;
        index++;
    }
    return -1;
}

ListNode* search_list_node(ListNode* head, int data){
    ListNode* curr = head->next;
    while(curr->next != NULL){
        if(curr->data == data) return curr;
        curr = curr->next;
    }
    return NULL;
}

void delete_val(ListNode* head, int data){
    ListNode* del_node = search_list_node(head, data);
    if(del_node == NULL) return;
    delete_at(del_node);
}

void delete_val_all(ListNode* head, int data){
    ListNode* del_node = search_list_node(head, data);
    if(del_node == NULL) return;
    delete_val_all(del_node, data);
    delete_at(del_node); 
}

void print_list_reverse(ListNode* head){
    ListNode* curr = head->next;
    if(curr->next == NULL) return;
    print_list_reverse(curr);
    printf("%d ", curr->data);
}

void delete_list(ListNode* head){
    ListNode* curr = head->next;
    while(curr->next != NULL){
        ListNode* old_node = curr;
        curr = curr->next;
        free(old_node);
    }
    free(curr);
    free(head);
}


int main(){
    ListNode* head = new_list();
    insert_begin(head, 1);
    insert_begin(head, 2);
    insert_begin(head, 3);
    print_list(head);
    insert_middle(head, 2, 4);
    insert_middle(head, 2, 5);
    insert_middle(head, 3, 6);
    insert_end(head, 7);    
    insert_end(head, 7);
    insert_end(head, 7);
    print_list(head);
    print_list_reverse(head);
    printf("\n");
    delete_begin(head);
    delete_middle(head, 2);
    delete_end(head);
    print_list(head);
    delete_val(head, 4);
    delete_begin(head);
    delete_end(head);
    delete_val_all(head, 7);
    print_list(head);
    delete_list(head);
    return 0;
}






#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}TreeNode;


TreeNode* create_node(int data, TreeNode* left, TreeNode* right){
    TreeNode* new_node = (TreeNode*) malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

TreeNode** new_bst(){
    TreeNode** root = (TreeNode**) malloc(sizeof(TreeNode*));
    *root = NULL;
    return root;
}

TreeNode** search(TreeNode** root, int data){
    TreeNode** tracer = root;
    while(*tracer != NULL){
        if((*tracer)->data == data) return tracer;
        else if((*tracer)->data > data) tracer = &((*tracer)->left);
        else tracer = &((*tracer)->right);
    }
    return tracer;
}

void insert_node(TreeNode** root, int data){
    TreeNode** found = search(root, data);
    while(*found){
        found = search(&(*found)->left, data);
    }
    *found = create_node(data, NULL, NULL);
}

void inorder(TreeNode** root){
    if(*root == NULL) return;
    inorder(&root[0]->left);
    printf("%d ", root[0]->data);
    inorder(&root[0]->right);
}

void preorder(TreeNode** root){
    if(*root == NULL) return;
    printf("%d ", root[0]->data);
    preorder(&root[0]->left);
    preorder(&root[0]->right);
}

void postorder(TreeNode** root){
    if(*root == NULL) return;
    postorder(&root[0]->left);
    postorder(&root[0]->right);
    printf("%d ", root[0]->data);
}

size_t height(TreeNode** root){
    if(*root == NULL) return -1;
    return 1 + MAX(height(&root[0]->left), height(&root[0]->right));
}

size_t size(TreeNode** root){
    if(*root == NULL) return 0;
    return 1 + size(&root[0]->left) + size(&root[0]->right);
}

int min(TreeNode** root){
    if(*root == NULL) return INT_MIN;
    TreeNode* curr = *root;
    while(curr->left != NULL){
        curr = curr->left;
    }
    return curr->data;
}

bool is_leaf(TreeNode* node){
    return !(node->left || node->right);
}

TreeNode* single_child(TreeNode* node){
    if(node->left == NULL && node->right != NULL)
        return node->right;
    if(node->left != NULL && node->right == NULL)
        return node->left;
    return NULL;
}

bool is_full(TreeNode* node){
    return (node->left && node->right);
}

TreeNode* inorder_successor(TreeNode** root, int data){
    TreeNode* curr = *root;
    if(curr == NULL) return NULL;
    TreeNode* val = NULL;
    bool has_left = false;
    if(curr->data <= data) val = inorder_successor(&curr->right, data);
    else{ 
        val = inorder_successor(&curr->left , data);
        has_left = true;
    }
    
    return val == NULL  &&  has_left ? curr : val;
}

TreeNode** inorder_successor_lite(TreeNode** root){
    if(*root == NULL) return NULL;
    TreeNode** tracer = &root[0]->right;
    while(tracer[0]->left != NULL){
        tracer = &tracer[0]->left;
    }
    return tracer;
}

void swap(TreeNode** i , TreeNode** j){
    TreeNode* left_i = (*i)->left;
    TreeNode* right_i = (*i)->right;
    TreeNode* left_j = (*j)->left;
    TreeNode* right_j = (*j)->right;

    TreeNode* temp = *i;
    *i = *j;

    (*i)->left = left_i;
    (*i)->right = right_i;

    (*j) = temp;

    (*i)->left = left_j;
    (*i)->right = right_j;
}

void delete(TreeNode** root, int data){

    TreeNode** found_node = search(root, data);
    if(found_node == NULL || *found_node == NULL) return;


    if(!is_full(*found_node)){
        TreeNode* child = single_child(*found_node);
        TreeNode* temp = *found_node;
        *found_node = child;
        free(temp);
        return;
    }

    TreeNode** succ = inorder_successor_lite(found_node);
    found_node[0]->data = succ[0]->data;
    delete(succ, succ[0]->data);
}

int main(){
    TreeNode** root = new_bst();
    insert_node(root, 5);
    insert_node(root, 3);
    insert_node(root, 7);
    insert_node(root, 2);
    insert_node(root, 4);
    insert_node(root, 6);
    insert_node(root, 8);
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    printf("%zu\n", height(root));
    printf("%zu\n", size(root));
    printf("%d\n", min(root));
    printf("%d\n", inorder_successor(root, 5)->data);
    delete(root, 5);
    inorder(root);
    printf("\n");
    delete(root, 3);
    inorder(root);
    printf("\n");
    delete(root, 7);
    inorder(root);
    printf("\n");
    delete(root, 2);
    inorder(root);
    printf("\n");
    delete(root, 4);
    inorder(root);
    printf("\n");
    delete(root, 6);
    inorder(root);
    printf("\n");
    delete(root, 8);
    inorder(root);
    printf("\n");
    return 0;
}


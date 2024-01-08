#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct node{
    float coeff;
    unsigned exp;
    struct node* next;
}PolyNode;

PolyNode* create_node(float coeff, unsigned exp, PolyNode* next){
    PolyNode* new_node = (PolyNode*) malloc(sizeof(PolyNode));
    new_node->coeff = coeff;
    new_node->exp = exp;
    new_node->next = next;
    return new_node;
}

PolyNode** new_poly(){
    PolyNode** head = (PolyNode**) malloc(sizeof(PolyNode*));
    *head = NULL;
    return head;
}

void add_term(PolyNode** head, float coeff, unsigned exp){
    PolyNode** tracer = head;
    while(*tracer && (*tracer)->exp > exp){
        tracer = &(*tracer)->next;
    }
    if(*tracer == NULL || (*tracer)->exp < exp) *tracer = create_node(coeff, exp, *tracer);

    else (*tracer)->coeff += coeff;
}

PolyNode** add_poly(PolyNode** poly1, PolyNode** poly2){
    PolyNode** result = new_poly();
    
    for(PolyNode* curr = *poly1; curr != NULL; curr = curr->next){
        add_term(result, curr->coeff, curr->exp);
    }
    
    for(PolyNode* curr = *poly2; curr != NULL; curr = curr->next){
        add_term(result, curr->coeff, curr->exp);
    }

    return result;
}

char* clean_poly(const char* poly){
    char* result = (char*) malloc(sizeof(char) * (strlen(poly) + 2));
    char* tracer = result;
    *tracer++ = '+';
    while(*poly){
        if(isspace(*poly)) poly++;
        else if(isalpha(*poly)){
            if(isdigit(*(tracer-1))) *tracer++ = *poly++;
            else *tracer++ = '1', *tracer++ = *poly++;

            if(*poly == '^') poly++;
            else *tracer++ = '1';
        }
        else if(*poly == '-') *tracer++ = '+', *tracer++ = *poly++;
        else if(*poly == '+' || isdigit(*poly) || *poly == '.') *tracer++ = *poly++;
        else return NULL;
    }
    *tracer = '\0';
    return result;
}

PolyNode** parse_poly(const char* poly){
    PolyNode** result = new_poly();
    char* cleaned_poly = clean_poly(poly);
    if(cleaned_poly == NULL) return NULL;
    char* token = strtok(cleaned_poly, "+");
    char* end;
    while(token){ 
        float coeff = strtof(token, &end);
        token = end + 1;
        unsigned exp = strtol(token, &end, 10);
        if(exp == 0) add_term(result, coeff, 0);
        else add_term(result, coeff, exp);

        token = strtok(NULL, "+");
    }
    return result;
}

void print_poly(PolyNode** poly){
    PolyNode* curr = *poly;
    while(curr != NULL){
        printf("%.2fx^%d ", curr->coeff, curr->exp);
        curr = curr->next;
    }
    printf("\n");
}

int main(){
    PolyNode** poly1 = parse_poly("2x^3 - 3x^5 - 4");
    PolyNode** poly2 = parse_poly("-3.8x^2 + 2x^4 + 1");
    print_poly(poly1);
    print_poly(poly2);
    if(poly1 == NULL || poly2 == NULL) return 1;
    PolyNode** result = add_poly(poly1, poly2);
    print_poly(result);
    return 0;
}
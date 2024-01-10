#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// FILEPATH: /workspaces/DSA/Hashtable/hashtable.c

typedef struct entry{
    char* key;
    int value;
    struct entry* next;
} Entry;

Entry* new_entry(char* key, int value){
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

typedef struct {
    Entry** arr;
    size_t capacity;
} Hashtable;

Hashtable* new_hashtable(size_t capacity){
    Hashtable* hashtable = (Hashtable*)malloc(sizeof(Hashtable));
    hashtable->arr = (Entry**)malloc(sizeof(Entry*) * capacity);
    hashtable->capacity = capacity;
    for(size_t i = 0; i<capacity; i++){
        hashtable->arr[i] = NULL;
    }
    return hashtable;
}

size_t hash(char* key, size_t capacity){
    size_t hash = 0;
    for(size_t i = 0; i<strlen(key); i++){
        hash = hash * 31 + key[i];
    }
    return hash % capacity;
}

void put(Hashtable* hashtable, char* key, int value){
    size_t index = hash(key, hashtable->capacity);
    Entry** tracer = &hashtable->arr[index];

    while(*tracer){
        if(strcmp((*tracer)->key, key) == 0){
            (*tracer)->value = value;
            return;
        }
        tracer = &(*tracer)->next;
    }
    *tracer = new_entry(key, value);
}

int get(Hashtable* hashtable, char* key){
    size_t index = hash(key, hashtable->capacity);
    
    for(Entry* entry = hashtable->arr[index]; entry; entry = entry->next){
        if(strcmp(entry->key, key) == 0){
            return entry->value;
        }
    }
    return -1;
}

void print_hashtable(Hashtable* hashtable){
    for(size_t i = 0; i<hashtable->capacity; i++){
        Entry* entry = hashtable->arr[i];
        printf("%zu: ", i);
        while(entry){
            printf("%s:%d ", entry->key, entry->value);
            entry = entry->next;
        }
        printf("\n");
    }
}

int main(){
    Hashtable* hashtable = new_hashtable(10);
    put(hashtable, "hello", 1);
    put(hashtable, "world", 2);
    put(hashtable, "hello", 3);
    put(hashtable, "world", 4);
    put(hashtable, "hey", 5);
    put(hashtable, "there", 6);
    print_hashtable(hashtable);
    printf("%d\n", get(hashtable, "hello"));
    printf("%d\n", get(hashtable, "world"));
    printf("%d\n", get(hashtable, "hey"));
    printf("%d\n", get(hashtable, "there"));
    return 0;
}




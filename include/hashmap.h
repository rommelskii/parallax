#ifndef HASHMAP_H
#define HASHMAP_H

#include "task.h"

typedef struct Entry {
    char* key;
    void* value;
    struct Entry* next;
} Entry;

typedef struct HashMap {
    Entry** buckets; // An array of pointers to Entry
    size_t table_size;
} HashMap;

unsigned long hash_function(const char* str);
HashMap*      hashmap_create(size_t table_size);
void          hashmap_set(HashMap* map, char* key, void* value);
void*         hashmap_get(HashMap* map, char* key);
void          hashmap_destroy(HashMap* map);

#endif //HASHMAP_H

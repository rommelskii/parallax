#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct Entry {
    char* key;
    char* value;
    struct Entry* next;
} Entry;

typedef struct HashMap {
    Entry** buckets; // An array of pointers to Entry
} HashMap;

unsigned long hash_function(const char* str);
HashMap*      hashmap_create(size_t table_size);
HashMap*      lut_create(size_t table_size);
void          hashmap_destroy(HashMap* map, size_t table_size);
void          hashmap_set(HashMap* map, const char* key, char* value, size_t table_size);
char*         hashmap_get(HashMap* map, const char* key, size_t table_size);
#endif //HASHMAP_H

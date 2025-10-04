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
} HashMap;

unsigned long hash_function(const char* str);
HashMap*      hashmap_create(size_t table_size);
HashMap*      lut_create(size_t table_size);
void          hashmap_destroy(HashMap* map, size_t table_size);
void          task_set(HashMap* map, Task* new_task, size_t table_size);
void          task_class_set(HashMap* map, const char* key, TaskClass* new_task, size_t table_size);
Task*         task_get(HashMap* map, const char* key, size_t table_size);
TaskClass*    task_class_get(HashMap* map, const char* key, size_t table_size);
#endif //HASHMAP_H

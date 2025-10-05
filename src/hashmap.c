#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "hashmap.h"

unsigned long hash_function(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

// Creates and initializes a new hash map
HashMap* hashmap_create(size_t table_size) {
    // Allocate memory for the map structure
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    
    // Allocate memory for the array of buckets
    map->buckets = (Entry**)calloc(table_size, sizeof(Entry*));
    
    return map;
}

// probably unused for prlx 
HashMap* lut_create(size_t table_size) {
	HashMap* hm = hashmap_create(table_size);

  /**
    * insert hashmap population code here
    */

	return hm;
}

// Inserts or updates a key-value pair in the hash map
void task_set(HashMap* map, Task* new_task, size_t table_size) {
    // 1. Hash the key to get the bucket index
    const char* key = new_task->task_content;
    unsigned long hash = hash_function(key);
    int index = hash % table_size;

    // 2. Go to the bucket and traverse the linked list
    Entry* current = map->buckets[index];
    while (current != NULL) {
        // If the key already exists, update the value and return
        if (strcmp(current->key, key) == 0) {
            current->value = (Task*)malloc(sizeof(Task)); //varying types
            current->value = new_task;
            return;
        }
        current = current->next;
    }

    // 3. If the key doesn't exist, create a new entry
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = strdup(key); // Use strdup to copy the key
    new_entry->value = (Task*)malloc(sizeof(Task));//account for varying types
    new_entry->value = new_task;
    new_entry->next = NULL;

    // Insert the new entry at the head of the linked list
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
}

void task_class_set(HashMap* map, const char* key, TaskClass* new_task) 
{
    size_t table_size = new_task->table_size;
    // 1. Hash the key to get the bucket index
    unsigned long hash = hash_function(key);
    int index = hash % table_size;

    // 2. Go to the bucket and traverse the linked list
    Entry* current = map->buckets[index];
    while (current != NULL) {
        // If the key already exists, update the value and return
        if (strcmp(current->key, key) == 0) {
            current->value = (TaskClass*)malloc(sizeof(TaskClass)); // varying types
            current->value = new_task;
            return;
        }
        current = current->next;
    }

    // 3. If the key doesn't exist, create a new entry
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = strdup(key); // Use strdup to copy the key
    new_entry->value = (TaskClass*)malloc(sizeof(TaskClass));//account for varying types
    new_entry->value = new_task;
    new_entry->next = NULL;

    // Insert the new entry at the head of the linked list
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
}

// Retrieves a value from the hash map by key
Task* task_get(HashMap* map, const char* key, size_t table_size) {
    unsigned long hash = hash_function(key);
    int index = hash % table_size;

    Entry* current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // Key found
        }
        current = current->next;
    }

    return NULL;
}

TaskClass* task_class_get(HashMap* map, const char* key, size_t table_size) {
    unsigned long hash = hash_function(key);
    int index = hash % table_size;

    Entry* current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // Key found
        }
        current = current->next;
    }

    return NULL;
}
// Frees all memory used by the hash map
void hashmap_destroy(HashMap* map, size_t table_size) {
    for (size_t i = 0; i < table_size; i++) {
        Entry* current = map->buckets[i];
        while (current != NULL) {
            Entry* temp = current;
            current = current->next;
            free(temp->key); // Free the duplicated key
            free(temp);      // Free the entry node
        }
    }
    free(map->buckets); // Free the buckets array
    free(map);          // Free the map structure
}

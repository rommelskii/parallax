#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "hashmap.h"

/**
  * @file hashmap.c
  *
  * @brief Implementation of the hash map procedures
  */


/**
  * @brief Transforms a string to a hash number
  *
  * Utilizes djb2 in performing the transformation
  *
  * @param str Pointer to the string to be transformed
  * @return Hashed number corresponding to the string argument
  */
static unsigned long hash_function(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

HashMap* hashmap_create(size_t table_size) {
    // Allocate memory for the map structure
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    // Allocate memory for the array of buckets
    map->buckets = (Entry**)calloc(table_size, sizeof(Entry*));
    map->table_size = table_size;
    return map;
}

void hashmap_set(HashMap* map, char* key, void* value)
{
    unsigned long hash = hash_function(key);
    size_t table_size = map->table_size;
    int index = hash % table_size;

    Entry* current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    // 3. If the key doesn't exist, create a new entry
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = strdup(key); // Use strdup to copy the key
    new_entry->value = value;
    new_entry->next = NULL;

    // Insert the new entry at the head of the linked list
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
}

void* hashmap_get(HashMap* map, char* key)
{
  unsigned long hash = hash_function(key);
  size_t table_size = map->table_size;
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

void hashmap_elem_remove(HashMap* map, char* key)
{
  unsigned long hash = hash_function(key);  
  size_t index = hash % map->table_size;
  Entry* current = map->buckets[index];
  Entry* prev = NULL;
  while (current != NULL)
  {
    if (strcmp(current->key, key) == 0)
    {
      break;
    }
    prev = current;
    current = current->next;
  }
  if (current == NULL)
  {
    printf("Hashmap error: delete node cannot be found\n");
    return;
  }
  if (prev == NULL)
  {
    map->buckets[index] = current->next;
  } else {
    prev->next = current->next; 
  }
  free(current->key);
  free(current);
}

void hashmap_destroy(HashMap* map) 
{
  size_t table_size = map->table_size;
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

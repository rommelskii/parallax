#ifndef HASHMAP_H
#define HASHMAP_H

#include "task.h"

/**
  * @file hashmap.h
  *
  * @brief Contains the structures and procedures for hashmap-related operations 
  */

/**
  * @brief Linked list node definition of an entry in a hash map
  */
typedef struct Entry {
    char* key;          /**< Pointer to the key string of an entry */
    void* value;        /**< Abstract data value */
    struct Entry* next; /**< Pointer to the next entry */
} Entry;

/**
  * @brief Hashmap structure
  * 
  * Contains an array of Entry pointer nodes with a fixed size
  */
typedef struct HashMap {
    Entry** buckets;    /**< Array of entry pointers*/
    size_t table_size;  /**< Fixed size of the hash table*/
} HashMap;


/**
  * @brief Creates a hashmap of a fixed size
  *
  * @param table_size Size of the hash table
  * @return Pointer to the created hashmap
  */
HashMap*      hashmap_create(size_t table_size);

/**
  * @brief Adds an entry to a hashmap by a key string and value
  *
  * @param map Pointer to the hashmap
  * @param key Pointer to the key string 
  * @param value Pointer to the value 
  */
void          hashmap_set(HashMap* map, char* key, void* value);

/**
  * @brief Finds an entry in a non-empty hashmap by a key 
  *
  * Utilizes the standard approach of hashing and appending to non-empty entries.
  *
  * @param map Pointer to the hashmap
  * @param key Pointer to the key string 
  * @return Pointer to the found element. NULL if not found
  */
void*         hashmap_get(HashMap* map, char* key);

/**
  * @brief Removes an entry in a hashmap by its key 
  *
  * @param map Pointer to the hashmap
  * @param key Pointer to the key string 
  */
void          hashmap_elem_remove(HashMap* map, char* key);

/**
  * @brief Frees a hashmap to memory
  *
  * @param map Pointer to the hashmap
  */
void          hashmap_destroy(HashMap* map);

#endif //HASHMAP_H

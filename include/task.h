#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> // for size_t
#include <string.h>

#define MAX_TABLE_SIZE 50

typedef struct HashMap HashMap; // prevents circular dependency

/**
 * @file task.h
 *
 * @brief Contains structures and functions for handling task-related operations.
 *
 * Defines the schema of tasks, task classes, and task collections. It also contains
 * the procedures for creating, modifying, removing, and destroying the task structures. 
 */


/**
 * @brief A basic task.
 *
 * Contains two strings, which are the class and the content.
 */
typedef struct Task 
{
  char* task_class;     /**< Pointer to the class name string*/
  char* task_content;   /**< Pointer to the content string*/
} Task;

/**
 * @brief A task class containing other tasks.
 *
 * Synonymous to a subject or category that the task belongs to. 
 */
typedef struct TaskClass
{
  char* task_class_name;        /**< Pointer to the class name string*/
  size_t table_size;            /**< Size of the hash table containing the tasks*/
  HashMap* task_class_table;    /**< Pointer to the hash table containing tasks*/
} TaskClass;


/**
 * @brief A task collection containing other classes.
 *
 * Serves as a lookup table for the existing classes in the serverside
 */
typedef struct TaskCollection
{
  HashMap* task_collection; /**< Pointer to the hash table of classes*/
  size_t collection_size;   /**< Size of the hash table*/
} TaskCollection;

/**
 * @brief Creates a task of known class and content
 *
 * @param class_of_task Pointer to the class string of the task
 * @param task_content Pointer to the content string of the task
 *
 * @return Pointer to the created task
 */
Task*           create_task(char* class_of_task, char* task_content);

/**
 * @brief Creates a task class of a known class and size
 *
 * @param class_of_task Pointer to the class string of the task class
 * @param class_size Size of the task class hash table
 *
 * @return Pointer to the created task class
 */
TaskClass*      create_task_class(char* class_of_task, size_t class_size);

/**
 * @brief Creates a task collection of known size
 *
 * @param collection_size Size of the task collection hash table 
 *
 * @return Pointer to the created task collection
 */
TaskCollection* create_task_collection(size_t collection_size);


/**
 * @brief Finds a task in a task class by its content
 *
 * @param task_class Pointer to the task class to look into
 * @param key Pointer to the key string (task content)
 *
 * @return Pointer to the task found. Returns NULL if not found
 */
Task* get_task(TaskClass* task_class, const char* key);

/**
 * @brief Adds a task to a task class
 *
 * @param task_class Pointer to the task class that will contain the new task
 * @param new_task Pointer to the task to be added
 */
void  add_task(TaskClass* task_class, Task* new_task);

/**
 * @brief Gets a task class by its class name from a task collection
 *
 * @param task_collection Pointer to the task collection containing the task class to be found
 * @param key Pointer to the key string (task class name)
 *
 * @return Pointer to the task class found. Returns NULL if not found
 */
TaskClass*  get_task_class(TaskCollection* task_collection, const char* key);

/**
 * @brief Adds a task class to a task collection
 *
 * @param task_collection Pointer to the task collection that will contain the new task
 * @param task_class Pointer to the task class to be added
 */
void        add_task_class(TaskCollection* task_collection, TaskClass* task_class);


/**
 * @brief Removes a task from a task class by its content
 *
 * @param task_class Pointer to the task class that contains the task to be removed
 * @param task_content Pointer to the content string of the task to be removed
 */
void remove_task(TaskClass* task_class, char* task_content);

/**
 * @brief Removes a task class from a task collection
 *
 * @param task_collection Pointer to the task collection that contains the task class to be removed 
 * @param class_name Pointer to the class name string of the task class to be removed
 */
void remove_task_class(TaskCollection* task_collection, char* class_name);

/**
  * @brief Prints the content of a task
  * 
  * @param task Pointer to the task to be printed
  */
void  print_task(Task* task);

void  print_task_list(TaskClass* task_class);


#endif //TASK_H

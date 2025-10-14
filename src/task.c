#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "hashmap.h"

#define MAX_CLASS_LENGTH 256
#define MAX_CONTENT_LENGTH 2056 

/**
 * @file task.c
 * @author Rommel John Ronduen
 * @date 10-07-25
 */

Task* create_task(char* class_of_task, char* task_content)
{
  Task* task = (Task*)malloc(sizeof(Task));
  task->task_class = class_of_task;
  task->task_content = task_content;
  return task;
}

TaskClass* create_task_class(char* class_name, size_t class_size)
{
  /**
   * @note This is a wrapper around the hashmap_create function
   */
  TaskClass* task_class = (TaskClass*)malloc(sizeof(TaskClass));
  task_class->task_class_name = class_name;
  task_class->table_size = class_size;
  task_class->task_class_table = hashmap_create(class_size);
  return task_class;
}

TaskCollection* create_task_collection(size_t collection_size)
{
  /**
   * @note This is a wrapper around the hashmap_create function
   */
  TaskCollection* task_collection = (TaskCollection*)malloc(sizeof(TaskCollection)); 
  task_collection->collection_size = collection_size;
  task_collection->task_collection = hashmap_create(collection_size);
  return task_collection;
}

Task* get_task(TaskClass* task_class, const char* key) 
{
  /**
   * @note Wrapper around the hashmap_get function.
   *
   * Casts the output of hashmap_get to a Task* type
   */
  if ( task_class == NULL || key == NULL ) 
  {
    printf("Task class error: task class or key is null\n");
    return NULL;
  }
  if (task_class->table_size <= 0) 
  {
    printf("Task class error: invalid table size (%zu)", task_class->table_size);
    return NULL;
  }

  void* ret = hashmap_get(task_class->task_class_table, key);
  if (ret == NULL)
  {
    return NULL;
  }

  return (Task*)ret; //cast into Task type
}

void add_task(TaskClass* task_class, Task* new_task)
{
  /**
   * @note Wrapper around the hashmap_set function
   */
  if ( task_class == NULL || new_task->task_content == NULL ) 
  {
    printf("Task class error: task class or key is null\n");
    return;
  }
  if ( new_task == NULL ) 
  {
    printf("Task class error: new task to be added is null\n");
    return;
  }
  if ( task_class->table_size <= 0 ) 
  {
    printf("Task class error: invalid table size (%zu)", task_class->table_size);
    return;
  }
  
  hashmap_set(task_class->task_class_table, new_task->task_content, new_task);
}

TaskClass*  get_task_class(TaskCollection* task_collection, const char* key)
{
  /**
   * @note Wrapper around the hashmap_get function
   *
   * Casts the output of hashmap_get to a TaskClass* type
   */
  if (task_collection == NULL || key == NULL) 
  {
    return NULL;
  }
  if (task_collection->collection_size <= 0)
  {
    return NULL;
  }

  void* ret = hashmap_get(task_collection->task_collection, key);

  if (ret == NULL)
  {
    return NULL;
  }
  return (TaskClass*)ret; // Cast into a TaskClass type
}

void add_task_class(TaskCollection* task_collection, TaskClass* task_class)
{
  /**
   * @note Wrapper around hashmap_set 
   */
  if (task_collection == NULL || task_class == NULL) 
  {
    return;
  }
  if (task_class->task_class_name == NULL)
  {
    return;
  }

  hashmap_set(task_collection->task_collection, task_class->task_class_name, task_class);
}

int remove_task(TaskClass* task_class, char* task_content)
{
  /**
   * @note Wrapper around hashmap_elem_remove
   */
  if (task_class == NULL || task_content == NULL)
  {
    return -1;
  }
  if (task_class->task_class_table == NULL)
  {
    return -1; 
  }

  return hashmap_elem_remove(task_class->task_class_table, task_content);
}

int remove_task_class(TaskCollection* task_collection, char* class_name)
{
  /**
   * @note Wrapper around hashmap_elem_remove
   */
  if (task_collection == NULL || class_name == NULL)
  {
    return -1;
  }
  if (task_collection->task_collection == NULL)
  {
    return -1; 
  }

  return hashmap_elem_remove(task_collection->task_collection, class_name);
}

void print_task(Task* task)
{
  /**
  * @warning Assumes that the task attributes are non-NULL
  */
  if (task == NULL)
  {
    return;
  }
  printf("Task class: %s\nContent: %s\n", task->task_class, task->task_content);
}

void print_task_list(TaskClass* task_class)
{
  if (task_class == NULL)
  {
    printf("Task list print error: task_class empty\n");
    return;
  }
  if (task_class->task_class_name == NULL || task_class->task_class_table == NULL)
  {
    printf("Task list print error: one or more task class attributes are NULL\n");
    return;
  }


  // we use task size since we are returning tasks from a task class
  Entry* entry_list = hashmap_get_entries(task_class->task_class_table, sizeof(Task));
  if (entry_list == NULL) // task class is empty, i.e., has no non-NULL entries
  {
    printf("Task class '%s' is empty\n", task_class->task_class_name);
    return;
  }

  Entry* iter = entry_list; 
  while (iter != NULL)
  {
    Task* current_task = (Task*)(iter->value); // variable for casting iterator value

    if (current_task == NULL)
    {
      printf("Task list print error: key valid but non-existing task\n");
      return;
    }
    if (current_task->task_content == NULL || current_task->task_class == NULL)
    {
      printf("Task list print error: key valid but some attribute doesn't exist\n");
      return;
    }
    // if task is valid, print content to stdout
    printf("Content: %s | Class: %s\n", current_task->task_content, current_task->task_class);
    iter = iter->next;
  }

  return;
}




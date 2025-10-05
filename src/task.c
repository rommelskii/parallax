#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "hashmap.h"

#define MAX_CLASS_LENGTH 256
#define MAX_CONTENT_LENGTH 2056 

/**
 * TASK INITIALIZERS
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
  TaskClass* task_class = (TaskClass*)malloc(sizeof(TaskClass));
  task_class->task_class_name = class_name;
  task_class->table_size = class_size;
  task_class->task_class_table = hashmap_create(class_size);
  return task_class;
}

TaskCollection* create_task_collection(size_t collection_size)
{
  TaskCollection* task_collection = (TaskCollection*)malloc(sizeof(TaskCollection)); 
  task_collection->collection_size = collection_size;
  task_collection->task_collection = hashmap_create(collection_size);
  return task_collection;
}


/**
  * TASK GETTERS
  */

Task* get_task(TaskClass* task_class, const char* key) 
{
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
  return (Task*)ret;
  //return task_get(task_class->task_class_table, key, task_class->table_size);
}

void add_task(TaskClass* task_class, Task* new_task)
{
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
  return (TaskClass*)ret;
}

void add_task_class(TaskCollection* task_collection, TaskClass* task_class)
{
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

/**
 * END OF TASK CLASS MUTATORS
 */


/*
* MISCELLANEOUS
*/

void print_task(Task* task)
{
  if (task == NULL)
  {
    return;
  }
  printf("Task class: %s\nContent: %s\n", task->task_class, task->task_content);
}




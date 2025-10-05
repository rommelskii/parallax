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

Task* create_task()
{
  Task* task = (Task*)malloc(sizeof(Task));
  task->task_class = (char*)malloc(MAX_CLASS_LENGTH + 1);
  task->task_content = (char*)malloc(MAX_CONTENT_LENGTH + 1);
  memset(task->task_class, 0, MAX_CLASS_LENGTH + 1);
  memset(task->task_content, 0, MAX_CONTENT_LENGTH + 1);
  return task;
}

TaskClass* create_task_class()
{
  TaskClass* task_class = (TaskClass*)malloc(sizeof(TaskClass));
  task_class->task_class_name = (char*)malloc(MAX_CLASS_LENGTH + 1);
  task_class->table_size = 0;
  task_class->task_class_table = NULL;
  return task_class;
}


/**
  * TASK MUTATORS
  */

void set_task_class(Task* task, char* class)
{
  if ( task == NULL || class == NULL ){
    printf("Task error: task or class is null\n");
    return;
  }
  size_t class_length = strnlen(class, MAX_CLASS_LENGTH);
  if ( class_length >= MAX_CLASS_LENGTH )
  {
    printf("Task error: class size too large\n");
  }
  strncpy(task->task_class, class, class_length);
}

void set_task_content(Task* task, char* content)
{
  if ( task == NULL || content == NULL ){
    printf("Task error: task or content is null\n");
    return;
  }
  size_t content_length = strnlen(content, MAX_CONTENT_LENGTH);
  if ( content_length >= MAX_CONTENT_LENGTH )
  {
    printf("Task error: content size too large\n");
  }
  strncpy(task->task_content, content, content_length);
}
/**
 * END OF TASK MUTATORS
 */

/**
  * TASK CLASS MUTATORS
  */
void set_task_class_name(TaskClass* task_class, char* class_name)
{
  if ( task_class == NULL || class_name == NULL )
  {
    printf("Task class error: task class or class name is null\n");
    return;
  }
  size_t class_length = strnlen(class_name, MAX_CLASS_LENGTH);
  if ( class_length >= MAX_CLASS_LENGTH )
  {
    printf("Task class error: class size too large\n");
  }
  strncpy(task_class->task_class_name, class_name, class_length);
}

void set_table(TaskClass* task_class, size_t table_size)
{
  if ( task_class == NULL || table_size <= 0 )
  {
    printf("Task class error: task class or table size is nonpositive (%zu)\n", table_size);
    return;
  }
  task_class->table_size = table_size;
  task_class->task_class_table = hashmap_create(table_size);
}

Task* get_task_from_class(TaskClass* task_class, const char* key) 
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
  return task_get(task_class->task_class_table, key, task_class->table_size);
}


void add_task_to_class(TaskClass* task_class, Task* new_task)
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

  task_set(task_class->task_class_table, new_task, task_class->table_size);
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




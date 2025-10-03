#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>
#include "task.h"
#include "hashmap.h"

#define MAX_UUID_LENGTH 36
#define MAX_CLASS_LENGTH 256
#define MAX_CONTENT_LENGTH 2056 

/**
 * UUID TOOLS
 */

char* generate_uuid()
{
  uuid_t binuuid; 
  char* uuid_buf = (char*)malloc(MAX_UUID_LENGTH + 1);
  uuid_generate_random(binuuid);
  uuid_unparse(binuuid, uuid_buf);

  return uuid_buf;
}

/**
 * TASK INITIALIZERS
 */

Task* create_task()
{
  Task* task = (Task*)malloc(sizeof(Task));
  task->task_uuid = NULL;
  task->task_class = NULL;
  task->task_content = NULL;
  return task;
}

TaskClass* create_task_class()
{
  TaskClass* task_class = (TaskClass*)malloc(sizeof(TaskClass));
  task_class->task_class_name = NULL;
  task_class->table_size = 0;
  task_class->task_class_table = NULL;
  return task_class;
}


/**
  * TASK MUTATORS
  */
void set_task_uuid(Task* task, char* uuid)
{
  if ( task == NULL || uuid == NULL ){
    printf("Task error: task or uuid is null\n");
    return;
  }
  size_t uuid_length = strnlen(uuid, MAX_UUID_LENGTH);
  if ( uuid_length != MAX_UUID_LENGTH ) 
  {
    printf("Task error: UUID size too large\n");
    return;
  }
  strncpy(task->task_uuid, uuid, MAX_UUID_LENGTH);
}

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

void set_table_size(TaskClass* task_class, size_t table_size)
{
  if ( task_class == NULL || table_size <= 0 )
  {
    printf("Task class error: task class or table size is nonpositive (%zu)\n", table_size);
    return;
  }
  task_class->table_size = table_size;
}

//key is uuid
Task* get_task_from_table(TaskClass* task_class, const char* key) 
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
  return hashmap_get(task_class->task_class_table, key, task_class->table_size);
}


void add_task_to_table(TaskClass* task_class, const char* key, Task* new_task, size_t table_size)
{
  if ( task_class == NULL || key == NULL ) 
  {
    printf("Task class error: task class or key is null\n");
    return;
  }
  if ( new_task == NULL ) 
  {
    printf("Task class error: new task to be added is null\n");
    return;
  }
  if ( table_size <= 0 ) 
  {
    printf("Task class error: invalid table size (%zu)", task_class->table_size);
    return;
  }

  hashmap_set(task_class->task_class_table, key, new_task, task_class->table_size);
}

/**
 * END OF TASK CLASS MUTATORS
 */

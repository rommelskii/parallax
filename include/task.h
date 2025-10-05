#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> // for size_t
#include <string.h>

typedef struct HashMap HashMap;

#define MAX_TABLE_SIZE 50

typedef struct Task 
{
  char* task_class;
  char* task_content; 
} Task;

typedef struct TaskClass
{
  char* task_class_name;
  size_t table_size;
  HashMap* task_class_table; 
} TaskClass;

typedef struct TaskCollection
{
  HashMap* task_collection;
  size_t collection_size;
} TaskCollection;

/**
  * Initializers
  */
Task*           create_task(char* class_of_task, char* task_content);
TaskClass*      create_task_class(char* class_of_task, size_t class_size);
TaskCollection* create_task_collection(size_t collection_size);


/**
  * Adders and getters
  */
Task* get_task(TaskClass* task_class, const char* key);
void  add_task(TaskClass* task_class, Task* new_task);

TaskClass*  get_task_class(TaskCollection* task_collection, const char* key);
void        add_task_class(TaskCollection* task_collection, TaskClass* task_class);

//Misc
void  print_task(Task* task);


#endif //TASK_H

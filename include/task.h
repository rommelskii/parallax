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
  char* task_uuid;
  char* task_class;
  char* task_content; 
} Task;

typedef struct TaskClass
{
  char* task_class_name;
  size_t table_size;
  HashMap* task_class_table; 
} TaskClass;

Task* create_task();
TaskClass* create_task_class();


#endif //TASK_H

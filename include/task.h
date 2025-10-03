#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> // for size_t

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
  //HashTable* task_class_table; 
} TaskClass;

#endif //TASK_H

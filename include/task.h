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
  char* task_content; //this is the unique identifier
} Task;

typedef struct TaskClass
{
  char* task_class_name;
  size_t table_size;
  HashMap* task_class_table; 
} TaskClass;

Task*       create_task();
TaskClass*  create_task_class();


void  set_task_class(Task* task, char* class);
void  set_task_content(Task* task, char* content);
void  set_task_class_name(TaskClass* task_class, char* class_name);
void  set_table(TaskClass* task_class, size_t table_size);

Task* get_task_from_class(TaskClass* task_class, const char* key);
void  add_task_to_class(TaskClass* task_class, Task* new_task);


void  print_task(Task* task);


#endif //TASK_H

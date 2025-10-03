#ifndef TASK_H
#define TASK_H

typedef struct Task 
{
  char* task_uuid;
  char* task_class;
  char* task_content; 
} Task;

typedef struct TaskClass
{
  char* task_class_name;
  HashTable* task_class_table;
} TaskClass;

#endif //TASK_H

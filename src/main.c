#include <stdlib.h>
#include <stdio.h>

#include "argparse.h"
#include "hashmap.h"
#include "task.h"

#define FLAG_INDEX 1
#define FIRST_CONTENT_INDEX 2
#define SECOND_CONTENT_INDEX 3
#define DEFAULT_CLASS "def"

void runtime_test()
{
  HashMap* task_collection = hashmap_create(100);

  Task* t = create_task();  
  set_task_class(t, "test task");
  set_task_content(t, "print new line");

  TaskClass* tc = create_task_class();
  set_task_class_name(tc, "Comarch"); 
  set_table(tc, 50); 
  add_task_to_class(tc, t);

  Task* find_task = task_get(tc->task_class_table, t->task_content, tc->table_size);


  printf("--- BEGIN UNIT TESTS ---\n");
  if (find_task != NULL)
  {
    printf("[WORKING] Task lookup\n");
  } else 
  {
    printf("[ERROR] Task lookup\n");
  }

  task_class_set(task_collection, tc->task_class_name, tc);

  TaskClass* find_task_class = task_class_get(task_collection, tc->task_class_name, tc->table_size);

  if ( find_task_class != NULL)
  {
    printf("[WORKING] Task class lookup\n");
  } else 
  {
    printf("[ERROR] Task class lookup\n");
  }

  printf("--- BEGIN RUNTIME TEST ---\n");
  Task* new_task = create_task();
  set_task_class(new_task, "Test class");
  set_task_content(new_task, "wash the dishes");
  print_task(new_task);

  TaskClass* new_task_class = create_task_class();
  set_task_class_name(new_task_class, "Test class");
  set_table(new_task_class, 50);
  add_task_to_class(new_task_class, t);

  task_class_set(task_collection, new_task_class->task_class_name, new_task_class);

  find_task_class = task_class_get(task_collection, new_task->task_class, 50);
  if (find_task_class != NULL)
  {
    add_task_to_class(find_task_class, new_task);
    printf("working\n");
  }
}

int main(int argc, char* argv[])
{
  const int NUM_OF_ARGS = argc - 1;
  if (NUM_OF_ARGS < 2) 
  {
    printf("Error: Expected 2 or more arguments, got %d\n", NUM_OF_ARGS);
    printf("Usage: prlx [FLAGS] [CONTENT/IDENTIFIER] [CONTENT]\n");
    return -1;
  }

  if ( strcmp(argv[FLAG_INDEX], "-t") == 0 ) 
  {
    runtime_test();
    return 0;
  }


  const char* content = get_content_arg(argv[FIRST_CONTENT_INDEX]);
  char* class = NULL;

  FLAG_TYPE flag = get_flag(argv[FLAG_INDEX]);
  switch (flag)
  {
    case FLAG_CREATE: // 1: content 2: class if necessary
      if (NUM_OF_ARGS == 2) 
      {
        class = "def";
      } else 
      {
        class = get_content_arg(argv[SECOND_CONTENT_INDEX]);
      }
      Task* new_task = create_task();
      set_task_class(new_task, class);
      set_task_content(new_task, content);
      print_task(new_task);
      break;  
    case FLAG_REMOVE:
      printf("Remove flag detected\n");
      break;  
    case FLAG_MODIFY:
      printf("Modify flag detected\n");
      break;  
    case FLAG_LIST:
      printf("List flag detected\n");
      break;  
    case FLAG_INVALID:
      printf("Flag error: %s is not a valid flag.\nConsult 'prlx --help' for info on flags.\n", argv[FLAG_INDEX]);
      break;
  }


  return 0;
}

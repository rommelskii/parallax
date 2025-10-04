#include <stdlib.h>
#include <stdio.h>

#include "argparse.h"
#include "task.h"

#define FLAG_INDEX 1
#define UUID_LENGTH 36
#define FIRST_CONTENT_INDEX 2
#define SECOND_CONTENT_INDEX 3
#define DEFAULT_CLASS "def"

void runtime_test()
{
  Task* t = create_task();  
  char* buf = (char*)malloc(37);
  memset(buf, 0, 37);
  set_task_uuid(t, generate_uuid(buf));
  set_task_class(t, "test task");
  set_task_content(t, "print new line");

  TaskClass* tc = create_task_class();
  set_task_class_name(tc, "Comarch"); 
  set_table(tc, 50); 
  add_task_to_table(tc, t->task_uuid, t, 50);
}

int main(int argc, char* argv[])
{
  const int NUM_OF_ARGS = argc - 1;
  char* uuid_buf = (char*)malloc(UUID_LENGTH+1);
  if (NUM_OF_ARGS < 2) 
  {
    printf("Error: Expected 2 or more arguments, got %d\n", NUM_OF_ARGS);
    printf("Usage: prlx [FLAGS] [CONTENT/IDENTIFIER] [CONTENT]\n");
    return -1;
  }

  if ( strcmp(argv[FLAG_INDEX], "-t") == 0 ) 
  {
    return 0;
  }


  FLAG_TYPE flag = get_flag(argv[FLAG_INDEX]);
  switch (flag)
  {
    case FLAG_CREATE: // 1: content 2: class if necessary
      const char* content = get_content_arg(argv[FIRST_CONTENT_INDEX]);
      char* class = NULL;
      if (NUM_OF_ARGS == 2) 
      {
        class = "def";
      } else 
      {
        class = get_content_arg(argv[SECOND_CONTENT_INDEX]);
      }
      Task* new_task = create_task();
      set_task_uuid(new_task, generate_uuid(uuid_buf));
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

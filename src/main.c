#include <stdlib.h>
#include <stdio.h>

#include "argparse.h"
#include "task.h"

#define FLAG_INDEX 1

void test_harness()
{
  Task* t = create_task();  
  char* buf = (char*)malloc(37);
  memset(buf, 0, 37);


  set_task_uuid(t, generate_uuid(buf, 37));
  set_task_class(t, "test task");
  //set_task_content(t, "print new line");
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
  switch ( get_flag(argv[FLAG_INDEX]) )
  {
    case FLAG_CREATE:
      printf("Create flag detected\n");
      test_harness();
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

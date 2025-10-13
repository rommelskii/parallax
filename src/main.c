#include <stdlib.h>
#include <stdio.h>

#include "argparse.h"
#include "hashmap.h"
#include "task.h"
#include "test.h"

#define FLAG_INDEX 1
#define FIRST_CONTENT_INDEX 2
#define SECOND_CONTENT_INDEX 3


int main(int argc, char* argv[])
{
  const int NUM_OF_ARGS = argc - 1;
  const char* DEFAULT_CLASS = "def";

  if (NUM_OF_ARGS < 2) 
  {
    printf("Error: Expected 2 or more arguments, got %d\n", NUM_OF_ARGS);
    printf("Usage: prlx [FLAGS] [CONTENT/IDENTIFIER] [CONTENT]\n");
    return -1;
  }

  // test entrypoint
  if ( strcmp(argv[FLAG_INDEX], "-t") == 0 ) 
  {
    if ( argparse_test() != 1 ) 
    {
      return EXIT_FAILURE;
    }
    else if ( task_test() != 1 )
    {
      return EXIT_FAILURE;
    }

    hashmap_entry_test();


    return EXIT_SUCCESS;
  }

  const char* content = NULL;
  char* class = NULL;

  FLAG_TYPE flag = get_flag(argv[FLAG_INDEX]);
  switch (flag)
  {
    case FLAG_CREATE: // 1: content 2: class if necessary
      if (NUM_OF_ARGS == 2) 
      {
        class = DEFAULT_CLASS;
      } else 
      {
        class = get_content_arg(argv[SECOND_CONTENT_INDEX]);
      }
      content = get_content_arg(argv[FIRST_CONTENT_INDEX]);
      Task* new_task = create_task(class, content);
      /* Entry point for pushing for IPC
      if ( push_to_fifo(FIFO_FD, new_task) < 0 )
      {
        return EXIT_FAILURE; 
      }
      */
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


  return EXIT_SUCCESS;
}

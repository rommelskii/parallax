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
  printf("--- BATCH 1 TESTS: INITIALIZATION ---\n");
  const size_t COLLECTION_SIZE = 100;

  /**
    * TEST #1a: TASK COLLECTION 
    */
  printf("Test #1a: Task Collection ");
  TaskCollection* task_collection = create_task_collection(COLLECTION_SIZE);
  if (task_collection == NULL)
  {
    printf("[FAILED]\n");
    return;
  } else 
  {
    printf("[PASSED]\n");
  }
  /**
    * TEST #1b: TASK CLASS
    */
  printf("Test #1b: Task Class ");
  const char* CLASS_NAME = "TEST_CLASS";
  const size_t CLASS_SIZE = 50;
  TaskClass* task_class = create_task_class(CLASS_NAME, CLASS_SIZE);
  if (task_class == NULL)
  {
    printf("[FAILED]\n");
    return;
  } else 
  {
    printf("[PASSED]\n");
  }
  /**
    * TEST #1c: TASK CREATION 
    */
  printf("Test #1c: Task Creation ");
  const char* TASK_CONTENT = "TEST_CONTENT";
  Task* task = create_task(CLASS_NAME, TASK_CONTENT);
  if (task == NULL)
  {
    printf("[FAILED]\n");
    return;
  } else 
  {
    printf("[PASSED]\n");
  }

  printf("--- BATCH 2: ATTRIBUTE TESTING ---\n");

  printf("Test #2a: Task class name ");
  if (task->task_class != CLASS_NAME)
  {
    printf("[FAILED]\n");
    return;
  } else
  {
    printf("[PASSED]\n");
  }
  printf("Test #2b: Task content ");
  if (task->task_content != TASK_CONTENT)
  {
    printf("[FAILED]\n");
    return;
  } else
  {
    printf("[PASSED]\n");
  }
  printf("Test #2c: Task class name ");
  if (task_class->task_class_name != CLASS_NAME)
  {
    printf("[FAILED]\n");
    return;
  } else
  {
    printf("[PASSED]\n");
  }
  printf("Test #2d: Task class hashmap ");
  if (task_class->task_class_table == NULL)
  {
    printf("[FAILED]\n");
    return;
  } else
  {
    printf("[PASSED]\n");
  }
  printf("Test #2e: Task collection hashmap ");
  if (task_collection->task_collection == NULL)
  {
    printf("[FAILED]\n");
    return;
  } else
  {
    printf("[PASSED]\n");
  }

  printf("--- BATCH 3: ADDITION TESTS ---\n");
  printf("Test #3a: Task Addition ");
  add_task(task_class, task);
  if ( get_task(task_class, task->task_content) == NULL )
  {
    printf("[FAILED]\n");
    return;
  } else
  {
    printf("[PASSED]\n");
  }

  printf("Test #3b: Task Class Addition ");
  add_task_class(task_collection, task_class);
  if ( get_task_class(task_collection, task_class->task_class_name) == NULL )
  {
    printf("[FAILED]\n");
    return;
  } else
  {
    printf("[PASSED]\n");
  }
  return;
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

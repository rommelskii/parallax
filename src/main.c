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

  printf("--- BATCH 4: DELETION TESTS ---\n");

  printf("Test #4a: Task Deletion ");
  char* content = task->task_content;
  remove_task(task_class, content);
  if ( get_task(task_class, content) != NULL )
  {
    printf("[FAILED]\n");    
  } else {
    printf("[PASSED]\n");    
  }

  printf("Test #4b: Task Class Deletion ");
  char* class = task_class->task_class_name;
  remove_task_class(task_collection, class);
  if ( get_task_class(task_collection, class) != NULL )
  {
    printf("[FAILED]\n");    
  } else {
    printf("[PASSED]\n");    
  }
  
  /**
    * Runtime test
    */

  const size_t RUNTIME_COLLECTION_SIZE = 50; 
  TaskCollection* runtime_task_collection = create_task_collection(RUNTIME_COLLECTION_SIZE);
  TaskClass* runtime_task_class = NULL;
  Task* runtime_task = NULL;

  system("cat ./misc/logo.txt");

  if (runtime_task_collection == NULL)
  {
    printf("Runtime test error: failed to create task collection\n");
    return;
  }
  while (1) 
  {
    char class_name[1024];
    char task_content[1024];
    char yn[16];

    printf("Enter todo class/category: ");
    fgets(class_name, sizeof(class_name), stdin);
    if ( strlen(class_name) > 0 && (class_name[ strlen(class_name) - 1] == '\n') )
    {
      class_name[ strlen(class_name) - 1 ] = '\0';
    }

    if ( strcmp(class_name, "quit") == 0 ) {
      return;
    }

    printf("Enter description: ");
    fgets(task_content, sizeof(task_content), stdin);
    if ( strlen(task_content) > 0 && (task_content[ strlen(task_content) - 1] == '\n') )
    {
      task_content[ strlen(task_content) - 1 ] = '\0';
    }

    printf("--- Summary ---\nclass: '%s'\ncontent:'%s'\n---------------\nContinue? (y/n) ", class_name, task_content);
    fgets(yn, sizeof(yn), stdin);
    if ( strlen(yn) > 0 && (yn[ strlen(yn) - 1] == '\n') )
    {
      yn[ strlen(yn) - 1 ] = '\0';
    }
    if ( strcmp(&yn[0], "y") != 0 )
    {
      continue;
    }

    system("clear");

    runtime_task = create_task(class_name, task_content);
    if (runtime_task == NULL)
    {
      printf("Runtime test error: failed to create task\n");
      return;
    }

    runtime_task_class =get_task_class(runtime_task_collection, class_name);
    if (runtime_task_class == NULL) // class does not exist; create it
    {
      printf("Class '%s' does not exist. Creating...\n", class_name);
      add_task_class(runtime_task_collection, create_task_class(class_name, RUNTIME_COLLECTION_SIZE)); 
      runtime_task_class = get_task_class(runtime_task_collection, class_name);
      add_task(runtime_task_class, runtime_task);
      printf("Appended task to '%s'\n\n", class_name);
    } else {
      if ( get_task(runtime_task_class, task_content) != NULL ) 
      {
        printf("Runtime error: task already exists in '%s'\n", class_name);
        continue;
      }
      printf("Appending task to '%s'...\n", class_name);
      add_task(runtime_task_class, runtime_task);
      printf("Appended task to '%s'\n\n", class_name);
    }
    printf("Enter category name 'quit' to exit runtime test\n");
    system("sleep 4");
    system("clear");
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

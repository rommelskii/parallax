#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include "argparse.h"
#include "hashmap.h"
#include "task.h"
#include "test.h"

/**
 * @file test.c
 * @brief Contains the testing modules for unit and runtime tests
 */

/**
 * we can define a test as a function that returns 1 if passed, and 0 otherwise 
 * 
 * unit tests:
 *  - argument parsing
 *  - tasks
 *  - runtime
 */

int argparse_test()
{
  /**
    * @note These are tests for the procedures in argparse.h
    */
  //test setup
  char* argv[5];

  const int COMMAND_INDEX = 0;
  const int FLAG_INDEX = 1;
  const int CONTENT_INDEX = 2;
  const int CLASS_INDEX =  3;

  //possible values
  const char* command_string = "./prlx";
  const char* create_flag = "-c";
  const char* modify_flag = "-m";
  const char* remove_flag = "-r";
  const char* list_flag   = "-l";
  const char* invalid_flag  = "-k";
  const char* content_string        = "this is a test";
  const char* class_string          = "class";

  printf("---- Flag Tests ----\n");
  /**
    * INITIAL CONDITIONS
    * Procedure: get_flag
    * Condition: valid command with create flag
    * Expected output: FLAG_CREATE 
    */
  argv[COMMAND_INDEX] = command_string;
  argv[FLAG_INDEX] = create_flag;
  argv[CONTENT_INDEX] = content_string;
  argv[CLASS_INDEX] = class_string;

  if ( get_flag(argv[FLAG_INDEX]) != FLAG_CREATE )
  {
    printf("[FAILED] @ create flag\n");
    return 0; 
  } else {
    printf("[PASSED] @ create flag\n");
  }

  /**
    * Procedure: get_flag
    * Condition: valid command with remove flag
    * Expected output: FLAG_REMOVE
    */
  argv[FLAG_INDEX] = remove_flag;
  if ( get_flag(argv[FLAG_INDEX]) != FLAG_REMOVE )
  {
    printf("[FAILED] @ remove flag\n");
    return 0; 
  } else {
    printf("[PASSED] @ remove flag\n");
  }

  /**
    * Procedure: get_flag
    * Condition: valid command with list flag
    * Expected output: FLAG_LIST 
    */
  argv[FLAG_INDEX] = list_flag;
  if ( get_flag(argv[FLAG_INDEX]) != FLAG_LIST )
  {
    printf("[FAILED] @ list flag\n");
    return 0; 
  } else {
    printf("[PASSED] @ list flag\n");
  }
  /**
    * Procedure: get_flag
    * Condition: valid command with modify flag
    * Expected output: FLAG_MODIFY 
    */
  argv[FLAG_INDEX] = modify_flag;
  if ( get_flag(argv[FLAG_INDEX]) != FLAG_MODIFY )
  {
    printf("[FAILED] @ modify flag\n");
    return 0; 
  } else {
    printf("[PASSED] @ modify flag\n");
  }

  /**
    * Procedure: get_flag
    * Condition: invalid valid command (incorrect flag)
    * Expected output: FLAG_INVALID 
    */
  argv[FLAG_INDEX] = invalid_flag;
  if ( get_flag(argv[FLAG_INDEX]) != FLAG_INVALID )
  {
    printf("[FAILED] @ invalid flag\n");
    return 0; 
  } else {
    printf("[PASSED] @ invalid flag\n");
  }

  printf("---- Content Extraction Tests ----\n");
  /**
    * Procedure: get_content_arg
    * Condition: valid command with standard content
    * Expected output: extracted content_string 
    */
  char* test_content = get_content_arg(argv[CONTENT_INDEX]);
  if ( strcmp(test_content, content_string) != 0 )
  {
    printf("[FAILED] @ content string extraction\n");
    return 0;
  } else {
    printf("[PASSED] @ content string extraction\n");
  }

  /**
    * Procedure: get_content_arg
    * Condition: valid command with standard content
    * Expected output: extracted content_string 
    */
  char* test_class = get_content_arg(argv[CLASS_INDEX]);
  if ( strcmp(test_class, class_string) != 0 )
  {
    printf("[FAILED] @ class string extraction\n");
    return 0;
  } else {
    printf("[PASSED] @ class string extraction\n");
  }
  return 1;
}

int task_test()
{
  // initial conditions
  Task* test_task = NULL;
  TaskClass* test_task_class = NULL;
  TaskCollection* test_task_collection = NULL;
  const char* CLASS = "class";
  const char* CONTENT = "test content";
  const size_t TABLE_SIZE = 100;

  printf("---- Task Structures Test ----\n");
  //Test 1: Task Creation
  test_task = create_task(CLASS, CONTENT);
  if (test_task == NULL)
  {
    printf("[FAILED] @ task creation\n");
    return 0;
  } else if ( test_task->task_class != CLASS )
  {
    printf("[FAILED] @ task class initialization\n");
    return 0;
  } else if ( test_task->task_content != CONTENT )
  {
    printf("[FAILED] @ task content initialization\n");
    return 0;
  } else {
    printf("[PASSED] @ task initialization\n");
  }

  test_task_class = create_task_class(CLASS, TABLE_SIZE);
  if (test_task_class == NULL)
  {
    printf("[FAILED] @ task class creation\n");
    return 0;
  } else if (test_task_class->task_class_name == NULL)
  {
    printf("[FAILED] @ task class name initialization\n");
    return 0;
  } else if (test_task_class->table_size != TABLE_SIZE)
  {
    printf("[FAILED] @ task class table size initialization\n");
    return 0;
  }  else if (test_task_class->task_class_table == NULL)
  {
    printf("[FAILED] @ task class table initialization\n");
    return 0;
  } else {
    printf("[PASSED] @ task class initialization\n");
  }

  test_task_collection = create_task_collection(TABLE_SIZE);
  if (test_task_collection == NULL)
  {
    printf("[FAILED] @ task collection creation\n");
    return 0;
  } else if (test_task_collection->collection_size != TABLE_SIZE)
  {
    printf("[FAILED] @ task collection table size initialization\n");
    return 0;
  } else if (test_task_collection->task_collection == NULL)
  {
    printf("[FAILED] @ task collection table initialization\n");
    return 0;
  } else {
    printf("[PASSED] @ task collection initialization\n");
  }
  //end of task initialization procedures

  //start of hashmap operations
  add_task(test_task_class, test_task);
  add_task_class(test_task_collection, test_task_class);
  
  Task* find_task = get_task(test_task_class, CONTENT);
  if (find_task == NULL)
  {
    printf("[FAILED] @ task lookup\n");
    return 0;
  } else {
    printf("[PASSED] @ task lookup\n");
  }
  
  Task* find_task_class = get_task_class(test_task_collection, CLASS);
  if (find_task_class == NULL)
  {
    printf("[FAILED] @ task class lookup\n");
    return 0;
  } else {
    printf("[PASSED] @ task class lookup\n");
  }

  remove_task(test_task_class, CONTENT);
  find_task = get_task(test_task_class, CONTENT);
  if (find_task != NULL)
  {
    printf("[FAILED] @ task deletion\n");
    return 0;
  } else {
    printf("[PASSED] @ task deletion\n");
  }

  remove_task_class(test_task_collection, CLASS);
  find_task_class = get_task_class(test_task_collection, CLASS);
  if (find_task_class != NULL)
  {
    printf("[FAILED] @ task class deletion\n");
    return 0;
  } else {
    printf("[PASSED] @ task class deletion\n");
  }
  //end of hashmap operations
  return 1;
}

void runtime_test()
{
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

    printf("---- Summary ----\nclass: '%s'\ncontent:'%s'\n---------------\nContinue? (y/n) ", class_name, task_content);
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



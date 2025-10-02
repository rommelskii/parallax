#include <stdlib.h>
#include <stdio.h>

#include "argparse.h"

int main(int argc, char* argv[])
{
  const int NUM_OF_ARGS = argc - 1;
  if (NUM_OF_ARGS < 2) 
  {
    printf("Error: Expected 2 or more arguments, got %d\n", NUM_OF_ARGS);
    printf("Usage: prlx [FLAGS] [CONTENT/IDENTIFIER] [CONTENT]\n");
    return -1;
  }


  return 0;
}

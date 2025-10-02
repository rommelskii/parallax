#include "argparse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FLAG_LENGTH 2

FLAG_TYPE get_flag(char* flag_string)
{
  const size_t ARG_FLAG_LENGTH = strnlen(flag_string, FLAG_LENGTH);
  if (flag_string == NULL || ARG_FLAG_LENGTH != 2)
  {
    printf("Flag error: empty or malformed flag (len: %zu)\n", ARG_FLAG_LENGTH);
    return FLAG_INVALID; 
  }

  if ( strncmp( flag_string, "-c", ARG_FLAG_LENGTH ) == 0 )
  {
    return FLAG_CREATE;
  } 
  else if ( strncmp ( flag_string, "-r", ARG_FLAG_LENGTH) == 0 )
  {
    return FLAG_REMOVE;
  }
  else if ( strncmp ( flag_string, "-m", ARG_FLAG_LENGTH) == 0 )
  {
    return FLAG_MODIFY;
  }
  else if ( strncmp ( flag_string, "-l", ARG_FLAG_LENGTH) == 0 )
  {
    return FLAG_LIST;
  }
}

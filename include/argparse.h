#ifndef ARGPARSE_H
#define ARGPARSE_H

typedef enum 
{
  FLAG_CREATE,
  FLAG_MODIFY,
  FLAG_REMOVE,
  FLAG_LIST,
  FLAG_INVALID
} FLAG_TYPE;

FLAG_TYPE get_flag(char* flag_string);


#endif //ARGPARSE_H

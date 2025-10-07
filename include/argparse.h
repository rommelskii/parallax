#ifndef ARGPARSE_H
#define ARGPARSE_H

/**
  * @file argparse.h
  * @brief Contains functions for extracting content from the argument vector. 
  *
  * Manipulates the caller buffer to extract the content.
  */

/**
  * @brief Possible flag types
  */
typedef enum 
{
  FLAG_CREATE, /**< -c */
  FLAG_MODIFY, /**< -m*/
  FLAG_REMOVE, /**< -r*/
  FLAG_LIST, /**< -l*/
  FLAG_INVALID /**< invalid/malformed flag*/
} FLAG_TYPE;


/**
  * @brief Assigns a string to its corresponding flag type.
  * 
  * Compares the argument with the possible flags.
  *
  * @param flag_string Pointer to the flag string in the argument vector
  * @return Flag type corresponding to the input flag string
  */
FLAG_TYPE get_flag(char* flag_string);

/**
  * @brief Safely extracts any of the non-flag arguments in the argument vector. 
  *
  * @param str_arg Pointer to the argument string
  * @return Pointer to the extracted argument.
  */
const char* get_content_arg(char* str_arg); 

#endif //ARGPARSE_H

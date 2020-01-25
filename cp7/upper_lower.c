#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS     0
#define NO_ARGV0    1
#define BAD_NAME    2

int main(int argc, char *argv[])
{
  int ErrorStatus = SUCCESS;
  int (*convert)(int c) = NULL; /* pointer to a function */
  int c = 0;

  /* check if args exist */
  if (SUCCESS == ErrorStatus) {
    if (0 >= argc) {
      printf("Your...");
      ErrorStatus = NO_ARGV0;
    }
  }

  /* check for valid names in the argv[0] string */
  if(SUCCESS == ErrorStatus)
    {
      if(0 == strcmp(argv[0], "lower"))
        {
          convert = tolower;
        }
      else if(0 == strcmp(argv[0], "upper"))
        {
          convert = toupper;
        }
      else
        {
          printf("This program performs two functions.\n");
          printf("If the executable is named lower then it converts all the input on stdin to lowercase.\n");
          printf("If the executable is named upper then it converts all the input on stdin to uppercase.\n");
          printf("As you have named it %s it prints this message.\n", argv[0]);
          ErrorStatus = BAD_NAME;
        }
    }

  /* ok so far, keep looping until EOF is encountered */
  if(SUCCESS == ErrorStatus)
    {
      while(EOF != (c = getchar()))
        {
          putchar((*convert)(c));
        }
    }

  /* and return what happened */
  return SUCCESS == ErrorStatus ? EXIT_SUCCESS : EXIT_FAILURE;
}

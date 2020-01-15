/*  */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
  printf("\nchar:\n");
  printf("Size of char: %d bits\n", CHAR_BIT);
  printf("Maximum value of char: %d\n", CHAR_MAX);
  printf("Minimum value of char: %d\n", CHAR_MIN);
  printf("Maximum value of signed char: %d\n", SCHAR_MAX);
  printf("Minimum value of signed char: %d\n", SCHAR_MIN);
  printf("Maximum value of unsigned char: %d\n", UCHAR_MAX);
  printf("\nint:\n");
  //printf("Size of int: %d bits\n", INT_BIT);
  printf("Maximum value of int: %d\n", INT_MAX);
  printf("Minimum value of int: %d\n", INT_MIN);
  printf("Maximum value of unsigned int: %u\n", UINT_MAX);
  printf("\nlong:\n");
  printf("Maximum value of long: %ld\n", LONG_MAX);
  printf("Minimum value of long: %ld\n", LONG_MIN);
  printf("Maximum value of unsigned long: %lu\n", ULONG_MAX);
  printf("\nshort:\n");
  printf("Maximum value of short: %d\n", SHRT_MAX);
  printf("Minimum value of short: %d\n", SHRT_MIN);
  printf("Maximum value of unsigned short: %u\n", USHRT_MAX);
  return EXIT_SUCCESS;
}

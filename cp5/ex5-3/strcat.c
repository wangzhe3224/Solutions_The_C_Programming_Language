#include <stdio.h>
#include <stdlib.h>

/* strcat: concatenate t to end of s; s must big enough */
void mstrcat(char *s, const char *t)
{
  while (*s)
    s++;                        /* find end of s */

  while (*t)
    *s++ = *t++;

  *s = '\0';
}

int main(void)
{
  char s[100] = "ab\0c";
  char t[100] = "def";
  mstrcat(s, t);
  puts(s);
  return EXIT_SUCCESS;
}

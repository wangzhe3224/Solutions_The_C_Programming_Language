#include <stdio.h>
#include <stdlib.h>

/* strend: returns 1 if string t occurs at the end of s
 zero otherwise */
int strend(const char *s, const char *t)
{
  int ls, lt;

  for (ls=0; *(s+ls); ++ls);    /* find length of s */
  for (lt=0; *(t+lt); ++lt);

  if (ls > lt) {
    s += ls - lt;               /* find s to where t should start */
    while (*s++ == *t++)
      if (!*s)
        return 1;
  }

  return 0;                     /* false */
}

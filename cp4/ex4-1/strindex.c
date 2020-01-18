#include <stdio.h>

/* strindex: returns the position of the rightmost occurrence of t in s,
   or -1 if there is none */
int strindex(char s[], char t[])
{
  int i, j, k, rindex;

  rindex = -1;
  for (i=0; s[i] != '\0'; i++) {
    /* check if t starts at index i */
    for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++);

    if (k > 0 && t[k] == '\0')  /* exist */
      rindex = i;
  }

  return rindex;
}

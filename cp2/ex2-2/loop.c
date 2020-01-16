/* Original Loop:
   for (i=0; i < lim - 1 && (c=getchar()) != '\n' && (c=getchar()) != EOF; ++i)
     s[i] = c;
 */
#include <stdio.h>
#include <stdlib.h>

#define LIMIT 512

int main()
{
  int i;
  int c, lim;
  char s[LIMIT];

  lim = LIMIT;
  i = 0;
  while (i < lim-1) {
    c = getchar();
    if (c == '\n')
      lim = 0;
    else if (c == EOF)
      lim = 0;
    else
      s[i++] = c;
  }

  s[i] = '\0';
  printf("%s\n", s);

  return EXIT_SUCCESS;
}

/* delete each character in string 1 that
 * matches any char in string 2
 */
#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

void squeeze(char s1[], char s2[]);

int main()
{
  char s1[] = "abcd";
  char s2[] = "bc";
  squeeze(s1, s2);
  printf("%s\n", s1);

  return EXIT_SUCCESS;
}

/* squeeze: delete all chars from s1 that match any in s2 */
void squeeze(char s1[], char s2[])
{
  int i, j, k;
  int instr2;

  for (i=j=0; s1[i] != '\0'; i++) {
    instr2 = FALSE;
    for (k=0; s2[k] != '\0' && !instr2; k++)
      if (s2[k] == s1[i])       /* compare 1 by 1 */
        instr2 = TRUE;
    if (!instr2)
      s1[j++] = s1[i];
  }

  s1[j] = '\0';
}

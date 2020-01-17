#include <stdio.h>
#include <string.h>

int any(char s1[], char s2[]);

int main()
{
  char s1[] = "abcd";
  char s2[] = "cd";

  printf("%d\n", any(s1, s2));
  /* expexting: 2 */

  strcpy(s1, "abcd");
  strcpy(s2, "dd");

  printf("%d\n", any(s1, s2));
  /* expexting: 3 */

  return 0;
}

int any(char s1[], char s2[])
{
  for (int i=0; s2[i] != '\0'; ++i) {
    for (int j=0; s1[j] != '\0'; ++j) {
      if (s1[j] == s2[i])
        return j;               /* find location */
    }
  }

  return -1;
}

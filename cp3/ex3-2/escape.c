#include <stdio.h>

#define TRUE  1
#define FALSE 0

/* escape: converts newlines and tab int visible escape sequences */
void escape(char s[], char t[])
{
  int i, j;

  for (i = j = 0; t[i] != '\0'; ++i) {
    switch (t[i]) {
    case '\n':
      s[j++] = '\\';
      s[j++] = 'n';
      break;

    case '\t':
      s[j++] = '\\';
      s[j++] = 't';
      break;

    default:
      s[j++] = t[i];
      break;
    }
  }

  s[j] = '\0';
}

/* unescape:  */
void unescape(char s[], char t[])
{
  int i, j;
  int slash;

  slash = FALSE;

  for (i = j = 0; t[i] != '\0'; ++i) {
    switch (t[i]) {
    case '\\':
      slash = TRUE;
      break;
    case 'n':
      if (slash) {
        s[j++] = '\n';
        slash = FALSE;
        break;
      }
    case 't':
      if (slash) {
        s[j++] = '\t';
        slash = FALSE;
      }
    default:
      s[j++] = t[i];
      break;
    }
  }

  s[j] = '\0';
}

int main()
{
  int i;
  char c, s[1024], t[1024];

  i=0;
  while ((c = getchar()) != EOF) {
    t[i++] = c;
  }

  t[i] = '\0';

  printf(">%s\n", t);
  escape(s, t);
  printf(">%s\n", s);
  unescape(t, s);
  printf(">%s\n", t);

  return 0;
}

/* strncmp: compare at most n chars of s and t */
int strncmp(char *s, const char *t, int n)
{
  /* find the first different char and compare */
  for (; *s == *t && n-- > 0; s++, t++)
    if (*s == '\0' || n == 0)
      return 0;                 /* s is same as t in first n chars */

  return *s - *t;               /* chat is just int */
}

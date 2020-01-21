/* strncat: concate at most n chars of t to the end of s;
 s is big enough */
void strncat(char *s, const char *t, int n)
{
  while (*s)                    /* points to the end of string s */
    s++;

  while (*t && n-- > 0)
    *s++ = *t++;

  *s = '\0';
}

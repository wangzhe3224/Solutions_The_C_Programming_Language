/* strncpy: copy at most n chars of t to s */
void strncpy(char *s, const char *t, int n)
{
  while (*t && n-- > 0)         /* wow... */
    *s++ = *t++;

  *s = '\0';                    /* end of string */
}

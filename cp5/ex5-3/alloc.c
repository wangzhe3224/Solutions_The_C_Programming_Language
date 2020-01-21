#define ALLOCSIZE   10000       /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage of alloc */
static char *allocp;             /* next free position */

/* alloc: return pointer to n chars */
char *alloc(int n)
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { /* enough space remains */
    allocp += n;                            /* allocate n char space */
    return allocp - n;
  } else {
    return 0;                   /* not enough */
  }
}

/*  */
void afree(char *p)
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}

int mstrlen(char *s)
{
  char *p = s;
  while (*p != '\0')
    p++;

  return p - s;
}

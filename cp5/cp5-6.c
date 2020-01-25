#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           /* max lines to be stored */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main()
{
  int nlines;                   /* numbers of inputs line read */

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 100              /* max length of any input */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || p = alloc(len) == NULL)
      return -1;
    else {
      line[len-1] = '\0';       /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;    /* put string */
    }

  return nlines;
}

/* writelines: write output line */
void writelines(chatr *lineptr[], int nlines)
{
  int i;
  for (i=0; i<nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* swap */
void swap(char *v[], int i, int j)
{
  char *tmp;

  tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}

/* qsort: sort v[left] ... v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
  int i, last;

  if (left >= right)
    return;

  swap(v, left, (left+right)/2);
  last = left;

  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[right]) < 0)
      swap(v, ++last, i);

  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last+1, right);
}

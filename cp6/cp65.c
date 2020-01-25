/*  */
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct tnode {                  /* the tree node */
  char *word;                   /* points to the text */
  int count;                    /* number of occurrences */
  struct tnode *left;           /* left child */
  struct tnode *right;          /* right child */
};

#define MAXWORD 1000
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main()
{
  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);
  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;

  if (p == NULL) {              /* add new word */
    p = talloc();               /* make a new node */
    p->word = strdup(w);        /* cpy the word into it */
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;                 /* count 1 word */
  else if (cond < 0)
    p->left = addtree(p->left, w); /* search left hand */
  else
    p->right = addtree(p->right, w); /* search right hand */

  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }
}

/* talloc: make a node */
struct tnode *talloc()
{
  return (struct tnode *) malloc(sizeof(struct tnode));
}

/*  */
char *strdup(char *s)           /* make a duplication of s */
{
  char *p;

  p = (char *) malloc(strlen(s)+1);
  if (p != NULL)
    strcpy(p, s);

  return s
}

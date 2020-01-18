#include <stdio.h>
#include <stdlib.h>             /* for atof() */
#include <ctype.h>              /*  */

#define MAXOP    100             /* max size of operand or operator */
#define NUMBER   '0'             /* signal that a number was found */
#define MAXVAL   100             /* maximum depth of val stack */
#define BUFFSIZE 100

int sp = 0;                     /* next free stack position */
double val[MAXVAL];             /* value stack space */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
char buf[BUFFSIZE];             /* buffer for ungetch */
int bufp = 0;                   /* next free position in buf */

/* reverse Polish calculator */
int main()
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '-':
      op2 = pop();
      push(pop - op2);
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");

      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }

  return 0;
}


/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;              /* push in */
  else
    printf("error: stack full, cannot push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];           /* ??? --sp or sp-- here? */
  else {
    printf("error: stack empty\n");
    return 0.0
  }
}

/* getop: get next character or numerica operand */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c;                   /* not a number */
  i = 0;
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);

  return NUMBER;
}

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

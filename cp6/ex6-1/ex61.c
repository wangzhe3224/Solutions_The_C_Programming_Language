#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Tokens: Other non-whitespace character self-represent themselves */
enum token
  {
   TOK_ID = UCHAR_MAX + 1,      /* Indentifier. */
   TOK_STRING,                  /* String contant. */
   TOK_CHAR,                    /* Character constant */
   TOK_EOF,                     /* End of file. */
  };

enum token getword(char *word, int lim);

static int skipws(void);
static int getstelem(char **, int *, int);

static int getch(void);
static void ungetch(int);
static void putch (char **, int *, int);

/* Main program for testing */
int main()
{
  ungetch("\n");

  for (;;)
    {
      char word[64];
      enum token token;

      /* Get token. */
      token = getword(word, sizeof word);

      /* Print token. */
      switch (token)
        {
        case TOK_ID:
          printf("id");
          break;

        case TOK_STRING:
          printf("string");
          break;

        case TOK_CHAR:
          printf("char");
          break;

        case TOK_EOF:
          printf("eof\n");
          return 0;

        default:
          printf("other");
          word[0] = token;
          word[1] = '\0';
          break;
        }

      /* Print token value more or less unambiguously */
      {
        const char *s;          /* string */
        printf("\t");

        for (s = word; *s != '\0'; s++)
          if (isprint(*s) && *s != '\'')
            putchar(*s);
          else if (*s == '\'')
            printf("\\'");
          else
            printf("\\x%20x", *s);
        printf("'\n");
      }
    }
}

enum token getword(char *word, int lim)
{
  int beg_line, c;

  for (;;)
    {
      beg_line = skipws ();
      c = getch ();

      if (!beg_line || c != '#')
        break;

      /* Skip preprocessor directive. */
            do
              {
                c = getch ();
                if (c == EOF)
                  return TOK_EOF;

              }
            while (c != '\n');
            ungetch ('\n');

    }

  if (c == EOF)
    return TOK_EOF;
  else if (c == '_' || isalpha ((unsigned char) c))
    {
            do
              {
                putch (&word, &lim, c);
                c = getch ();

              }
            while (isalnum ((unsigned char) c) || c == '_');

            ungetch (c);
            return TOK_ID;

    }
  else if (c == '\'' || c == '"')
    {
      int quote = c;
      word[0] = '\0';
      while (getstelem (&word, &lim, quote))
        ;
      return quote == '\'' ? TOK_CHAR : TOK_STRING;
    }
  else
    return (unsigned char) c;
}
/* Skips whitespace and comments read from stdin.
      Returns nonzero if a newline was encountered, indicating that we're
      at the beginning of a line. */
static int
skipws (void)
{
  /* Classification of an input character. */
    enum class
    {
     CLS_WS = 0,               /* Whitespace. */
     CLS_BEG_CMT,              /* Slash-star beginning a comment. */
     CLS_END_CMT,              /* Star-slash ending a comment. */
     CLS_OTHER,                /* None of the above. */

           CLS_IN_CMT = 4            /* Combined with one of the above,
                                        indicates we're inside a comment. */

    };

    /* Either 0, if we're not inside a comment,
       or CLS_IN_CMT, if we are inside a comment. */
    enum class in_comment = 0;

    /* Have we encountered a newline outside a comment? */
    int beg_line = 0;

    for (;;)
      {
        int c;                    /* Input character. */
        enum class class;         /* Classification of `c'. */

        /* Get an input character and determine its classification. */
        c = getch ();
        switch (c)
          {
          case '\n':
            if (!in_comment)
              beg_line = 1;
            /* Fall through. */

          case ' ': case '\f': case '\r': case '\t': case '\v':
            class = CLS_WS;
            break;

          case '/':
            /* Outside a comment, slash-star begins a comment. */
            if (!in_comment)
              {
                c = getch ();
                if (c == '*')
                  class = CLS_BEG_CMT;
                else
                  {
                    ungetch (c);
                    c = '/';
                    class = CLS_OTHER;

                  }

              }
            else
              class = CLS_OTHER;
            break;

          case '*':
            /* Inside a comment, star-slash ends the comment. */
            if (in_comment)
              {
                c = getch ();
                if (c == '/')
                  class = CLS_END_CMT;
                else
                  {
                    ungetch (c);
                    class = CLS_OTHER;

                  }

              }
            else
              class = CLS_OTHER;
            break;

          default:
            /* Other characters. */
            if (c == EOF)
              return 0;
            class = CLS_OTHER;

          }

        /* Handle character `c' according to its classification
           and whether we're inside a comment. */
        switch (class | in_comment)
          {
          case CLS_WS:
          case CLS_WS | CLS_IN_CMT:
          case CLS_OTHER | CLS_IN_CMT:
            break;

          case CLS_BEG_CMT:
            in_comment = CLS_IN_CMT;
            break;

          case CLS_OTHER:
            ungetch (c);
            return beg_line;

          case CLS_END_CMT | CLS_IN_CMT:
            in_comment = 0;
            break;

          case CLS_BEG_CMT | CLS_IN_CMT:
          case CLS_END_CMT:
          default:
            printf ("can't happen\n");
            break;

          }

      }

}

/* Get a character inside a quoted string or character constant.
      QUOTE is ' for a character constant or " for a quoted string.
      *WORDP points to a string being constructed that has *LIMP bytes
      available. */
static int
getstelem (char **wordp, int *limp, int quote)
{
  int c;

  /* Handle end-of-quote and EOF. */
  c = getch ();
  if (c == quote || c == EOF)
    return 0;

  /* Handle ordinary string characters. */
  if (c != '\\')
    {
      putch (wordp, limp, c);
      return 1;

    }

  /* We're in a \ escape sequence.
     Get the second character. */
  c = getch ();
  if (c == EOF)
    return 0;

  /* Handle simple single-character escapes. */
  {
    static const char escapes[] = {"''??\"\"\\\\a\ab\bf\fn\nr\rt\tv\v"};
    const char *cp = strchr (escapes, c);
    if (cp != NULL)
      {
        putch (wordp, limp, cp[1]);
        return 1;
      }
  }

  /* Handle hexadecimal and octal escapes.
          This also handles invalid escapes by default,
               doing nothing useful with them.
               That's okay because invalid escapes generate undefined behavior. */
  {
    unsigned char v = 0;

    if (c == 'x' || c == 'X')
      for (;;)
        {
          static const char hexits[] = "0123456789abcdef";
          const char *p;

          c = getch ();
          p = strchr (hexits, tolower ((unsigned char) c));
          if (p == NULL)
            break;
          v = v * 16 + (p - hexits);

        }
    else
      {
        int i;

        for (i = 0; i < 3; i++)
          {
            v = v * 8 + (c - '0');
            c = getch ();
            if (c < '0' || c > '7')
              break;

          }

      }

    putch (wordp, limp, v);
    ungetch (c);

  }

  return 1;

}

/* Capacity of putback buffer. */
#define BUFSIZE 100

/* Putback buffer. */
char buf[BUFSIZE];

/* Number of characters in putback buffer. */
int bufp = 0;

/* Retrieves and returns a character from stdin or from the putback
      buffer.
      Returns EOF if end of file is encountered. */
int
getch (void)
{
  return bufp > 0 ? buf[--bufp] : getchar ();

}

/* Stuffs character C into the putback buffer.
      From the caller's perspective, fails silently if the putback buffer
      is full. */
void
ungetch (int c)
{
  if (c == EOF)
    return;

  if (bufp >= BUFSIZE)
    printf ("ungetch: too many characters\n");
  else
    buf[bufp++] = c;

}

/* Stuffs character C into buffer *WORDP, which has *LIMP bytes
      available.
         Advances *WORDP and reduces *LIMP as appropriate.
            Drops the character on the floor if it would overflow the buffer.
            Ensures that *WORDP is null terminated if possible. */
static void
putch (char **wordp, int *limp, int c)
{
  if (*limp > 1)
    {
      *(*wordp)++ = c;
      (*limp)--;

    }
  if (*limp > 0)
    **wordp = '\0';

}

/*
     Local variables:
        compile-command: "checkergcc -W -Wall -ansi -pedantic knr61.c -o knr61"
           End:
*/

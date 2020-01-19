#include <stdio.h>
#include <stdlib.h>
#include "getint.h"

/* sample implementation of getint */
int main(void)
{
    int i, r;

    r = getint(&i);
    if (r > 0)
        printf("%d\n", i);
    else if (r == 0)
        printf("not a number\n");
    else if (r == EOF)
        printf("end of file\n");
    else
        printf("wtf happend?\n");
    return EXIT_SUCCESS;
}

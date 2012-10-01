#include <stdio.h>
#include "dp.h"

int main(int argc, char *argv[])
{
    char a[25];
    char b[25];
    char c[25];
    
    scanf("%s%s", a, b);

    lcs(a, b, c);

    puts(c);
    
    return 0;
}

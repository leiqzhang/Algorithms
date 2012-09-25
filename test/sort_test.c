#include <stdio.h>
#include "sort.h"
#include "tool.h"

void print(int *array, int len)
{
    int i = 0;
    for (i = 0; i < len; ++i) {
        printf("%d ", array[i]);
    }
    putchar('\n');
}

int main(int argc, char *argv[])
{
    int data[]= {10, 19, 23, 3, 8, 29};
    print(data, 6);
    isort(data, 6, less);
    print(data, 6);
    return 0;
}

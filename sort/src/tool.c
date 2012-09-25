/* some small functions to do the job well. */

/*
 * To swap the value of two integers.
 */
void swap(int *first, int *second)
{
    if (first != second) {      /* to avoid the bug caused by same pointer */
        *first = *first ^ *second;
        *second= *first ^ *second;
        *first = *first ^ *second;
    }
}

int less(int a, int b)
{
    return a < b ? 1 : 0;
}

int greater(int a, int b)
{
    return a > b ? 1 : 0;
}

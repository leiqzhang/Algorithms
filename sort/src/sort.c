typedef int (*fun)(int,int);
/* 插入排序 */
void isort(int *array, int len, fun compare)
{
    int i = 0, j = 0;
    int key;

    for (i = 1; i < len; ++i) {
        key = array[i];
        j = i - 1;

        while (compare(key,array[j]) && j >= 0) {
            array[j + 1] = array[j];
            --j;
        }

        array[j + 1] = key;
    }
}

#include <stdio.h>
#include "sort.h"
#include "tool.h"

void menu()
{
    printf("====排序算法测试====\n");
    printf("1. 插入排序.\n");
    printf("2. 冒泡排序.\n");
    printf("3. 希尔排序.\n");
    printf("4. 归并排序.\n");
    printf("5. 堆排序.\n");
    printf("6. 快速排序.\n");
    printf("7. 计数排序.\n");
    printf("8. 基数排序.\n");
    printf("\n请选择[1-9]: ");
}

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
    int data[]= {6, 5, 3, 1, 4, 2};
    int select = 0;
    
    menu();
    scanf("%d", &select);

    printf("排序前:\n");
    print(data, 6);

    switch (select) {
    case 1:
        isort(data, 6, less);
        break;
    case 2:
        bsort(data, 6, less);
        break;
    case 3:
        ssort(data, 6, less);
        break;
    case 4:
        msort(data, 6, less);
        break;
    case 5:
        hsort(data, 6, less);
        break;
    case 6:
        fsort(data, 6, less);
        break;
    case 7:
        /* csort(data, 6, less); */
        break;
    case 8:
        /* rsort(data, 6, less); */
        break;
    }

    printf("\n排序后:\n");
    print(data, 6);
    return 0;
}

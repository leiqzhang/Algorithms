#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sort.h"
#include "tool.h"

/* 排序时使用的比较函数类型 */
typedef int (*CmpFun)(int , int);
/* 排序算法类型 */
typedef void (*SortFun)(int *, int, int (*fun)(int ,int));

/* 初始化测始数据 */
void build_data(int *data, int len);

/* 测试排序算法正确性以及效率 */
void test(SortFun sortfun, int *data, int len, CmpFun cmp);

/* 打印数组内容 */
void print(int *data, int len);

/* 打印程序使用方法 */
void usage();

int main(int argc, char *argv[])
{

    int opt = 0;
    int num = 0;                /* 排序测试规模 */
    int *data = NULL;
    int flag = 0;
    CmpFun cmp = less;
    const char *optstr = "n:ibsmhfcr";

    if (1 == argc)
        usage();
    
    while ((opt = getopt(argc, argv, optstr)) != -1) {
        switch(opt) {
        case 'n':               /* 选项n与其参数确定测试规模 */
            num = atoi(optarg);
            data = (int *)calloc(sizeof(int), num);
            build_data(data, num);
            printf("排序前:\n");
            print(data, num);
            flag = 1;
            break;
        case 'i':               /* 除n外的其余选项确定测试的排序方法 */
            test(isort, data, num, cmp);
            break;
        case 'b':
            test(bsort, data, num, cmp);
            break;
        case 's':
            test(ssort, data, num, cmp);
            break;
        case 'm':
            test(msort, data, num, cmp);
            break;
        case 'h':
            test(hsort, data, num, cmp);
            break;
        case 'f':
            test(fsort, data, num, cmp);
            break;
        case 'c':
            test(csort, data, num, cmp);
            break;
        case 'r':
            test(rsort, data, num, cmp);
            break;
        default:
            usage();
            break;
        }
    }

    if (1 == flag) {
    /* 打印结果,在测试规模比较大的时候建议重定向到文件 */
        printf("\n排序后:\n");
        print(data, num);           
        free(data);
    }
    return 0;
}

/* 根据测试规模来初始化测试数据 */
void build_data(int *data, int len)
{
    int index = 0;

    srand((unsigned)time(0));

    for (; index < len; ++index)
        data[index] = rand() % len;
}

/* 测试排序算法,测试参数包括:排序用时,排序结果 */
void test(SortFun sortfun, int *data, int len, CmpFun cmp)
{
    clock_t begin, end;

    begin = clock();
    sortfun(data, len, cmp);
    end = clock();

    printf("\n排序过程耗时: %.20fs\n", (double)(end - begin) / CLOCKS_PER_SEC);
}

/* 打印数组内容 */
void print(int *data, int len)
{
    int i;
    for(i = 0; i < len; ++i)
        printf("%d ", data[i]);
    printf("\n");
}

/* 打印程序使用方法 */
void usage()
{
    printf("用法 : sort_test -n 测试规模 排序类型.\n");
    printf("测试规模是一个整数值,如过测试规模比较大,\
建议将程序输出重定向至文件,然后使用文本处理工具进行分析.\n");

    printf("\n排序类型及相应参数如下:\n");
    printf("-i           --直接插入排序.\n");
    printf("-b           --冒泡排序.\n");
    printf("-s           --希尔排序.\n");
    printf("-m           --归并排序.\n");
    printf("-h           --堆排序.\n");
    printf("-f           --快速排序.\n");
    printf("-c           --计数排序.\n");
    printf("-r           --基数排序(内部使用归并排序).\n");
}

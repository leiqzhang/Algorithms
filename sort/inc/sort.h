#ifndef _SORT_H
#define _SORT_H

typedef int (*fun)(int,int);


/* 插入排序 */
void isort(int *array, int len, fun compare);

/* 冒泡排序 */
void bsort(int *array, int len, fun compare);

/* 希尔排序 */
void ssort(int *array, int len, fun compare);

/* 归并排序 */
void msort(int *array, int len, fun compare);

/* 堆排序 */
void hsort(int *array, int len, fun compare);

/* 快速排序 */
void fsort(int *array, int len, fun compare);

/* 计数排序 */
void csort(int *array, int len, fun compare);

/* 基数排序 */
void rsort(int *array, int len, fun compare);

#endif

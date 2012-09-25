#ifndef _SORT_H
#define _SORT_H

typedef int (*fun)(int,int);

/* 插入排序 */
void isort(int *array, int len, fun compare);

#endif

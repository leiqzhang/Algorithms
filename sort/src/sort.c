#include <stdlib.h>

typedef int (*fun)(int,int);

/* 插入排序 */
void isort(int *array, int len, fun compare)
{
    int i = 0, j = 0;
    int key;                    /* 关键字值 */
    int step = 1;               /* 为与希尔排序形式统一 */

    /* 按step为步长进行插入排序 */
    /* 和希尔排序对比一下看看？ */
    for (i = step; i < len; i += step) {
        key = array[i];
        j = i - step;

        /* 将array[i]插入到array[0...i-1]中去 */
        while (!compare(array[j], key) && j >= 0) {
            array[j + step] = array[j];
            j -= step;
        }

        array[j + step] = key;
    }
}

/* 冒泡排序 */
void bsort(int *array, int len, fun compare)
{
    int i = 0, j = 0;

    for (; i != len; ++i) {
        for (j = 0; j != len - i - 1; ++j) {
            if(!compare(array[j], array[j + 1]))
               swap(array + j, array + j + 1);
        }
    }
}

/* 希尔排序 */
void ssort(int *array, int len, fun compare)
{
    /* 已知最好的步长序列，由Marcin Ciura设计 */
    int gaps[]={1750, 701, 301, 132, 57, 23, 10, 4, 1};
    int index;
    int i = 0, j = 0;
    int step;                   /* 当前插入排序步长 */
    int key;                    /* 关键字值 */

    /* 变步长插入排序 */
    for (index = 0; index < 9; ++index) {
        step = gaps[index];

        /* 按step为步长进行插入排序 */
        /* 和直接插入排序对比看看？ */
        for (i = step; i < len; i += step) {
            key = array[i];

            j = i - step;

            while (!compare(array[j], key) && j >= 0) {
                array[j + step] = array[j];
                j -= step;
            }

            array[j + step] = key;
        }
    }

}

/* 归并排序的本体 */
static void msort_fun(int *array, int low, int high, fun compare);
/* 合并函数 */
static void merge(int *array, int low, int mid, int high, fun compare);
/* 归并排序 */
void msort(int *array, int len, fun compare)
{
    /* msort是个马甲，我们要透过马甲看真相 */
    msort_fun(array, 0, len - 1, compare);
}

/* 归并排序的本体 */
static void
msort_fun(int *array, int low, int high, fun compare)
{
    if (low < high) {
        int mid = (high + low) / 2;           /* 将数组划分为两部分 */
        msort_fun(array, low, mid, compare); /* 对左子数组排序 */
        msort_fun(array, mid + 1, high, compare); /* 对右字数自排序 */

        merge(array, low, mid, high, compare); /* 合并左右子数组使整体有序 */
    } /* 没错，完了 */
}

/* 合并函数 */
static void
merge(int *array, int low, int mid, int high, fun compare)
{
    int len = high - low + 1;
    int *tmp = (int *)calloc(sizeof(int), len);
    int left = 0, right = 0;    /* 循环计数变量 */
    int index;

    /* 拷贝数据到临时数组中 */
    /* 用memcpy的话还有包含strleftng.h，麻烦 */
    for (index = 0; index < len; ++index)
        tmp[index] = array[low + index];

    left = 0;               /* left指示左子数组的第一个元素 */
    right = mid - low + 1;  /* right指示右子数组的第一个元素 */
    index = low;            /* index指向实际数组 */

    /* 从左子数组和右子数组中取最小元素拷贝到array中 */
    /* 左右子数组其中一个取完就退出循环 */
    while (left <= mid - low && right <= high - low) {
        if (compare(tmp[left], tmp[right]))
            array[index++] = tmp[left++];
        else
            array[index++] = tmp[right++];
    }

    /* 左子数组没拷贝完 */
    for (; left <= mid - low;)
        array[index++] = tmp[left++];
    /* 右子数组没拷贝完 */
    for (; right <= high - low;)
        array[index++] = tmp[right++];

    free(tmp);                  /* 别忘了释放calloc分配的内存 */
}


/* 取堆中结点的左子结点 */
static int lchild(int node);
/* 取堆中结点的右子结点 */
static int rchild(int node);
/* 取堆中结点的父结点 */
static int father(int node);
/* 建堆，根据比较函数确定是最大堆还是最小堆 */
static void build_heap(int *heap, int size, fun compare);
/* 保持堆性质 */
static void heapify(int *heap, int root, int size, fun compare);
/* 堆排序 */
void hsort(int *array, int len, fun compare)
{
    int index = len - 1;
    
    build_heap(array, len, compare);

    for(; index > 0; --index) {
        /* 堆顶数是堆中最大/最小的数，将其放到排序后的正确位置 */
        swap(array + 0, array + index);
        /* 重建堆 */
        heapify(array, 0, index, compare);
    }
}

/*
           # 0
          / \
         /   \
        /     \
     1 #       # 2
      / \      /
     /   \    /
    /     \  /
    #      # #
    3      4 5
*/
static int lchild(int node)
{
    return 2 * node + 1;
}
static int rchild(int node)
{
    return 2 * node + 2;
}
static int father(int node)
{
    return (node - 1) / 2;
}
/* 建堆 */
static void build_heap(int *heap, int size, fun compare)
{
    int index = father(size - 1);

    for (; index >= 0; --index)
        heapify(heap, index, size, compare);
}

/* 维持堆中以root为根的子堆的堆性质 */
static void heapify(int *heap, int root, int size, fun compare)
{
    int left = lchild(root);
    int right = rchild(root);
    int most = root; /* 根、左子结点、右子结点中最大(大顶堆)或最小(小顶堆)的结点 */

    if (left < size) /* 求出根、左子结点、右子结点中最大(大顶堆)或最小(小顶堆)的结点 */
        most = !compare(heap[left], heap[most])? left: most;
    if (right < size)
        most = !compare(heap[right], heap[most])? right: most;

    if (most != root) {
        /* 最大/最小的结点应该在根上 */
        swap(heap + most, heap + root);
        /* 若有变动，则应对most为根的子堆也进行堆性质维护 */
        heapify(heap, most, size, compare);
    }
}


/* 分隔函数，供快排使用，不是牛排 */
static int partition(int *array, int low, int high, fun compare);
/* 快速排序的本体 */
static void fsort_func(int *array, int low, int high, fun compare);
/* 快速排序的马甲 */
void fsort(int *array, int len, fun compare)
{
    fsort_func(array, 0, len - 1, compare);
}

static void
fsort_func(int *array, int low, int high, fun compare)
{
    int mid;
    
    if (low < high) {
        /* 将数组划分为两部分，左边的数全小于右边 */
        mid = partition(array, low, high, compare);
        /* 对左子数组进行排序 */
        fsort_func(array, low, mid - 1, compare);
        /* 对右子数组进行排序 */
        fsort_func(array, mid + 1, high, compare);
    }
}

static int
partition(int *array, int low, int high, fun compare)
{
    int counter;                /* 循环计数值 */
    int left_end;               /* 指示小于key值的最后一个数 */

    counter = left_end = low - 1;

    while(++counter != high) {
        /* 若遇到比key值更小的数，将其添加到left_end后面，成为新的left_end */
        if (!compare(array[high], array[counter])) {
            ++left_end;
            swap(array + counter, array + left_end);
        }
        /* 如果当前元素值比key值大，则left_end不动 */
    }

    swap(array + high, array + left_end + 1);

    return left_end + 1;
}

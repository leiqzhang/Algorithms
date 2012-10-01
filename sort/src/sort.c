#include <stdlib.h>

typedef int (*fun)(int,int);

static void swap(int *first, int *second);

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
        /* 必须先检查j是否大于0，否则array[j]可能导致越界访问 */
        while (j >= 0 && !compare(array[j], key)) {
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
    int gaps[9]={1750, 701, 301, 132, 57, 23, 10, 4, 1};
    int index;
    int i = 0, j = 0;
    int step;                   /* 当前插入排序步长 */
    int key;                    /* 关键字值 */

    /* 变步长插入排序 */
    for (index = 0; index < 9; ++index) {
        step = gaps[index];

        /* 按step为步长进行插入排序 */
        /* 和直接插入排序对比看看？ */
        for (i = step; i < len; ++i) {
            key = array[i];

            j = i - step;
            
            /* 必须先检查j是否大于0，否则array[j]可能导致越界访问 */
            while (j >= 0 && !compare(array[j], key)) {
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
static void
merge(int *array, int low, int mid, int high, fun compare, int div);
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
        msort_fun(array, mid + 1, high, compare); /* 对右子数组排序 */

        merge(array, low, mid, high, compare, 1); /* 合并左右子数组使整体有序 */
    } /* 没错，完了 */
}

/* 合并函数 */
/* 合并函数最后一个参数是为了与基数排序时按十进止位排序而设置的 */
static void
merge(int *array, int low, int mid, int high, fun compare, int div)
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
        if (compare(tmp[left] / div, tmp[right] / div))
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

/* 计数排序 */
void csort(int *array, int len, fun compare)
{
    int largest = 0;          /* 数组中最大元素值 */
    int most = 0;             /* 数组中最大元素值(升序)或最小元素值(降序) */
    int counter;              /* 循环计数变量 */

    int *freq;                /* freq数组用来记录每个元素出现的频率 */
    /* dup是数组的一个副本 */
    int *dup = (int *)calloc(sizeof(int), len);

    most = largest = dup[0] = array[0];
    for (counter = 1; counter != len; ++counter) {
        if (!compare(array[counter], most)) /* 选出升序时最大值或降序时最小值 */
            most = array[counter];
        if (array[counter] > largest) /* 选出最大值 */
            largest = array[counter];
        dup[counter] = array[counter];
    }

    /* 分配largest+1个存储空间给freq数组 */
    freq = (int *)calloc(sizeof(int), largest + 1);

    /* 扫描数组,令 freq[key] = key值在array数组中出现的次数 */
    for (counter = 0; counter != len; ++counter)
        ++freq[dup[counter]];

    /* 令freq[key]=key值的元素为在array数组中最大的序号(非下标) */
    for (counter = 1; counter != most + 1; ++counter)
        freq[counter] += freq[counter - 1];

    /* freq[key]=key值在array数组中最大的序号 */
    /* 则将key值放置到array数组的第freq[key]个 */
    /* 位置上,即 array[freq[key]]=key */
    for (counter = 0; counter != len; ++counter) {
        if (most == largest)
            array[freq[dup[counter]] - 1] = dup[counter];
        else
            array[len -freq[dup[counter]]] = dup[counter];
        freq[dup[counter]] -= 1;
    }

    free(freq);                 /* 释放内存 */
    free(dup);                  /* 释放内存 */
}

/* 计算整数的十进制位数 */
static int digit_numbers(int number);
/* 计算10的整数次幂 */
static int ten_pow(int n);
/* 基数排序 */
void rsort(int *array, int len, fun compare)
{
    int max_digit_num = 0;          /* 数组中各个元素的最大十进制位数 */
    int digit_num;                  /* 用于记录循环时当前元素的十进制位数 */
    int counter = 0;                /* 循环计数变量 */
    int div;                        /* 按位排序时用于取出十进制位 */

    int step;
    int low, mid, high;
    
    for (; counter != len; ++counter) { /* 计算最大十进制位数 */
        digit_num = digit_numbers(array[counter]);
        if (digit_num > max_digit_num)
            max_digit_num = digit_num;
    }

    /* 从个位开始,逐次按十进制位排序 */
    for (digit_num = 1; digit_num <= max_digit_num; ++digit_num) {
        div = ten_pow(digit_num - 1);

        /* 基数排序比须使用稳定排序,这里使用归并排序(非递归) */
        for (counter = 1; counter < len; counter *= 2) { /* log(len)趟归并 */
            step = counter -  1; /* 要归并的两段子数组的距离:第一个元素之间的距离 */
            low = 0;
            
            while (low < len) {
                mid  = low + step;
                if (mid >= len) /* 防止数组越界 */
                    mid = len - 1;
                
                high = mid + step + 1; /* 防止数组越界访问 */
                if (high >= len)
                    high = len - 1;
                
                merge(array, low, mid, high, compare, div);

                low = high + 1;    /* 归并下一段 */
            }
        }

    }
}

/* 计算一个数的十进制位数 */
/* 为了尽量不调用外部的库,不使用math库里的对数函数 */
static int digit_numbers(int number)
{
    if (number < 10)
        return 1;
    else
        return 1 + digit_numbers(number / 10);
}
/* 计算10的整数次幂,理由同上 */
static int ten_pow(int n)
{
    if (0 == n)
        return 1;
    else
        return 10 * ten_pow(n - 1);
}


/*
 * To swap the value of two integers.
 */
static void swap(int *first, int *second)
{
    if (first != second) {      /* to avoid the bug caused by same pointer */
        *first = *first ^ *second;
        *second= *first ^ *second;
        *first = *first ^ *second;
    }
}


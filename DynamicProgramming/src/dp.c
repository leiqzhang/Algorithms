#include <stdlib.h>

/* 求字符串长度 */
static int length(char str[]);
/* 求str_a[0...len_a-1]与str_b[0...len_b-1]的LCS长度 */
static void lcs_len(char str_a[], char str_b[], int **len);
/* 求最长公共子序列 */
void lcs(char str_a[], char str_b[], char *lcs_str)
{
    const int len_a = length(str_a);
    const int len_b = length(str_b);

    int n;
    int a = len_a, b = len_b;
    
    int **len = (int **)calloc(len_a + 1, sizeof(int *));
    for (n = 0; n <= len_a; ++n) /* 为二维数组分配内存 */
        len[n] = (int *)calloc(len_b + 1, sizeof(int));

    lcs_len(str_a, str_b, len); /* 求str_a[0...i]与str_b[0...j]的LCS长度 */

    n = len[len_a][len_b];      /* n是LCS的长度 */

    lcs_str[n--] = '\0';        /* lcs_str数组用于存放LCS */

    while (n >= 0) {            /* 通过len[i][j]数组的辅助，逐个比较str_a和str_b的元素，得到LCS */
        if (str_a[a - 1] == str_b[b - 1])
            (lcs_str[n] = str_a[a - 1]), --n, --a, --b;
        else
            len[a - 1][b] > len[a][b - 1] ? --a: --b;
    }
    
    for (n = 0; n <= len_a; ++n) /* 释放动态数组内存 */
        free(len[n]);
    free(len);
}

static int length(char str[])
{
    if (str[0] != '\0')
        return 1 + length(str + 1);
    else
        return 0;
}
/* 求str_a[0...i]与str_b[0...j]的LCS长度 */
static void lcs_len(char str_a[], char str_b[], int **len)
{
    int a, b;

    for (a = 1; str_a[a - 1] != '\0'; ++a)
        for (b = 1; b < str_b[b - 1] != '\0'; ++b) {
            if (str_a[a - 1] == str_b[b - 1])
                len[a][b] = len[a - 1][b - 1] + 1;
            else
                len[a][b] = len[a - 1][b] > len[a][b - 1] ? len[a - 1][b]: len[a][b - 1];
        }
}

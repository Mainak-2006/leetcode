#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int digitFactors[10][4] = {
    {0, 0, 0, 0}, /* 0 */
    {0, 0, 0, 0}, /* 1 */
    {1, 0, 0, 0}, /* 2 */
    {0, 1, 0, 0}, /* 3 */
    {2, 0, 0, 0}, /* 4 */
    {0, 0, 1, 0}, /* 5 */
    {1, 1, 0, 0}, /* 6 */
    {0, 0, 0, 1}, /* 7 */
    {3, 0, 0, 0}, /* 8 */
    {0, 2, 0, 0}  /* 9 */
};

static void subtractFactors(const int a[4], const int b[4], int out[4]) {
    for (int i = 0; i < 4; i++) {
        int v = a[i] - b[i];
        out[i] = v > 0 ? v : 0;
    }
}

static int isSubset(const int req[4], const int have[4]) {
    for (int i = 0; i < 4; i++)
        if (have[i] < req[i])
            return 0;
    return 1;
}

static int getFactorCount(const int need[4], int g[10]) {
    int count8 = need[0] / 3;
    int rem2 = need[0] % 3;
    int count9 = need[1] / 2;
    int count3 = need[1] % 2;
    int count4 = rem2 / 2;
    int count2 = rem2 % 2;
    int count6 = 0;

    if (count2 == 1 && count3 == 1) {
        count2 = 0;
        count3 = 0;
        count6 = 1;
    }
    if (count3 == 1 && count4 == 1) {
        count2 = 1;
        count6 = 1;
        count3 = 0;
        count4 = 0;
    }

    g[2] = count2;
    g[3] = count3;
    g[4] = count4;
    g[5] = need[2];
    g[6] = count6;
    g[7] = need[3];
    g[8] = count8;
    g[9] = count9;

    return count2 + count3 + count4 + need[2] + count6 + need[3] + count8 + count9;
}

static char *construct(const int g[10]) {
    int len = 0;
    for (int d = 2; d <= 9; d++)
        len += g[d];
    char *s = malloc((size_t)len + 1);
    char *p = s;
    for (int d = 2; d <= 9; d++)
        for (int k = 0; k < g[d]; k++)
            *p++ = (char)('0' + d);
    *p = '\0';
    return s;
}

static char *smallestNumber(const char *num, long long t) {
    int n = (int)strlen(num);

    int primeCount[4] = {0, 0, 0, 0};
    int primes[4] = {2, 3, 5, 7};
    for (int p = 0; p < 4; p++) {
        while (t % primes[p] == 0) {
            t /= primes[p];
            primeCount[p]++;
        }
    }
    if (t != 1)
        return strdup("-1");

    int g[10] = {0};
    int lenT = getFactorCount(primeCount, g);
    if (lenT > n)
        return construct(g);

    int prefix[4] = {0, 0, 0, 0};
    int firstZero = n;
    for (int i = 0; i < n; i++) {
        int d = num[i] - '0';
        if (d == 0 && firstZero == n)
            firstZero = i;
        for (int p = 0; p < 4; p++)
            prefix[p] += digitFactors[d][p];
    }

    if (firstZero == n && isSubset(primeCount, prefix))
        return strdup(num);

    char *res = malloc((size_t)n + 3);

    for (int i = n - 1; i >= 0; i--) {
        int d = num[i] - '0';
        for (int p = 0; p < 4; p++)
            prefix[p] -= digitFactors[d][p];
        if (i > firstZero)
            continue;
        int space = n - 1 - i;
        for (int b = d + 1; b <= 9; b++) {
            int need[4], tmp[4];
            subtractFactors(primeCount, prefix, tmp);
            subtractFactors(tmp, digitFactors[b], need);
            int g2[10] = {0};
            int s = getFactorCount(need, g2);
            if (s <= space) {
                int k = 0;
                for (int j = 0; j < i; j++)
                    res[k++] = num[j];
                res[k++] = (char)('0' + b);
                for (int j = 0; j < space - s; j++)
                    res[k++] = '1';
                for (int dgt = 2; dgt <= 9; dgt++)
                    for (int c = 0; c < g2[dgt]; c++)
                        res[k++] = (char)('0' + dgt);
                res[k] = '\0';
                return res;
            }
        }
    }

    int g3[10] = {0};
    int s = getFactorCount(primeCount, g3);
    int k = 0;
    for (int j = 0; j < n + 1 - s; j++)
        res[k++] = '1';
    for (int dgt = 2; dgt <= 9; dgt++)
        for (int c = 0; c < g3[dgt]; c++)
            res[k++] = (char)('0' + dgt);
    res[k] = '\0';
    return res;
}
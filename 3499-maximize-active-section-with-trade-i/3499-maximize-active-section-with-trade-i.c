#include <stdlib.h>
#include <string.h>

int maxActiveSectionsAfterTrade(char* s) {
    int n = strlen(s);
    int ones = 0;
    for (int i = 0; i < n; i++)
        if (s[i] == '1')
            ones++;
    char *t = (char *)malloc(n + 3);
    t[0] = '1';
    memcpy(t + 1, s, n);
    t[n + 1] = '1';
    t[n + 2] = '\0';

    int m = n + 2;
    char runChar[m];
    int runLen[m];
    int runs = 0;

    int i = 0;
    while (i < m) {
        char c = t[i];
        int j = i;
        while (j < m && t[j] == c)
            j++;

        runChar[runs] = c;
        runLen[runs] = j - i;
        runs++;

        i = j;
    }

    int bestGain = 0;
    for (i = 1; i < runs - 1; i++) {
        if (runChar[i] == '1' &&
            runChar[i - 1] == '0' &&
            runChar[i + 1] == '0') {

            int gain = runLen[i - 1] + runLen[i + 1];
            if (gain > bestGain)
                bestGain = gain;
        }
    }

    free(t);
    return ones + bestGain;
}
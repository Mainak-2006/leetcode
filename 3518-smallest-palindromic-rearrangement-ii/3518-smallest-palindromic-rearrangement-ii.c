#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 1000001LL

long long combLimited(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r > n - r) r = n - r;

    long long ans = 1;

    for (int i = 1; i <= r; i++) {
        ans = ans * (n - r + i) / i;
        if (ans > LIMIT) return LIMIT;
    }

    return ans;
}

long long countWays(int freq[]) {
    int total = 0;
    for (int i = 0; i < 26; i++)
        total += freq[i];

    long long ans = 1;
    int rem = total;

    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) continue;

        ans *= combLimited(rem, freq[i]);
        if (ans > LIMIT) ans = LIMIT;

        rem -= freq[i];
    }

    return ans;
}

char* smallestPalindrome(char* s, int k) {
    int cnt[26] = {0};
    int n = strlen(s);

    for (int i = 0; i < n; i++)
        cnt[s[i] - 'a']++;

    int half[26] = {0};
    char mid = '\0';

    for (int i = 0; i < 26; i++) {
        half[i] = cnt[i] / 2;
        if (cnt[i] % 2)
            mid = 'a' + i;
    }

    if (countWays(half) < k) {
        char *res = (char *)malloc(1);
        res[0] = '\0';
        return res;
    }

    int len = n / 2;

    char *left = (char *)malloc(len + 1);
    int pos = 0;

    while (pos < len) {
        for (int c = 0; c < 26; c++) {
            if (half[c] == 0)
                continue;

            half[c]--;

            long long ways = countWays(half);

            if (ways >= k) {
                left[pos++] = 'a' + c;
                break;
            }

            k -= ways;
            half[c]++;
        }
    }

    left[len] = '\0';

    char *ans = (char *)malloc(n + 1);

    int idx = 0;

    for (int i = 0; i < len; i++)
        ans[idx++] = left[i];

    if (mid)
        ans[idx++] = mid;

    for (int i = len - 1; i >= 0; i--)
        ans[idx++] = left[i];

    ans[idx] = '\0';

    free(left);
    return ans;
}
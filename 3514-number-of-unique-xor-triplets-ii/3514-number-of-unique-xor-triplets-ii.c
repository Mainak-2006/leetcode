#include <stdbool.h>

int uniqueXorTriplets(int* nums, int numsSize) {
    bool dp[4][2048] = {false};

    dp[0][0] = true;

    for (int i = 0; i < numsSize; i++) {
        int v = nums[i];
        for (int k = 2; k >= 0; k--) {
            for (int x = 0; x < 2048; x++) {
                if (dp[k][x]) {
                    dp[k + 1][x ^ v] = true;
                }
            }
        }
    }

    int ans = 0;
    for (int x = 0; x < 2048; x++) {
        if (dp[1][x] || dp[3][x]) {
            ans++;
        }
    }

    return ans;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char* stoneGameIII(int* stoneValue, int stoneValueSize) {
    int n = stoneValueSize;

    int* dp = (int*)malloc((n + 1) * sizeof(int));

    dp[n] = 0;

    for (int i = n - 1; i >= 0; i--) {
        int sum = 0;
        dp[i] = INT_MIN;

        for (int j = 0; j < 3 && i + j < n; j++) {
            sum += stoneValue[i + j];
            
            int score = sum - dp[i + j + 1];

            if (score > dp[i]) {
                dp[i] = score;
            }
        }
    }

    int result = dp[0];

    free(dp);

    if (result > 0)
        return "Alice";
    else if (result < 0)
        return "Bob";
    else
        return "Tie";
}
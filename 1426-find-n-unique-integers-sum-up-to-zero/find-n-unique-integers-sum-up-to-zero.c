int* sumZero(int n, int* returnSize) {
    int* ans = (int*)malloc(n * sizeof(int));
    *returnSize = n;

    int idx = 0;

    for (int i = 1; i <= n / 2; i++) {
        ans[idx++] = i;
        ans[idx++] = -i;
    }

    if (n % 2 == 1) {
        ans[idx] = 0;
    }

    return ans;
}
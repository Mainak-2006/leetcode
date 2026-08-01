#define MAXN 21

int memo[MAXN][MAXN];
int vis[MAXN][MAXN];

int solve(int* nums, int l, int r) {
    if (l == r)
        return nums[l];

    if (vis[l][r])
        return memo[l][r];

    vis[l][r] = 1;

    int left = nums[l] - solve(nums, l + 1, r);
    int right = nums[r] - solve(nums, l, r - 1);

    memo[l][r] = (left > right) ? left : right;
    return memo[l][r];
}

bool predictTheWinner(int* nums, int numsSize) {
    memset(vis, 0, sizeof(vis));
    return solve(nums, 0, numsSize - 1) >= 0;
}
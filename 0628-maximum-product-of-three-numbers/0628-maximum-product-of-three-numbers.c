#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maximumProduct(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    int n = numsSize;

    int prod1 = nums[n-1] * nums[n-2] * nums[n-3];
    int prod2 = nums[n-1] * nums[0] * nums[1];

    return prod1 > prod2 ? prod1 : prod2;
}
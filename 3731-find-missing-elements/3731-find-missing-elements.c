#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int* findMissingElements(int* nums, int numsSize, int* returnSize) {

    qsort(nums, numsSize, sizeof(int), compare);

    int* result = (int*)malloc(sizeof(int) * 101);
    int k = 0;

    int prevNum = nums[0];

    for (int i = 1; i < numsSize; i++) {

        while (nums[i] != prevNum + 1) {
            result[k++] = ++prevNum;
        }

        prevNum = nums[i];
    }

    *returnSize = k;
    return result;
}
int maxProduct(int* nums, int numsSize) {

    int max1 = INT_MIN, max2 = INT_MIN;
    int min1 = INT_MAX, min2 = INT_MAX;

    for (int i = 0; i < numsSize; i++) {

        int num = nums[i];

        if (num > max1) {
            max2 = max1;
            max1 = num;
        } else if (num > max2) {
            max2 = num;
        }

        if (num < min1) {
            min2 = min1;
            min1 = num;
        } else if (num < min2) {
            min2 = num;
        }
    }

    int p1 = (max1 - 1) * (max2 - 1);
    int p2 = (min1 - 1) * (min2 - 1);

    return (p1 > p2) ? p1 : p2;
}
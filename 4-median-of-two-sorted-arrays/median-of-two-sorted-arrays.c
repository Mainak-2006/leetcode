double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int merged[2000];   // max size (safe for constraints)
    int i = 0, j = 0, k = 0;

    // Merge both arrays
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] < nums2[j])
            merged[k++] = nums1[i++];
        else
            merged[k++] = nums2[j++];
    }

    // Remaining elements
    while (i < nums1Size)
        merged[k++] = nums1[i++];

    while (j < nums2Size)
        merged[k++] = nums2[j++];

    int total = nums1Size + nums2Size;

    // Find median
    if (total % 2 == 1) {
        return merged[total / 2];
    } else {
        return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
    }
}
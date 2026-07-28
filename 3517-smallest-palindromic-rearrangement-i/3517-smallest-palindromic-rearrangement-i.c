char* smallestPalindrome(char* s) {
    
    int freq[26] = {0};
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        freq[s[i] - 'a']++;
    }

    char* left = (char*)malloc(len + 1);
    char* right = (char*)malloc(len + 1);
    char* result = (char*)malloc(len + 1);
    int leftIndex = 0;

    // Build the left half
    for (int i = 0; i < 26; i++) {
        int half = freq[i] / 2;
        for (int j = 0; j < half; j++) {
            left[leftIndex++] = 'a' + i;
        }
    }
    left[leftIndex] = '\0';

    // Find middle character (if any)
    char middle = '\0';
    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2 != 0) {
            middle = 'a' + i;
            break;
        }
    }

    // Build right half (reverse of left)
    for (int i = 0; i < leftIndex; i++) {
        right[i] = left[leftIndex - i - 1];
    }
    right[leftIndex] = '\0';

    // Construct final result
    result[0] = '\0';
    strcat(result, left);
    if (middle != '\0') {
        int lenRes = strlen(result);
        result[lenRes] = middle;
        result[lenRes + 1] = '\0';
    }
    strcat(result, right);

    // Clean up
    free(left);
    free(right);
    return result;
}

int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int minimumPushes(char* word) {
    int charCount[26] = {0};

    for(int i = 0; word[i] != '\0'; i++) {
        charCount[word[i] - 'a']++;
    }

    qsort(charCount, 26, sizeof(int), compare);

    int minPushCount = 0;

    for(int i = 0; i < 26; i++) {
        minPushCount += charCount[i] * (i / 8 + 1);
    }

    return minPushCount;
}
char* smallestSubsequence(char* s) {
    int freq[26] = {0};
    bool visited[26] = {false};

    int n = strlen(s);

    for (int i = 0; i < n; i++)
        freq[s[i] - 'a']++;

    char *stack = (char *)malloc((n + 1) * sizeof(char));
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        freq[c - 'a']--;

        if (visited[c - 'a'])
            continue;

        while (top >= 0 &&
               stack[top] > c &&
               freq[stack[top] - 'a'] > 0) {
            visited[stack[top] - 'a'] = false;
            top--;
        }

        stack[++top] = c;
        visited[c - 'a'] = true;
    }

    stack[top + 1] = '\0';
    return stack;
}

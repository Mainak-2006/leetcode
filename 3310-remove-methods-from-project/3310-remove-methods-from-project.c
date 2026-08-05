#include <stdlib.h>
#include <stdbool.h>

int* remainingMethods(int n, int k, int** invocations, int invocationsSize,
                      int* invocationsColSize, int* returnSize) {

    // Build adjacency list
    int *outDegree = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < invocationsSize; i++)
        outDegree[invocations[i][0]]++;

    int **adj = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        adj[i] = (int *)malloc(outDegree[i] * sizeof(int));

    int *idx = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < invocationsSize; i++) {
        int u = invocations[i][0];
        int v = invocations[i][1];
        adj[u][idx[u]++] = v;
    }

    // Find suspicious methods using BFS
    bool *sus = (bool *)calloc(n, sizeof(bool));
    int *queue = (int *)malloc(n * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = k;
    sus[k] = true;

    while (front < rear) {
        int u = queue[front++];

        for (int i = 0; i < outDegree[u]; i++) {
            int v = adj[u][i];
            if (!sus[v]) {
                sus[v] = true;
                queue[rear++] = v;
            }
        }
    }

    // Check if any outside method invokes a suspicious method
    for (int i = 0; i < invocationsSize; i++) {
        int u = invocations[i][0];
        int v = invocations[i][1];

        if (!sus[u] && sus[v]) {
            int *ans = (int *)malloc(n * sizeof(int));
            for (int j = 0; j < n; j++)
                ans[j] = j;

            *returnSize = n;

            // Free memory
            for (int j = 0; j < n; j++)
                free(adj[j]);
            free(adj);
            free(outDegree);
            free(idx);
            free(sus);
            free(queue);

            return ans;
        }
    }

    // Return remaining (non-suspicious) methods
    int *ans = (int *)malloc(n * sizeof(int));
    int cnt = 0;

    for (int i = 0; i < n; i++)
        if (!sus[i])
            ans[cnt++] = i;

    *returnSize = cnt;

    // Free memory
    for (int i = 0; i < n; i++)
        free(adj[i]);
    free(adj);
    free(outDegree);
    free(idx);
    free(sus);
    free(queue);

    return ans;
}
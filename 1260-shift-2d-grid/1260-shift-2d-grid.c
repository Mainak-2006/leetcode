#include <stdlib.h>

int** shiftGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = gridColSize[0];
    int totalElements = m * n;
 
    k = k % totalElements;
    int** result = (int**)malloc(m * sizeof(int*));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    *returnSize = m;
    
    for (int i = 0; i < m; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int old1DIndex = i * n + j;
            int new1DIndex = (old1DIndex + k) % totalElements;
            
            int newRow = new1DIndex / n;
            int newCol = new1DIndex % n;
            
            result[newRow][newCol] = grid[i][j];
        }
    }
    return result;
}
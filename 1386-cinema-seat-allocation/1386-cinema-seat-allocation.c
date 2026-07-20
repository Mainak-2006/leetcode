#include <stdlib.h>

typedef struct {
    int row;
    int mask;
} RowMask;

int cmp(const void *a, const void *b) {
    return ((RowMask *)a)->row - ((RowMask *)b)->row;
}

int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize) {

    RowMask *rows = (RowMask *)malloc(sizeof(RowMask) * reservedSeatsSize);
    int m = 0;

    // Build row -> bitmask
    for (int i = 0; i < reservedSeatsSize; i++) {
        int r = reservedSeats[i][0];
        int seat = reservedSeats[i][1];

        int found = -1;
        for (int j = 0; j < m; j++) {
            if (rows[j].row == r) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            rows[m].row = r;
            rows[m].mask = 0;
            found = m++;
        }

        rows[found].mask |= (1 << (seat - 1));
    }

    long long ans = 2LL * n;

    int LEFT   = (1<<1)|(1<<2)|(1<<3)|(1<<4);
    int MIDDLE = (1<<3)|(1<<4)|(1<<5)|(1<<6);
    int RIGHT  = (1<<5)|(1<<6)|(1<<7)|(1<<8);

    for (int i = 0; i < m; i++) {
        ans -= 2;

        int mask = rows[i].mask;

        int leftFree = (mask & LEFT) == 0;
        int rightFree = (mask & RIGHT) == 0;
        int middleFree = (mask & MIDDLE) == 0;

        if (leftFree && rightFree)
            ans += 2;
        else if (leftFree || rightFree || middleFree)
            ans += 1;
    }

    free(rows);
    return (int)ans;
}
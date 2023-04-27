#include <stdio.h>
#include <stdlib.h>

const int shift[4][3] = {{1,  0,  0},
                         {0,  1,  1},
                         {-1, 0,  2},
                         {0,  -1, 3}};
int m, n, min, maze[10][10], res[100][2], path[100], pathxy[100][2];

void backtracking(int x, int y, int pn) {
    if (x == m - 1 && y == n - 1) {
        if (pn < min) {
            min = pn;
            for (int i = 1; i <= pn; i++) {
                res[i][0] = pathxy[i - 1][0];
                res[i][1] = pathxy[i - 1][1];
            }
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        path[pn] = shift[i][2];
        int nx = x + shift[i][0];
        int ny = y + shift[i][1];
        pathxy[pn][0] = nx;
        pathxy[pn][1] = ny;
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && (pn && abs(path[pn] - path[pn - 1]) != 2 || !pn) &&
            !maze[nx][ny]) {
            backtracking(x + shift[i][0], y + shift[i][1], pn + 1);
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    min = 100;
    res[0][0] = 0;
    res[0][1] = 0;
    backtracking(0, 0, 0);
    for (int i = 0; i <= min; i++) {
        printf("(%d,%d)\n", res[i][0], res[i][1]);
    }
    return 0;
}
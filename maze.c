#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m, n, nump, min;
int maze[10][10], res[100][2];
char path[100];

void backtracking(int x, int y) {
    if (x == m - 1 && y == n - 1) {
        if (nump < min) {
            min = nump;
            for (int i = 1; i <= nump; i++) {
                switch (path[i - 1]) {
                    case 'W' :
                        res[i][0] = res[i - 1][0] - 1;
                        res[i][1] = res[i - 1][1];
                        break;
                    case 'S' :
                        res[i][0] = res[i - 1][0] + 1;
                        res[i][1] = res[i - 1][1];
                        break;
                    case 'A' :
                        res[i][0] = res[i - 1][0];
                        res[i][1] = res[i - 1][1] + 1;
                        break;
                    case 'D' :
                        res[i][0] = res[i - 1][0];
                        res[i][1] = res[i - 1][1] - 1;
                        break;
                }
            }
        }
        return;
    }
    if (path[nump - 1] != 'S' && x != 0 && maze[x - 1][y] != 1) {
        path[nump] = 'W';
        nump++;
        backtracking(x - 1, y);
        nump--;
    }
    if ((nump == 0 || path[nump - 1] != 'W') && x != m - 1 && maze[x + 1][y] != 1) {
        path[nump] = 'S';
        nump++;
        backtracking(x + 1, y);
        nump--;
    }
    if (path[nump - 1] != 'D' && y != n - 1 && maze[x][y + 1] != 1) {
        path[nump] = 'A';
        nump++;
        backtracking(x, y + 1);
        nump--;
    }
    if ((nump == 0 || path[nump - 1] != 'A') && y != 0 && maze[x][y - 1] != 1) {
        path[nump] = 'D';
        nump++;
        backtracking(x, y - 1);
        nump--;
    }
    return;
}
int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    nump = 0;
    min = 100;
    res[0][0] = 0;
    res[0][1] = 0;
    backtracking(0, 0);
    for (int i = 0; i <= min; i++) {
        printf("(%d,%d)\n", res[i][0], res[i][1]);
    }
    return 0;
}
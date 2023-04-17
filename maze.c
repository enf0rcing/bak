#include <stdio.h>

int m, n, min;
int maze[10][10], res[100][2];
char path[100];

void backtracking(int x, int y, int flag) {
    if (x == m - 1 && y == n - 1) {
        if (flag < min) {
            min = flag;
            for (int i = 1; i <= flag; i++) {
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
    if (path[flag - 1] != 'S' && x != 0 && maze[x - 1][y] != 1) {
        path[flag] = 'W';
        backtracking(x - 1, y, flag + 1);
    }
    if ((flag == 0 || path[flag - 1] != 'W') && x != m - 1 && maze[x + 1][y] != 1) {
        path[flag] = 'S';
        backtracking(x + 1, y, flag + 1);
    }
    if (path[flag - 1] != 'D' && y != n - 1 && maze[x][y + 1] != 1) {
        path[flag] = 'A';
        backtracking(x, y + 1, flag + 1);
    }
    if ((flag == 0 || path[flag - 1] != 'A') && y != 0 && maze[x][y - 1] != 1) {
        path[flag] = 'D';
        backtracking(x, y - 1, flag + 1);
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
    min = 100;
    res[0][0] = 0;
    res[0][1] = 0;
    backtracking(0, 0, 0);
    for (int i = 0; i <= min; i++) {
        printf("(%d,%d)\n", res[i][0], res[i][1]);
    }
    return 0;
}
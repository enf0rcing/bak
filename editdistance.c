#include <stdio.h>
#include <string.h>
#define MIN(x, y) x < y ? x : y

int main() {
    char word1[501], word2[501];
    scanf("%s\n%s", word1, word2);
    int l1, l2;
    l1 = strlen(word1);
    l2 = strlen(word2);
    if (!l1) {
        printf("%d", l2);
        return 0;
    } else if (!l2) {
        printf("%d", l1);
        return 0;
    }
    int dp[501][501];//dp代表word1(0,i-1)和word2(0, j-1)之间的最小编辑距离
    dp[0][0] = 0;
    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
            dp[i][0] = i;
            dp[0][j] = j;
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = MIN(dp[i - 1][j] + 1, dp[i][j - 1] + 1);//删除(和增加等价)操作
                dp[i][j] = MIN(dp[i][j], dp[i - 1][j - 1] + 1);//替换操作
            }
        }
    }
    printf("%d", dp[l1][l2]);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define int long long
int check(int w[], int n, int k, int P) {
    int cnt = 1; // 至少一组
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (sum + w[i] > P) {
            cnt++;
            sum = w[i];
        } else {
            sum += w[i];
        }
        if (cnt > k) return 0; // 超过k组，不可行
    }
    return cnt <= k; // 检查是否满足分组数
}

signed main() {
    int n, k;
    scanf("%lld %lld", &n, &k);
    int *w = (int *)malloc(sizeof(int) * n);
    int max_val = 0, sum_val = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &w[i]);
        if (w[i] > max_val) max_val = w[i];
        sum_val += w[i];
    }
    int left = max_val, right = sum_val;
    while (left < right) { // 二分查找
        int mid = (left + right) / 2;
        if (check(w, n, k, mid)) {
            right = mid; // 可行，尝试更小值
        } else {
            left = mid + 1; // 不可行，增大下界
        }
    }
    printf("%lld\n", left);
    free(w);
    return 0;
}
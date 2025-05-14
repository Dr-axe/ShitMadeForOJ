/*
理论时间复杂度n^2·logn,但是这段代码优化有点差，在OJ上一千的样例也需要跑二十多毫秒
*/
#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<array>
long long int MAX = 2100000000LL;
long long int target,max = -MAX, min = MAX; ;
int n;
int count = 0;
std::array<long long, 2> nums[9999];

int doubled_search(std::vector<std::array<long long, 3>> &store, long long int mubiao) {
    int l = 0, r = count - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (store[mid][0] < mubiao) {
            l = mid + 1;
        } else if (store[mid][0] > mubiao) {
            r = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}
int main() {
    scanf("%d %lld", &n, &target);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &nums[i][0]);
        nums[i][1] = i + 1;
        max = max > nums[i][0] ? max : nums[i][0];
        min = min < nums[i][0] ? min : nums[i][0];
    }
    sort(nums,nums+n);
    std::vector<std::array<long long, 3>> store;
    store.resize(n * (n - 1) / 2);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            long long sum = nums[i][0] + nums[j][0];
            if (sum + 2 * min <= target && sum + 2 * max >= target) {
                store[count][0] = sum;
                store[count][1] = nums[i][1];
                store[count][2] = nums[j][1];
                count++;
            }
        }
    }
    sort(store.begin(), store.begin() + count, [](const auto& a, const auto& b) { return a[0] < b[0]; });
    for (int i = 0; i < count; i++) {
        long long needed = target - store[i][0];
        int w = doubled_search(store, needed);
        if (w != -1) {
            int ll = w, rr = w;
            while (ll > 0 && store[ll - 1][0] == needed) ll--;
            while (rr < count - 1 && store[rr + 1][0] == needed) rr++;
            for (int j = ll; j <= rr; j++) {
                if (store[i][1] != store[j][1] && store[i][1] != store[j][2] &&
                    store[i][2] != store[j][1] && store[i][2] != store[j][2]) {
                    printf("%lld %lld %lld %lld", store[i][1], store[i][2], store[j][1], store[j][2]);
                    return 0;
                }
            }
        }
    }
    printf("IMPOSSIBLE");
    return 0;
}
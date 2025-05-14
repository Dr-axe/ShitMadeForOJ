#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int n, t;
    cin >> n >> t;
    long long* k = new long long[n];
    long long max_k = 0;
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        max_k = max(max_k, k[i]);
    }
    long long l = 0, r = (long long)t * max_k;
    long long ans = r;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += mid / k[i];
            if (sum >= t) break;  // 提前终止
        }
        if (sum >= t) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    delete[] k;
    return 0;
}
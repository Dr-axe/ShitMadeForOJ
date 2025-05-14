#include <iostream>
#include <deque>
#include <vector>
using namespace std;
typedef long long LL;
int main() {
    int n, l, r;
    scanf("%d %d %d",&n,&l,&r);
    vector<LL> s(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        LL x;
        scanf("%lld",&x);
        s[i] = s[i - 1] + x;//记录当前位置的累计和
    }
    deque<int> q;
    LL res = -1e18;
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.front() < i - r) q.pop_front();//超出最大长度的不考虑，弹出队列
        if (i - l >= 0) {//i在合法区间的时候开始进入维护，保证队列单调递增(即保证留下来的是合法区间内的谷底)
            while (!q.empty() && s[q.back()] >= s[i - l]) q.pop_back();
            q.push_back(i - l);
        }
        if (!q.empty()) res = max(res, s[i] - s[q.front()]);
    }
    printf("%lld",res);
    return 0;
}
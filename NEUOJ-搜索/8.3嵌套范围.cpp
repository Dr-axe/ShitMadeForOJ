#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
int n;
int count;
int lowbit(int x) {
    return x & -x;
}
int get(const std::vector<int>& array, int x) {
    if (x == 0) {
        return 0;
    }
    int sum = 0;
    while (x > 0) {
        sum += array[x];
        x -= lowbit(x);
    }
    return sum;
}
void add(std::vector<int>& array, int x, int y) {
    while (x<=count){
        array[x]+=y;
        x+=lowbit(x);
    }
}
int main() {    
    scanf("%d", &n);
    std::map<std::pair<int, int>, int> store;
    std::set<int> unique_r;
    for (int i = 0; i < n; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        store[std::make_pair(l, -r)] = i;
        unique_r.insert(r);
    }
    count = unique_r.size();
    std::map<int, int> list;
    std::vector<int> r_store(count + 1, 0);
    int index = 1;
    for (int r : unique_r) {
        list[r] = index++;
    }
    std::vector<int> output_baohan(n, 0);
    std::vector<int> output_beiBaoHan(n, 0);
    auto it = std::prev(store.end());
    for (int i = 0; i < n; ++i) {
        int r = -(it->first.second);
        int position_in_r = list[r];
        output_baohan[it->second] = get(r_store, position_in_r)>0;
        add(r_store, position_in_r, 1);
        if (it == store.begin()) {
            break;
        }
        it = std::prev(it);
    }
    std::fill(r_store.begin(), r_store.end(), 0);
    it = store.begin();
    for (int i = 0; i < n; ++i) {
        int r = -(it->first.second);
        int positionInR = list[r];
        output_beiBaoHan[it->second] = i > get(r_store, positionInR - 1);
        add(r_store, positionInR, 1);
        if (it == std::prev(store.end())) {
            break;
        }
        it = std::next(it);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", output_baohan[i]);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", output_beiBaoHan[i]);
    }
    return 0;
}
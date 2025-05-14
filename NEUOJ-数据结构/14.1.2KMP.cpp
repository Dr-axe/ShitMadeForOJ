#include <iostream>
#include <vector>
#include <string>
using namespace std;
std::vector<int> ans;
void kmpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return ;
    vector<int> next(m, 0);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j =next[j-1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        next[i] = j;
    }
    j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            ans.push_back(i - j + 1);
            j=next[j-1];
        }
    }
}
int main() {
    string T;
    string P;
    std::cin>>T>>P;
    kmpSearch(T, P);
    for(int num : ans){
        std::cout<<num<<std::endl;
    }
    return 0;
}
/*
原题目：
给你一个字符串 s 和一个正整数 k 。
用 vowels 和 consonants 分别表示字符串中元音字母和辅音字母的数量。
如果某个字符串满足以下条件，则称其为 美丽字符串 ：
vowels == consonants，即元音字母和辅音字母的数量相等。
(vowels * consonants) % k == 0，即元音字母和辅音字母的数量的乘积能被 k 整除。
返回字符串 s 中 非空美丽子字符串 的数量。
子字符串是字符串中的一个连续字符序列。
英语中的 元音字母 为 'a'、'e'、'i'、'o' 和 'u' 。
英语中的 辅音字母 为除了元音字母之外的所有字母。
*/
#include<iostream>
#include<string>
#include<math.h>
#include<unordered_map>
using namespace std;
int findMinW(int k) {
    int w = 1;
    for (int i = 2; i * i <= k; i++) {
        int count = 0;
        while (k % i == 0) {
            k /= i;
            count++;
        }
        int s=count/2+count%2;
        while(s--){w *= i;}
    }
    if (k > 1) {
        w *= k;
    }
    return w;
}
class Solution {
    public:
        long long beautifulSubstrings(string s, int k) {
            int leng=s.size();
            int l=200000;//随便的一个数，防止相对关系炸到负数
            int toVowels=2130466;//额外左移一位的元音字母的位集合
            int w=findMinW(k)*2;//求出最小的w使得(w/2)^2%k=0
            long long sum = 0;
            unordered_map<int ,int> record;
            if(w>leng){return 0;}
            record[(w-1)<<18|200000]++;
            for (int i = 0; i < leng; i++){
                l=(toVowels>>(s[i]-97)&2)-1+l;//判断字母是否为元音字母，是则返回1，不是则-1，以此维护前缀数组就能得到元音字母和非元音字母数量的相对关系
                sum+=record[(i%w)<<18|l]++;//每一组相对关系相同且满足二者之间距离为w*n(即二者与k的模相等)的时候，元音和辅音字母数量就分别是w*n/2,必定满足可以被k整除
            }
            return sum;
        }
};
int main(){
    Solution sol;
    std::string s = "baeyh";
    int k = 2;
    std::cin>>s>>k;//注释掉就是上面的已有的测试样例
    long long result = sol.beautifulSubstrings(s, k);
    printf("\n结果是 %lld ",result);
    return 0;
}
#include <unordered_map>
#include <string>
#include<iostream>
#include <functional>
#include <cstring>
#include<unordered_set>
#include<vector>
#include<set>
using namespace std;
string input;
string x;
vector<double>pos;
int charToIndex(char c) {
    if (c >= '0' && c <= '9') {
        return c - 47;             // 0-9 对应索引 1-10
    } else if (c >= 'a' && c <= 'z') {
        return c - 60;       // a-z 对应索引 37-61
    } else if (c >= 'A' && c <= 'Z') {
        return c-54;       // A-Z 对应索引 11-36
    }
    return 0; // 无效字符（根据题意，输入保证合法）
}
std::string cutstr(const std::string& in,int a) {//截取a为起点的后5位
    std::string result = in.substr(a, 6);
    result.resize(6, '.');  // 自动截断或补零
    return result;
}
double getweight(int n){
    int l=input.size();
    if(n>=l){return 0;}
    else{return pos[l-1-n];}
}
struct specialcmp{
    bool operator()(int a, int b) const {
        if (a<0){
            int l=x.size();
            for(int i=0;i<l;i++){
                char n,m;
                if(b+i<input.size()){m=input[b+i];}
                else{m='.';}
                n=x[i];
                if(n!=m){return n<m;}
            }
            return 0;
        }
        else if(b<0){
            int l=x.size();
            for(int i=0;i<l;i++){
                char n,m;
                if(a+i<input.size()){n=input[a+i];}
                else{n='.';}
                m=x[i];
                if(n!=m){return n<m;}
            }
            return 0;
        }
        else{
            if (a+6<input.size()&&b+6<input.size()){
                string n=cutstr(input,a+6),m=cutstr(input,b+6);
                for(int i=0;i<6;i++){
                    if(n[i]!=m[i]){return n[i]<m[i];}
                }
            }
            return getweight(a+6)<getweight(b+6);
        }
    }
};
struct specialHash {
    size_t operator()(const std::string& it) const {
        size_t ha=0;
        for(const char c:it){
            int in=charToIndex(c);
            ha<<=6;
            ha|=in;
        }
        return ha;
    }
};
double getnewweight(set<int, specialcmp>::const_iterator it, const set<int, specialcmp>& g){
    int len=input.size();
    double l=0,r=99999;
    if(it!=g.begin()){auto p=prev(it);l=pos[len-1-*p];}
    if(it != g.end()&&next(it)!=g.end()){auto p=next(it);r=pos[len-1-*p];}
    return (l+r)/2;
}
void resetweight(set<int, specialcmp>::const_iterator it, const set<int, specialcmp>& g){
    int len=input.size();
    double i=1;
    pos.push_back(0);
    for(const auto p:g){
        pos[len-1-p]=i;
        i++;
    }
}
bool isEqual(int j,int gap,int locate) {
    if (gap<=6){
        string s1=input.substr(j,gap),s2=x.substr(locate,gap);
        return memcmp(s1.data(), s2.data(), s1.size()) == 0;
    }
    else{
        string s1=input.substr(j,6),s2=x.substr(locate,6);
        if(memcmp(s1.data(), s2.data(), s1.size()) == 0){
            return isEqual(j+6,gap-6,locate+6);
        }
        else{
            return 0;
        } 
    }
}
int main() {
    unordered_map<string, set<int,specialcmp>,specialHash> indexmap; // 自动使用特化的哈希
    unordered_set<string>map1to4;
    cin>>input;
    int size=input.size();
    for(int i=size-1;i>=0;i--){
        string it=cutstr(input,i);
        auto pair=indexmap[it].insert(i);
        if(!pair.second){//插入失败后触发保护机制，重新进行分配
            resetweight(indexmap[it].insert(i).first,indexmap[it]);
            indexmap[it].insert(i);
        }
        else{
            pos.push_back(getnewweight(indexmap[it].insert(i).first,indexmap[it]));
        }
        it.pop_back();
        while(!it.empty()&&map1to4.insert(it).second){
            it.pop_back();
        }
    }
    // cout<<input.size()<<endl;
    // for(const auto it:pos){
    //     cout<<it<<" ";
    // }
    // cout<<endl;
    // for(const auto set:indexmap){
    //     cout<<set.first<<"  "<<set.second.size()<<endl;
    // }
    int times;
    cin>>times;
    for(int i=0;i<times;i++){
        cin>>x;
        if(x.size()>=6){
            string indexstr=cutstr(x,0);
            auto it=indexmap.find(indexstr);
            int find=0;
            if (it!=indexmap.end()){
                auto that=it->second.find(-1);
                if(that!=it->second.end()){find=1;}
            }
            cout<<find<<endl;
        }
        else{
            cout<<map1to4.count(x)<<endl;
        }
    }
    return 0;
}
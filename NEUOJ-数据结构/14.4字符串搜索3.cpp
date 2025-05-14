#include <unordered_map>
#include <string>
#include<iostream>
#include <functional>
#include <cstring>
#include<unordered_set>
#include<vector>
#include<set>
#include<cmath>
using namespace std;
unsigned long int MAX=0x7fffffffffffffff;
string input;
string x;
vector<unsigned long int>pos;
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
    result.resize(5, '.');  // 自动截断或补零
    return result;
}
unsigned long int getweight(int n){
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
            if (a+5<input.size()&&b+5<input.size()){
                string n=cutstr(input,a+5),m=cutstr(input,b+5);
                for(int i=0;i<5;i++){
                    if(n[i]!=m[i]){return n[i]<m[i];}
                }
            }
            return getweight(a+5)<getweight(b+5);
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
unsigned long int getnewweight(set<int, specialcmp>::const_iterator it, const set<int, specialcmp>& g){
    int len=input.size();
    unsigned long int l=0,r=MAX;
    if(it!=g.begin()){auto p=prev(it);l=pos[len-1-*p];}
    if(it != g.end()&&next(it)!=g.end()){auto p=next(it);r=pos[len-1-*p];}
    return (l+r)/2;
}
void resetweight(set<int, specialcmp>::const_iterator it, const set<int, specialcmp>& g){
    int len=input.size();
    if(g.size()>256){
        auto front=it;
        auto back=it;
        int count=0;
        for(int i=0;i<40&&next(back)!=g.end();i++,count++,back++);
        for(int i=0;i<40&&front!=g.begin();i++,--front,count++);
        unsigned long int l=*front,r=*back;
        unsigned long int gap=(r-l)/count;
        unsigned long int nownum=pos[len-1-*front];
        for(int i=1;i<count;i++){
            ++front;
            nownum+=gap;
            pos[len-1-*front]=nownum;
        }
    }
    else{
        unsigned long int i=1;
        unsigned long int gap=MAX/(g.size()+1);
        for(const auto p:g){
            pos[len-1-p]=i*gap;
            i++;
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
            cout<<"\ndefendence\n";
            resetweight(pair.first,indexmap[it]);
            pos.push_back(getnewweight(indexmap[it].insert(i).first,indexmap[it]));
        }
        else{
            pos.push_back(getnewweight(pair.first,indexmap[it]));
        }
        do{
        it.pop_back();
        }while(!it.empty()&&map1to4.insert(it).second);
    }
    // cout<<input.size()<<endl;
    // for(const auto it:pos){
    //     cout<<it<<" "<<endl;
    // }
    // cout<<endl;
    // for(const auto set:indexmap){
    //     cout<<set.first<<"  "<<set.second.size()<<endl;
    // }
    int times;
    cin>>times;
    for(int i=0;i<times;i++){
        cin>>x;
        if(x.size()>=5){
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
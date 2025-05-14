/*
https://oj.neu.edu.cn/courses/26/part/51/problem/229
循环进行kmp的做法
(标准做法是字符串哈希)
*/
#include <iostream>
#include <vector>
#include <string>
#include<set>
using namespace std;
int h,w;
int h1,w1;
int notice=0;
vector<vector<int>>kmpWaypoints;
vector<string> pattern;
vector<string> text;
set<int> ans;
set<int> preans;
void loadALine(int x){
    vector<int> nextLine(w1,0);
    int j = 0;
    for (int i = 1; i < w1; ++i) {
        while (j > 0 && pattern[x][i] != pattern[x][j]) {
            j =nextLine[j-1];
        }
        if (pattern[x][i] == pattern[x][j]) {
            ++j;
        }
        nextLine[i] = j;
    }
    kmpWaypoints.push_back(nextLine);
}
void loadWaypoints(){
    for (int i = 0; i < h1; i++){
        loadALine(i);
    }
}
int kmp(int t,int p){
    int j = 0;
    if (notice){
        cout<<"the situation of line "<<t<<" is:\n";
        for(const auto it:pattern[t]){
            printf("%zu ",it);
        }
        cout<<endl;
    }
    for (int i = 0; i < w; ++i) {
        while (j > 0 && text[t][i] != pattern[p][j]) {
            j = kmpWaypoints[p][j-1];
        }
        if (text[t][i] == pattern[p][j]) {
            ++j;
        }
        if (j == w1) {
            if(notice){cout<<"save the situation"<<i-j+1<<endl;}
            if (ans.find(i-j+1)!=ans.end()){
                preans.insert(i - j + 1);
            }
            j=kmpWaypoints[p][j-1];
            
        }
    }
    ans=move(preans);preans.clear();
    if (ans.empty()){
        if(notice){cout<<"break the check:no posible situation\n";}
        return 1;
    }
    return 0;
}
void kmpSearch(int beginLine) {
    int line1=beginLine,line2=0;
    for (;line2<h1;line2++,line1++){
        if (line2==0){//对起始行kmp
            int j = 0;
            for (int i = 0; i < w; ++i) {
                while (j > 0 && text[line1][i] != pattern[0][j]) {
                    j = kmpWaypoints[0][j - 1];
                }
                if (text[line1][i] == pattern[0][j]) {
                    ++j;
                }
                if (j == w1) {
                    if(notice){cout<<"input "<<i<<" "<<j<<endl;}
                    preans.insert(i - j + 1);
                    j=kmpWaypoints[0][j-1];
                }

            }
            ans=move(preans);
            preans.clear();
            if(notice){
                cout<<"the origin situation of line "<<line1<<" is:\n";
                for(const auto it:ans){
                    printf("%zu ",it);
                }
            cout<<endl;
            }
            continue;
        }
        if (kmp(line1,line2)){//后续对每一行kmp取并集，并集为空则无结果，退出，否则继续
            if(notice){cout<<"no posible situation:Line "<<beginLine<<endl;}
            return ;
        }    
    }
    for(const auto it:ans){//能走到这一步说明并集不为空，并集即为所求，打印
        cout<<beginLine<<" "<<it<<endl;
    }
    ans.clear();
}
int main() {
    cin>>h>>w;
    for (int  i = 0; i <h; i++){
        string newone;
        cin>>newone;
        text.push_back(newone);
    }
    cin>>h1>>w1;
    for (int  i = 0; i <h1; i++){
        string newone;
        cin>>newone;
        pattern.push_back(newone);
    }
    loadWaypoints();
    for (int i = 0; i <=(h-h1); i++){
        kmpSearch(i);
    }
}
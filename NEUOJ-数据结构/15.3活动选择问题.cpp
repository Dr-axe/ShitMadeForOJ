/*
题目：
https://oj.neu.edu.cn/courses/26/part/221/problem/1001
*/
#include<map>
#include<iostream>
using namespace std;
map<int , int >ewm;
void input(int b,int e){//键按结束时间排，结束时间越早越靠前（优先级越高），值取最晚的开始时间，根据贪心，全部按照最晚开始最早结束的必然是局部最优解，题目又只需要局部最优解
    auto it=ewm.find(e);
    if(it==ewm.end()){ewm[e]=b;}
    else{it->second=it->second>b?it->second:b;}
}
int main(){
    int times,nowtime=0;
    cin>>times;
    for(int i=0;i<times;i++){
        int b,e;cin>>b>>e;
        input(b,e);
    }
    int count=0;
    for(const auto pair:ewm){
        if(pair.second>nowtime){
            count++;nowtime=pair.first;
        }
    }
    cout<<count;
}
#include<stdlib.h>
#include<iostream>
#include<map>
using namespace std;
int main(){
map<long double ,pair<long double,long double>> list;
int n;long double w;
cin>>n>>w;
for (int i = 0; i < n; i++){
    long double x,y;
    cin>>x>>y;
    if(list.find(y/x)==list.end()){
        list[y/x]=make_pair(x,y);
    }
    else{
        list[y/x].first+=x;
        list[y/x].second+=y;
    }
}
long double sum=0;
for (const auto &[k,pair]:list){
    if (w>pair.second){
        w-=pair.second;
        sum+=pair.first;
    }
    else if (w<=pair.second){
        sum+=w/pair.second*pair.first;
        cout<<sum;
        return 0;
    }
    // cout<<sum<<" "<<w<<endl; 
}
cout<<sum;
return 0;
}
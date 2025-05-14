/*
4*4数字华容道的自动求解最短路径计算，基于双向BFS并添加剪枝实现
带显示完整路径的版本在 自用小程序/数字华容道无敌版
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<map>
#include<chrono>
using namespace std;
int newd=1;
unsigned long int checker_target=0x123456789abcdef0,checker=15;
unsigned long int nextLineChecker=0x0001000100010001;
unsigned long int scanner=0xffffffff00000000,scanner1=0xffffffff,scanner2=0xaaaaaaaaaaaaaaaa;
int be[16];
int mindistance=45;
int MAX=1<<30;
/*basic=1<<16 -1 =65535 */
int up=65520;int down=4095;int L=61166;int R=30583;
map<unsigned long int, int> plates;
map<unsigned long int, int> check_depth;
map<unsigned long int,int>br1;
map<unsigned long int,int>b1;
map<unsigned long int,int>br2;
map<unsigned long int,int>b2;
unsigned long int getnp(unsigned long int node,int p_0,int s){
    unsigned long int move=(checker<<(60-4*(p_0)+s))&node;
    if (s>0){ 
        return (move^node)|(move>>s);
    }
    else if (s<0){
        return (move^node)|(move<<(-s));
    }
}
void loadbe (unsigned long int p){
    int count=1;
    for(int i=60;i>=0;i-=4){
        int t=15&(p>>i);
        be[t]=count;
        count++;
    }
}
bool Check(unsigned long int p){
    int count=1;
    int summary=0;
    for(int i=60;i>=0;i-=4){
        int t=15&(p>>i);
        if(t!=0){
            summary+=abs(t-count)%4+abs((t-1)/4-(count-1)/4);    
        }
        count++;
    }
    return (summary+newd)<mindistance;
}
bool Check2(unsigned long int p){
    int summary=0;
    int n=1;
    for(int i=60;i>=0;i-=4){
        int t=15&(p>>i);
        t=be[t];
        if(t!=0){
            summary+=abs(t-n)%4+abs((t-1)/4-(n-1)/4);
        }
        n++;
    }
    return (summary+newd)<mindistance;
}
void printPlate(unsigned long int p){
    int x=64;
    while (x){
        x-=4;
        printf("%ld ",15&(p>>x));
        if(nextLineChecker&(1<<x)){printf("\n");}
    } 
}
void direction_go(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=plates.find(np);
    if(it==plates.end()){
        if(Check(np)){
            plates.emplace(np,newd);
            b1.emplace(np,p_0-(s/4));
        }
    }
}
void explore(unsigned long int node,int p_0){
    if((up>>p_0)&1){direction_go(node,16,p_0);}
    if((down>>p_0)&1){direction_go(node,-16,p_0);}
    if((R>>p_0)&1){direction_go(node,-4,p_0);}
    if((L>>p_0)&1){direction_go(node,4,p_0);}
}
void checkMin(unsigned long int node){
    auto it=plates.find(node);
    if(it!=plates.end()){mindistance=mindistance<(it->second+newd)?mindistance:(it->second+newd);}
}
void direction_go2(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=check_depth.find(np);
    if(it==check_depth.end()){
        if(Check2(np)){
            check_depth.emplace(np,newd);checkMin(np);b2.emplace(np,p_0-(s/4));
        }
    }
}
void explore2(unsigned long int node,int p_0){
    
    if((up>>p_0)&1){direction_go2(node,16,p_0);}
    if((down>>p_0)&1){direction_go2(node,-16,p_0);}
    if((R>>p_0)&1){direction_go2(node,-4,p_0);}
    if((L>>p_0)&1){direction_go2(node,4,p_0);}
}
int main(){
    int position_0;
    unsigned long int input,begin=0;
    for(int i=0;i<16;i++){
        cin>>input;
        if (!input){
            position_0=i;
        }
        begin<<=4;
        begin|=input;
    }
    loadbe(begin);
    if (begin==checker_target){printf("0");return 0;}
    plates.emplace(begin, 0);
    br1.emplace(begin,position_0);
    check_depth.emplace(checker_target,0);
    br2.emplace(checker_target,15);
    while (newd<=30){
        for(auto it = br1.begin();it!=br1.end();++it){
            explore(it->first,it->second);
        }
        br1=move(b1);b1.clear();
        for(auto it = br2.begin();it!=br2.end();++it){
            explore2(it->first,it->second);
        }
        br2=move(b2);b2.clear();
        if(mindistance<45){printf("%d",mindistance);return 0;}
        newd++;
    }
    printf("%d",mindistance);
}
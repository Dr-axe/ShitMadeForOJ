/*3*3的数字华容道求最优解*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
int max_depth = 32;
long int checker_target=4886718336,checker=15;
int MAX=1<<30;
int up=504;int down=63;int L=438;int R=219;
class Node {
    public:
        int situation,p0,mindistance;
        Node(int p0) : p0(p0){
            situation=0;mindistance=MAX;
        }
};
unordered_map<long int,Node> plates;
void printPlate(long int p){
    for (int i = 0; i < 3; i++){
        printf("%ld %ld %ld \n",(15&(p>>(32-4*(0+i*3)))),(15&(p>>(32-4*(1+i*3)))),(15&(p>>(32-4*(2+i*3)))));
    }
}
long int direction_go(long int node,int s){
    auto it=plates.find(node);
    int a=it->second.mindistance+1;
    int p_0=it->second.p0;
    int way=32-4*(p_0)+s;
    long int p=it->first;
    long int move=(checker<<way)&it->first;
    long int np;
    if (s>0){
        np=(move^p)|(move>>s);
    }
    else if (s<0){
        np=(move^p)|(move<<(-s));
    }
    it=plates.find(np);
    if (it==plates.end()){
        plates.emplace(np, Node(p_0-(s/4)));
        it=plates.find(np);
    }
    int b=it->second.mindistance;
    if (a<b){
        it->second.mindistance=a;
        return np;    
    }
    return 0;
}
void explore(long int node,int depth){
    if (depth >= max_depth) {
        return;
    }
    auto it=plates.find(node);
    int p_0=it->second.p0;
    if((up>>p_0)&1){
        long int np=direction_go(node,12);
        if (np){explore(np,depth+1);}
    }
    if((down>>p_0)&1){
        long int np=direction_go(node,-12);
        if (np){explore(np,depth+1);}
    }
    if((R>>p_0)&1){
        long int np=direction_go(node,-4);
        if (np){explore(np,depth+1);}
    }
    if((L>>p_0)&1){
        long int np=direction_go(node,4);
        if (np){explore(np,depth+1);}
    }
}
int main(){
    int position_0;
    long int input,begin=0;
    for(int i=0;i<9;i++){
        cin>>input;
        if (!input){
            position_0=i;
        }
        begin<<=4;
        begin|=input;
    }
    plates.emplace(begin, Node(position_0)); 
    auto it=plates.find(begin);
    it->second.mindistance=0;
    explore(begin,0);
    it=plates.find(checker_target);
    if (it != plates.end()) {
        std::cout << it->second.mindistance << std::endl;
    } else {
        std::cerr << "Target not found." << std::endl;
    }
}
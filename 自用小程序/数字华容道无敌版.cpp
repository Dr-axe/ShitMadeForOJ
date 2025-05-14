#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<unordered_map>
#include<chrono>
#include<deque>
using namespace std;
int newd=1;
unsigned long int checker_target=0x123456789abcdef0,checker=15;
unsigned long int nextLineChecker=0x0001000100010001;
int be[16],ba[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
unsigned long int wayPoint;
int mindistance=45;
int MAX=1<<30;
/*basic=1<<16 -1 =65535 */
int up=65520;int down=4095;int L=61166;int R=30583;
unordered_map<unsigned long int,int> plates;
unordered_map<unsigned long int,int> plates_record;
unordered_map<unsigned long int,int> check_depth;
unordered_map<unsigned long int,int> check_depth_record;
unordered_map<unsigned long int,int>br1;
unordered_map<unsigned long int,int>b1;
unordered_map<unsigned long int,int>br2;
unordered_map<unsigned long int,int>b2;
void loadbe (unsigned long int p){
    int count=1;
    for(int i=60;i>=0;i-=4){
        int t=15&(p>>i);
        be[t]=count;
        count++;
    }
}
int getp0(unsigned long int p){
    int i=0;
    while (checker&p){
        p>>=4;
        i++;
    }
    return (15-i);
}
unsigned long int getnp(unsigned long int node,int p_0,int s){
    unsigned long int move=(checker<<(60-4*(p_0)+s))&node;
    if (s>0){ 
        return (move^node)|(move>>s);
    }
    else if (s<0){
        return (move^node)|(move<<(-s));
    }
}
void printPlate(unsigned long int p){
    int x=64;
    while (x){
        x-=4;
        printf("%ld ",15&(p>>x));
        if(nextLineChecker&(1<<x)){printf("\n");}
    } 
}
bool Check(unsigned long int p,int b[16]){
    int summary=0;
    int n=1;
    for(int i=60;i>=0;i-=4){
        int t=15&(p>>i);
        t=b[t];
        if(t!=0){
            summary+=abs(t-n)%4+abs((t-1)/4-(n-1)/4);
        }
        n++;
    }
    return (summary+newd)<mindistance;
}
void direction_go(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=plates.find(np);
    if(it==plates.end()){
        if(Check(np,ba)){
            plates.emplace(np,newd);
            b1.emplace(np,p_0-(s/4));
            plates_record.emplace(np,-s);
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
    if(it!=plates.end()){mindistance=mindistance<(it->second+newd)?mindistance:(it->second+newd);wayPoint=node;}
}
void direction_go2(unsigned long int node,int s,int p_0){
    unsigned long int np=getnp(node,p_0,s);
    auto it=check_depth.find(np);
    if(it==check_depth.end()){
        if(Check(np,be)){
            check_depth.emplace(np,newd);checkMin(np);b2.emplace(np,p_0-(s/4));check_depth_record.emplace(np,-s);
        }
    }
}
void explore2(unsigned long int node,int p_0){
    
    if((up>>p_0)&1){direction_go2(node,16,p_0);}
    if((down>>p_0)&1){direction_go2(node,-16,p_0);}
    if((R>>p_0)&1){direction_go2(node,-4,p_0);}
    if((L>>p_0)&1){direction_go2(node,4,p_0);}
}
std::deque<unsigned long int> reconstructPath(
    unsigned long int wayPoint,
    const std::unordered_map<unsigned long int, int>& forward_parent,
    const std::unordered_map<unsigned long int, int>& backward_parent
) {
    std::deque<unsigned long int> path;
    path.push_back(wayPoint);
    unsigned long int current = wayPoint;
    while (forward_parent.find(current) != forward_parent.end()) {
        int move = forward_parent.at(current);
        current = getnp(current,getp0(current), move);
        path.push_front(current);
    }
    current = wayPoint;
    while (backward_parent.find(current) != backward_parent.end()) {
        int move = backward_parent.at(current);
        current = getnp(current, getp0(current),move);
        path.push_back(current);
    }
    return path;
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
    // auto start = std::chrono::high_resolution_clock::now();
    while (newd<=23){
        for(auto it = br1.begin();it!=br1.end();++it){
            explore(it->first,it->second);
        }
        br1=move(b1);b1.clear();
        for(auto it = br2.begin();it!=br2.end();++it){
            // printPlate(it->first);
            explore2(it->first,it->second);
        }
        br2=move(b2);b2.clear();
        // printf("组一新增节点数量：%d 组二新增节点数量：%d\n",br1.size(),br2.size());
        // auto end = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        // std::cout << "函数运行时间: " << duration << " 微秒" << std::endl;
        if(mindistance<45){printf("最小步骤是：%d，接下来给出最小步骤解\n",mindistance);break;}
        newd++;
    }
auto path = reconstructPath(wayPoint, plates_record, check_depth_record);
for (auto state : path) {
    printPlate(state);
    std::cout << "↓\n";
}
}
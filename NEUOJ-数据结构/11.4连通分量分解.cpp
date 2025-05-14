#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<vector>
int count=0,turn=0;
class Node {
    public:
        int size,situation;
        std::vector<int> neighbor;
        Node(int size) : size(size) {
            situation=0;
        }
};
int explore(Node* list,std::map<int,int> & myMap,int p){
    list[p].situation=1;
    myMap[p]=turn;
    count++;
    for (int i = 0; i < list[p].size; i++){
        if (!list[list[p].neighbor[i]].situation){
            explore(list,myMap,list[p].neighbor[i]);
        }
    }
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    Node* list=(Node*)malloc(sizeof(Node)*(n+1));
    for (int i = 0; i <n; i++){
        list[i]=Node(0);
    }
    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        list[a].neighbor.push_back(b);
        list[b].neighbor.push_back(a);
        list[a].size++;
        list[b].size++;
    }
    // for (int i = 0; i < n; i++)
    // {
    //     printf("\n*%d,大小：%d* ",i,list[i].size);
    //     for (int ii = 0; ii < list[i].size; ii++)
    //     {
    //         printf("%d ",list[i].neighbor[ii]);
    //     }
    // }
    int beginning=0;
    std::map<int,int> myMap;
    while (count<n){
        explore(list,myMap,beginning);
        if (count<n){
            while (list[beginning].situation!=0&&beginning<=n){
                beginning++;
            }
        }
        turn++;
    }
    // for(const auto pair:myMap){
    //     std::cout<<pair.first<<" "<<pair.second<<std::endl;
    // }
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        a=myMap[a];
        b=myMap[b];
        if (a==b){
            printf("yes\n");
        }
        else{
            printf("no\n");
        }
    }
}
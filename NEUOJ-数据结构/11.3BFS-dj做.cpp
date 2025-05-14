/*
这题我比较叛逆，题目要求我用BFS，但是我用的dijkstra做的····
*/
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
int MAX=1<<30;
class Node {
    public:
        int size,situation;
        int* neighbor;
        Node(int size) : size(size) {
            situation=0;
            neighbor=(int*)malloc(sizeof(int)*size);
        }
};
void explore(Node* list,int x,int* record){//利用dijkstra
    list[x].situation=1;
    int* a=list[x].neighbor;
    int w=record[x]+1;
    for (int i = 0; i < list[x].size; i++){
        record[a[i]]=w<record[a[i]]?w:record[a[i]];
    }
}
int main(){
    int n;
    scanf("%d",&n);
    Node* list=(Node*)malloc(sizeof(Node)*(n+1));
    int* record=(int*)malloc(sizeof(int)*(n+1));
    for (int i = 0; i <n; i++)
    {
        int num,size;
        scanf("%d %d",&num,&size);
        list[num]=Node(size);
        record[num]=MAX;
        for(int j=0;j<size;j++){
            int in;
            scanf("%d",&in);
            list[num].neighbor[j]=in;
        }
    }
    record[1]=0;
    for (int i = 1; i < n; i++)
    {
        int mini=MAX,minNum=0;
        for(int j=1;j<=n;j++){
            if (list[j].situation==0&&record[j]<mini){
                mini=record[j];minNum=j;    
            }
        }
        explore(list,minNum,record);
    }
    for(int i= 1;i<=n;i++){
        printf("%d %d\n",i,record[i]);
    }   
}
/* 12.3用这段也可以，当时好像是用dijkstra做的复杂度O（n^2) */
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
int MAX=1<<30;int count = 1;
class Node {
    public:
        int size,situation;
        int* neighbor;
        int* neighbor_distance;
        Node(int size):size(size) {
            situation=1;
            neighbor=(int*)malloc(sizeof(int)*size);
            neighbor_distance=(int*)malloc(sizeof(int)*size);
        }
};
void explore(Node* list,int x,long long int* record){//利用dijkstra
    list[x].situation=0;
    int* a=list[x].neighbor;
    int* dis=list[x].neighbor_distance;
    for (int i = 0; i < list[x].size; i++){
        long long int w=record[x]+dis[i];
        if(w<record[a[i]]){
            record[a[i]]=w;
            if(list[a[i]].situation==0){
            list[a[i]].situation=1;count--;
            }
        }
    }
    count++;
}
int main(){
    int n;
    scanf("%d",&n);
    Node* list=(Node*)malloc(sizeof(Node)*n);
    long long int* record=(long long int*)malloc(sizeof(long long int)*n);
    for (int i = 0; i <n; i++)
    {
        int num,size;
        scanf("%d %d",&num,&size);
        list[num]=Node(size);
        record[num]=MAX-1;
        for(int j=0;j<size;j++){
            int way,distance;
            scanf("%d %d",&way,&distance);
            list[num].neighbor[j]=way;
            list[num].neighbor_distance[j]=distance;
        }
    }
    // for (int i = 0; i < n; i++){
    //     printf("\n*%d,大小：%d* ",i,list[i].size);
    //     for (int ii = 0; ii < list[i].size; ii++){printf("%d->%d ",list[i].neighbor[ii],list[i].neighbor_distance[ii]);}
    // }
    record[0]=0;
    while (count < n)
    {
        long long int mini=MAX;int minNum=0;
        for(int j=0;j<n;j++){
            if (list[j].situation==1&&record[j]<mini){
                mini=record[j];minNum=j;    
            }
        }
        explore(list,minNum,record);
        // printf("\n*%d %d*\n",mini,minNum);
    }
       for(int i= 0;i<n;i++){printf("%d %lld\n",i,record[i]);}
}
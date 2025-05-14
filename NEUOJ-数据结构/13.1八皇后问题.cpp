#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
int staticQueen[8]={0,0,0,0,0,0,0,0};int n;
int lowbit(int x){
    return x&-x;
}
int panDuan(int* qipan,int x){
    if (qipan[x]!=0){
        return qipan[x];
    }
    int line=0;
    for(int i=1;i<=x;i++){
        int w=qipan[x-i];
        line|=w,line|=w<<i,line|=w>>i;
    }
    for(int i=x+1;i<8;i++){
        int w=qipan[i];
        line|=w,line|=w<<(i-x),line|=w>>(i-x);
    }
    // printf(" *%d* ",line);
    return 255^(255&line);
}
void printall(int* qipan){
    printf("\n");
    for(int j=0;j<8;j++){
        for (int i = 0; i < 8; i++){
            
            if (qipan[j]&(1<<i)){
                printf("Q");
            }
            else{
                printf(".");
            }
        }
        printf("\n");
    }
}
int go(int* qipan,int x){
    int line=qipan[x];
    // printf("goto %d line\n",x);
    int o=!staticQueen[x];
    // printf("\n=%d=",x);
    if (o){
        line=panDuan(qipan, x);
    }
    // if (x==7)
    // {
    //     printf("*%d*",line);
    // }
    while (line){
        // printf("=%d= %d",x,line);
        qipan[x]=lowbit(line);
        if (x==7){
            printall(qipan);
            qipan[x]=0;
            return 1;
        }
        go(qipan,x+1);
        // printf("back to %d line \n",x);
        line-=lowbit(line);
        // printf("\n[%d %d]",x,line);
    }
    if (o){
        qipan[x]=0;
    }
    return 0;
}
int main(){
    cin>>n;
    int qipan[8];for(int i=0;i<8;i++){qipan[i]=0;}
    for(int i=0;i<n;i++){int x,y;cin>>x,cin>>y;staticQueen[x]=1;qipan[x]=1<<y;}
    // printall(qipan);
    // printf("\n--------\n");
    go(qipan,0);
}
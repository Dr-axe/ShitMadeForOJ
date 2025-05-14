#include<stdio.h>
#include<stdlib.h>
#include<iostream>
int main(){
    int n;
    scanf("%d",&n);
    int** block=(int**)malloc(sizeof(int*)*n);
    for (int i = 0; i < n; i++)
    {
        block[i]=(int*)malloc(sizeof(int)*n);
        for (int j = 0; j < n; j++)
        {
            block[i][j]=0;
        }
    }
    for (int i = 0; i < n; i++){
        int u,k;
        scanf("%d %d",&u,&k);
        u--;
        for (int j = 0; j < k; j++)
        {
            int in;
            scanf("%d",&in);
            block[u][in-1]=1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ",block[i][j]);
        }
        printf("\n");
    }
}
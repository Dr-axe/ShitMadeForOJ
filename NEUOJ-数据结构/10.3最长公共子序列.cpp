#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    std::string a,b;
    int n;
    scanf("%d",&n);
    for (int w = 0; w < n; w++)
    {
        std::cin>>a>>b;
        int** block=(int**)malloc(sizeof(int*)*(a.length()+1));
        for (int i = 0; i <= a.length(); i++)
        {
            block[i]=(int*)malloc(sizeof(int)*(b.length()+1));
            block[i][0]=0;
        }
        for (int i = 0; i <= b.length(); i++)
        {
            block[0][i]=0;
        }
        for (int i = 0; i < a.length(); i++)//i行
        {
            for (int j = 0; j < b.length(); j++)//j列
            {
                if (a[i]==b[j])
                {
                    block[i+1][j+1]=block[i][j]+1;
                }
                else
                {
                    block[i+1][j+1]=block[i][j+1]>block[i+1][j]?block[i][j+1]:block[i+1][j];
                }
            }
        }
        printf("%d\n",block[a.length()][b.length()]);
        for (int i = 0; i <= a.length(); i++)
        {
            free(block[i]);
        }
        free(block);
    }
}
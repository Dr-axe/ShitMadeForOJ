#include<stdio.h>
#include<stdlib.h>
int main(){
    int n;
    scanf("%d",&n);
    int* position=(int*)malloc(sizeof(int)*(n+1));
    for (int i = 1; i <= n; i++)
    {
        int in;
        scanf("%d",&in);
        position[in]=i;
    }
    int count=1;
    for (int i = 1; i < n; i++)
    {
        if (position[i+1]<position[i])
        {
            count++;
        }
    }
    printf("%d",count);
}
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
int main(){
    int n;
    scanf("%d",&n);
    long long int sum=0;
    long long int maxSum=-2100000000;int input;
    for (int i = 0; i < n; i++)
    {        
        scanf("%d",&input);
        sum+=input;
        maxSum=maxSum>sum?maxSum:sum;
        if (sum<0)
        {
            sum=0;
        }
    }
    printf("%lld",maxSum);
}
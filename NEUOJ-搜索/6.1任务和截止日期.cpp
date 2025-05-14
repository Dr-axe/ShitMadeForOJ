#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
int main(){
    int n;
    scanf("%d",&n);
    int* nums=(int*)malloc(sizeof(int)*n);
    long long int sum=0;
    for (int i = 0; i < n; i++)
    {
        int d;
        scanf("%d %d",&nums[i],&d);
        sum+=d;
    }
    std::sort(nums,nums+n);
    long long int timeLine=0;
    for (int i = 0; i < n; i++)
    {
        timeLine+=nums[i];
        sum-=timeLine;
    }
    printf("%lld\n",sum);
}
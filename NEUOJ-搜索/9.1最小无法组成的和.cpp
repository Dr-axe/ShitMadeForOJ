#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
int main(){
    int n;
    scanf("%d",&n);
    int* nums=(int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        int input;
        scanf("%d",&input);
        nums[i]=input;
    }
    std::sort(nums,nums+n);
    long long int max_sum=0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i]>max_sum+1)
        {
            printf("%lld",max_sum+1);
            return 0;
        }
        else if (nums[i]<=max_sum+1)
        {
            max_sum+=nums[i];
        }
    }
    printf("%lld",max_sum+1);
}
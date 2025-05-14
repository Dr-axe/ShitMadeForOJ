#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<map>
int main(){
    int n,k;
    scanf("%d %d ",&n,&k);
    int* nums=(int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&nums[i]);
    }
    std::map<int,int>situation;
    std::map<int,int>checker;
    int level=0,left=-1;
    long long int sum=0;
    for (int i=0;i<n;i++)
    {
        if (situation.find(nums[i])!=situation.end())
        {
            checker.erase(situation[nums[i]]);
            situation[nums[i]]=i;
            checker[i]=nums[i];
            sum+=i-left;
            // printf("+(%d-%d)",i,left);
        }
        else
        {
            situation[nums[i]]=i;
            checker[i]=nums[i];
            level++;
            if (level>k)
            {
                auto it=checker.begin();
                left=it->first;
                situation.erase(it->second);   
                checker.erase(it->first);
                level--; 
            }
            sum+=i-left;
            // printf("+(%d-%d)",i,left);
        }
    }
        printf("%lld",sum);
}
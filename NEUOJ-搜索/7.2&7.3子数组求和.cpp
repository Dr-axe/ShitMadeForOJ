#include<stdio.h>
#include<iostream>
#include<map>
#include<stdlib.h>
int main(){
    int n,target;
    scanf("%d %d",&n,&target);
    std::map<long long int,int> store;
    long long int sum=0;
    long long int count=0;
    store[0]++;
    for (int i = 0; i < n; i++)
    {
        int input;
        scanf("%d",&input);
        sum+=input;
        auto it=store.find(sum-target);
        if (it!=store.end())
        {
            count+=it->second;
        }
        store[sum]++;
    }
    printf("%lld",count);
}
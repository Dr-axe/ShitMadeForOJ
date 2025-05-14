#include<stdio.h>
#include<iostream>
#include<map>
#include<stdlib.h>
int main(){
    int n;
    scanf("%d",&n);
    std::map<int,int> store;
    int sum=0;
    long long int count=0;
    store[0]++;
    for (int i = 0; i < n; i++)
    {
        int input;
        scanf("%d",&input);
        sum+=input;
        sum%=n;//sum作为余数维护
        if (sum<0)
        {
            sum+=n;
        }
        auto it=store.find(sum);//sum%n=n,x%n=n,则(sum-x)%n=0,整除
        if (it!=store.end())
        {
            count+=it->second;
        }
        store[sum]++;
    }
    printf("%lld",count);
}
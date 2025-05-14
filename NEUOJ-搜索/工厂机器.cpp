#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<map>
#include<cmath>
int main(){
    int n,target;
    scanf("%d %d",&n,&target);
    int* e=(int*)malloc(sizeof(int)*n);
    double eff=0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&e[i]);
        eff+=(double)1/e[i];
    }
    double mintime=target/eff;
    mintime=std::round(mintime);
    //printf("%lf\n",mintime);
    int min=static_cast<int>(mintime);
    std::map<std::pair<int,int>,int> timeLine;
    int count=0;
    for (int i = 0; i < n; i++)
    {
        count+=min/e[i];
        int left=e[i]-min%e[i];
        if (left==0)
        {
            count++;
        }
        timeLine[std::make_pair(left,e[i])]++;
    }
    int extratime=0;
    while (count<target)
    {
        auto it=timeLine.begin();
        extratime=it->first.first;
        count+=it->second;
        timeLine[std::make_pair(it->first.first+it->first.second,it->first.second)]=it->second;
        timeLine.erase(std::make_pair(it->first.first,it->first.second));
    }
    printf("%d",extratime+min);
}
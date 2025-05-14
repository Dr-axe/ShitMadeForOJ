#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<map>
#include<tuple>
int MAX_NUM=2000000000;
int main(){
    std::map<std::tuple<int,int,int>,int> tourists;
    int n;
    scanf("%d",&n);
    int* output=(int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        tourists[std::make_tuple(a, b,i)]++;
    }
    int count=0;
    while (!tourists.empty())
    {
        count++;
        int br=0;
        auto it=tourists.upper_bound(std::make_tuple(br,MAX_NUM,MAX_NUM));
        while (it!=tourists.end())
        {
            it->second--;
            output[std::get<2>(it->first)]=count;
            br=std::get<1>(it->first);
            if (it->second==0)
            {
                tourists.erase(it->first);
            }    
            it=tourists.upper_bound(std::make_tuple(br,MAX_NUM,MAX_NUM));
        }
    }
    printf("%d\n",count);
    for (int i = 0; i < n; i++)
    {
        printf("%d ",output[i]);
    }
}
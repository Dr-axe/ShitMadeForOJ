#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<map>
int main(){
    int n;
    scanf("%d",&n);
    std::map<int,int> list;
    int input;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&input);
        auto last=list.end();
        if (!list.empty())
        {
            last=std::prev(last);
        }
        // for(const auto pair:list){
        //     std::cout<<"=="<<pair.first<< pair.second<<"=="<<std::endl;
        // }
        if (last->first>=input)
        {
            // printf("way A \n");
            auto e=list.end();
            auto b=list.lower_bound(input);
            if (b!=list.begin()&&!list.empty())
            {
                b=std::prev(b);
            }
            // std::cout<<"||"<<e->first<< e->second<<"||"<<std::endl;
            // std::cout<<"||"<<b->first<< b->second<<"||"<<std::endl;
            if (b->first<input)
            {
                printf("%d ",b->second);
                b=std::next(b);
                list.erase(b,e);
            }
            else
            {
                printf("0 ");
                list.erase(b,e);
            }
            list[input]=i+1;
        }
        else
        {
            // printf("way B %d\n",input);
            auto it=list.lower_bound(input);
            if (it!=list.begin()&&!list.empty())
            {
                it=std::prev(it);
            }
            // std::cout<<"||"<<it->first<< it->second<<"||"<<std::endl;
            if (!list.empty())
            {
                printf("%d ",it->second);
            }
            else
            {
                printf("0 ");
            }    
            list[input]=i+1;    
        }
    }
}
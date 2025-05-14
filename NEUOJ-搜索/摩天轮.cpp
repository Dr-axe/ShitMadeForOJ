#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<map>
int n,limit;
int main(){
    scanf("%d %d",&n,&limit);
    std::map<int,int> children;
    int input;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&input);
        children[input]++;
    }
    int count=0;
    while (!children.empty())
    {
        auto it=std::prev(children.end());
        it->second--;
        int max=it->first;
        //printf("||%d--\n",it->first);
        if (it->second==0)
        {
            //printf("||%d erase\n",it->first);
            children.erase(it->first);
        }
        count++;
        auto target=children.upper_bound(limit-max);
        if (target!=children.begin())
        {
            target=std::prev(target);
        if (target!=children.end()&&(target->first)<=(limit-max))
        {
            target->second--;
            //printf("%d--\n",target->first);
            if (target->second==0)
            {
                //printf("%d erase\n",target->first);
                children.erase(target->first);
            }
        }
        }
    }
    printf("%d",count);   
}
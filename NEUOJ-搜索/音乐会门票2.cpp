#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<map>
int main(){
    int n,m;
    std::map<int,int> tickets;
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d",&x);
        tickets[x]++;
    }
    for (int i = 0; i < m; i++)
    {
        int x;
        scanf("%d",&x);
        if (tickets.upper_bound(x)!=tickets.begin())
        {
            auto it=std::prev(tickets.upper_bound(x));
            if (it!=tickets.end())
            {
                printf("%d\n",it->first);
                it->second--;
                if (it->second==0)
                {
                    tickets.erase(it->first);
                }
            }
            else
            {
                printf("-1\n");
            }
        }
        else
        {
            printf("-1\n");
        }
        
        
        
    }
    
}
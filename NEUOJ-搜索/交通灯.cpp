#include<stdio.h>
#include<stdlib.h>
#include<map>
int main(){
    std::map<int,int> road;
    std::map<int,int> leng;
    int l,n;
    scanf("%d %d",&l,&n);
    road[0]=l;
    road[l]=0;
    leng[0]++;leng[l]++;
    for (int i = 0; i < n; i++)
    {
        int input;
        scanf("%d",&input);
        road[input]++;
        auto the=road.find(input);
        auto next=std::next(the);
        //printf("后节点是%d",next->first);
        auto pre=std::prev(the);
        //printf("前节点是%d",pre->first);
        auto it=leng.find(pre->second);
        it->second--;
        //printf("%d %d--\n",it->second,it->first);
        if (it->second==0)
        {
            //printf("del%d\n",it->first);
            leng.erase(it->first);
        }
        road[input]=next->first-input;
        leng[next->first-input]++;
        pre->second=input-pre->first;
        leng[input-pre->first]++;
        auto max=std::prev(leng.end());
        printf("%d\n",max->first);
    }
}
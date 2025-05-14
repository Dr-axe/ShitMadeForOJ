#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<list>
#include<map>
/*莫队解法*/
int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    int sz=(int)floor(sqrt(n));//分成sz组
    int l=n/sz+(n%sz!=0);//每组的最大长度为l
    int* size=(int*)malloc(sizeof(int)*sz);
    for (int i = 0; i < sz; i++)
    {
        size[i]=l;
    }
    if (n%l!=0)
    {
        size[sz-1]=n%l;
    }
    std::map<int,std::list<int>> modui;
    for (int i = 0; i < sz; i++)
    {
        for (int ii = 1; ii <= size[i]; ii++)
        {
            modui[i].push_back(l*i+ii);
        }
    }
    int num=n;
    auto it=modui.begin();
    int locate_group=0;
    int locate=1;//记录上一个出列的数字的位置,也就是新的起点的位置
    for (int i = 0; i <n ; i++)
    {
        // for (int ii = 0; ii < sz; ii++)
        // {
        //     printf("=%d=",size[ii]);
        // }
        // printf("\n");
        int targetlocate=(locate+k%num)%num;//?
        if (targetlocate==0)
        {
            targetlocate=num;
        }
        // printf("*%d %d*\n",targetlocate,locate);
        locate=targetlocate;
        if (targetlocate<=locate_group)
        {
            locate_group=0;
            it=modui.begin();
        }
        while (locate_group+size[it->first]<targetlocate)
        {
            locate_group+=size[it->first];
            it=std::next(it);
            if (it==modui.end())
            {
                it=modui.begin();
            }
        }
        auto searcher=it->second.begin();
        int target=targetlocate-locate_group;
        for (int ii = 1; ii < target; ii++)
        {
            searcher=std::next(searcher);
        }
        printf("%d ",*searcher);
        it->second.erase(searcher);
        size[it->first]--;
        if (size[it->first]==0)
        {
            int w=it->first;
            it=std::next(it);
            if (it==modui.end())
            {
                it=modui.begin();
            }
            modui.erase(w);
        }
        
        num--;
    }
}
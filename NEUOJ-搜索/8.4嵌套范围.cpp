#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<math.h>
#include<set>
#include<algorithm>
int n;int count;
int lowbit(int x) {
    return x & -x;
}
int get(int* array,int x ){//获取0~x的前缀和
    if (x == 0) {
        return 0;
    }
    int sum = 0;
    while (x > 0) {
        sum += array[x];
        x -= lowbit(x);
    }
    return sum;
}
int add(int* array,int x,int y){
    while (x<=count){
        array[x]+=y;
        x+=lowbit(x);
    }
}
int main(){
    scanf("%d",&n);
    std::map<std::pair<int,int>,int> store;
    std::map<int,int> list;//存储值与在树状数组中排序位置的关系
    for (int i = 0; i < n; i++)
    {
        int l,r;
        scanf("%d %d",&l,&r);
        store[std::make_pair(l,-r)]=i;
        list[r]=0;
    }
    count=(int)list.size();
    int* r_store=(int*)malloc(sizeof(int)*(count+1));
    r_store[0]=0;
    while (true){
        auto it=list.begin();
        for(int i=1;i<=count;i++){
            r_store[i]=0;
            it->second=i;
            it=std::next(it);
        }
        break;
    }
    int* output_baohan=(int*)malloc(sizeof(int)*n);
    int* output_beiBaoHan=(int*)malloc(sizeof(int)*n);
    auto it=std::prev(store.end());
    for (int i = 0; i < n; i++)
    {
        auto the=list.find(-(it->first.second));//找到这个的存储序列 logn
        int position_in_r=the->second;
        output_baohan[it->second]=get(r_store,position_in_r);//存储要输出的结果 logn
        add (r_store,position_in_r,1);//存储右端点logn
        it=std::prev(it);//遍历下一个位置1
    }
    for (int i = 0; i <= count; i++){
        r_store[i]=0;
    }
    it=store.begin();
    for (int i = 0; i < n; i++)
    {  
        auto the=list.find(-(it->first.second));
        int positionInR=the->second;
        output_beiBaoHan[it->second]=i-get(r_store,positionInR-1);
        add(r_store,positionInR,1);
        it=std::next(it);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ",output_baohan[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ",output_beiBaoHan[i]);
    }
    return 0;
}
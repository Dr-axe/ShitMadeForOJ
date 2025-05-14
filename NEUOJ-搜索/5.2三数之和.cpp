#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<array>
int MAX=2100000000;
std::array<int,2> nums[9999];
int target,n;
int max=-MAX,min=MAX;    
int count=0;
int doubled_search(std::vector<std::array<int, 3>> &store,int mubiao){
    int l=0,r=count-1;
    int mid=(l+r)/2;
    while (l<=r)
    {
        if (store[mid][0]<mubiao)
        {
            l=mid+1;        
        }
        else if (store[mid][0]>mubiao)
        {
            r=mid-1;
        }
        else
        {
            return mid;
        }
        mid=(l+r)/2;
    }
    return -1;
}
int main(){
    scanf("%d %d",&n,&target);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&nums[i][0]);
        nums[i][1]=i+1;
        max=max>nums[i][0]?max:nums[i][0];
        min=min<nums[i][0]?min:nums[i][0];
    }
    sort(nums,nums+n);
    std::vector<std::array<int, 3>> store(n * (n - 1) / 2);
    for (int i = 0; i < n-1; i++)//先存储可能出现在结果中的两两组合
    {
        for (int j = i+1; j < n; j++)
        {
            if (nums[i][0]+nums[j][0]+min<=target&&nums[i][0]+nums[j][0]+max>=target)
            {
                store[count][0]=nums[i][0]+nums[j][0];
                store[count][1]=nums[i][1];
                store[count][2]=nums[j][1];
                count++;
            }
        }
    }
    std::sort(store.begin(), store.begin() + count, [](const auto& a, const auto& b) { return a[0] < b[0]; }); 
    for (int i = 0; i < n; i++)//开始一个个数找可能满足条件的两两组合
    {
        int w=doubled_search(store,target-nums[i][0]);//二分查找获取一组
        if (w!=-1)
        {
            int ll=w,rr=w;
            while (ll>0&&store[ll-1][0]==store[w][0])//获取左侧的组边界
            {
                ll--;
            }
            while (rr<count-1&&store[rr+1][0]==store[w][0])//获取右侧的组边界
            {
                rr++;
            }
            for (int j = ll; j <= rr; j++)
            {
                if (nums[i][1]!=store[j][1]&&nums[i][1]!=store[j][2])
                {
                    printf("%d %d %d",nums[i][1],store[j][1],store[j][2]);   
                    return 0;
                }   
            }   
        }   
    }
    printf("IMPOSSIBLE");
}
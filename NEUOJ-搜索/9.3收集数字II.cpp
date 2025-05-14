#include<stdio.h>
#include<stdlib.h>
#include<map>
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int* position=(int*)malloc(sizeof(int)*(n+1));
    position[0]=0;
    std::map<int,int>guild;//<position,num>
    for (int i = 1; i <= n; i++){
        int in;
        scanf("%d",&in);
        guild[i]=in;
        position[in]=i;
    }
    int count=1;
    for (int i = 1; i < n; i++)
    {
        if (position[i+1]<position[i])
        {
            count++;
        }
    }
    for(int i=0 ;i<m ;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        if (l!=r){
            int num_l=guild[l],num_r=guild[r];
            int old=(num_l!=1&&position[num_l-1]>l)+(num_l!=n&&l>position[num_l+1])+(num_r!=1&&position[num_r-1]>r)+(num_r!=n&&r>position[num_r+1]);
            position[guild[l]]=r;position[guild[r]]=l;int br=guild[l];guild[l]=guild[r];guild[r]=br;
            int xin=(num_l!=1&&position[num_l-1]>r)+(num_l!=n&&r>position[num_l+1])+(num_r!=1&&position[num_r-1]>l)+(num_r!=n&&l>position[num_r+1]);
            if (num_l-num_r==1||num_r-num_l==1){
                int larger=num_l>num_r?num_l:num_r;
                // printf("= %d %d =\n",position[larger],position[larger-1]);
                if (position[larger]>position[larger-1]){
                    old-=1;
                }
                else{
                    xin-=1;
                }
            }
            // printf("%d %d %d %d\n %d %d %d %d \n",(num_l!=1&&num_l!=n&&position[num_l-1]>l),(l>position[num_l+1]),(position[num_r-1]>r),(num_r!=1&&num_r!=n&&r>position[num_r+1]),(num_l!=1&&num_l!=n&&position[num_l-1]>r),(r>position[num_l+1]),(position[num_r-1]>l),(num_r!=1&&num_r!=n&&l>position[num_r+1]));
            // printf("*%d %d*",old,xin);
            count=count+xin-old;
        }
        printf("%d\n",count);
    }
}
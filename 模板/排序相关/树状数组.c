#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int n,m;
int lowbit(int x) {
    return x & -x;
}
int _begin(int x,int y){
    return (y - 1) & ~(x - 1);
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
    while (x<=n){
        array[x]+=y;
        x+=lowbit(x);
    }
}
int main(){
    scanf("%d %d",&n,&m);
    int* b_array=(int*)malloc(sizeof(int)*(n+2));
    b_array[0]=0;
    /*初始化*/
    for(int i=1;i<=n;i++){
        scanf("%d",&b_array[i]);
    }
    for (int i = 1; i <= n; i++){
        int x=lowbit(i);
        int level=(int)log2(x);
        int begin=_begin(x,i);
        for (int j = level-1; j >= 0; j--)
        {
            begin+=(1<<j);
            b_array[i]+=b_array[begin];    
        }
    }
    for (int i = 0; i < m; i++)
    {
        int command,x,y;
        scanf("%d %d %d",&command,&x,&y);
        if (command==1)
        {
            add(b_array,x,y);
        }
        else if (command==2)
        {
            int left=get(b_array,x-1),right=get(b_array,y);
            printf("%d\n",right-left);
        }
        else if (command==3)
        {
            for(int o=1;o<=n;o++){printf("%d ",b_array[o]);}
        }
    }
}
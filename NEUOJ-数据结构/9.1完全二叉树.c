#include<stdio.h>
#include<stdlib.h>
int main(){
    int num;
    scanf("%d",&num);
    int* nums=(int *)malloc(sizeof(int)*(num+1));
    for (int i = 1; i <= num; i++)
    {
        scanf("%d",&nums[i]);
    }
    for (int i = 1; i <= num; i++)
    {
        printf("node %d: key = %d,",i,nums[i]);
        if (i>1)
        {
            printf(" parent key = %d,",nums[i/2]);
        }
        if (i*2<=num)
        {
            printf(" left key = %d,",nums[i*2]);
        }
        if (i*2<num)
        {
            printf(" right key = %d,",nums[i*2+1]);
        }
        printf("\n");
    }
}
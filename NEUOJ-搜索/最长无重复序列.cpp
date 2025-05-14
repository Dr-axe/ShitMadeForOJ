#include<stdio.h>
#include<map>
#include<stdio.h>
#include<iostream>
int main(){
    int left=0,right=0,leng=0,max=1;
    int n;
    scanf("%d",&n);
    int* songs=(int*)malloc(sizeof(int)*n);
    std::map<int,int> list;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&songs[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (list[songs[right]])
        {
            while (songs[left]!=songs[right])
            {
                list.erase(songs[left]);
                left++;
            }
            leng=right-left;
            left++;
        }
        else
        {
            list[songs[right]]++;
            leng++;
            max=leng>max?leng:max;
        }
        right++;
    }
    printf("%d",max);
}
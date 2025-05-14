#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<map>
int main(){
    int n;
    std::cin>>n;
    std::map<int,int> nums;
    for (int i = 0; i < n; i++)
    {
        int input;
        scanf("%d",&input);
        nums[input]++;
    }
    int count=0;
    for(const auto pair : nums){
        count++;
    }
    std::cout<<count;
}
#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int cnt=n/25;
    n%=25;
    cnt+=n/10;
    n%=10;
    cnt+=n/5;
    n%=5;
    cnt+=n;
    printf("%d",cnt);
}
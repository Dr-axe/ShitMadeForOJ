#include<stdlib.h>
#include<stdio.h>
int main(){
    int n,max=0;
    long long int sum=0;
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        int input;
        scanf("%d",&input);
        max=max>input?max:input;
        sum+=input;
    }
    sum=sum>(max*2)?sum:(max*2);
    printf("%lld",sum);
}
/*
纯水
*/
#include<iostream>
int main(){
    long int a=1,b=1;
    long int input;
    scanf("%ld",&input);
        for (int i = 1; i < input; i++)
        {
            b+=a;
            a=b-a;
        }
        printf("%ld",b);
}
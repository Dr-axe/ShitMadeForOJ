/*
用最大堆做优先队列我真是个人物
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
int H=2000000;
using namespace std;
void maxHeapify(int* A,int i){//下沉
    int l=i*2;
    int r=i*2+1;
    int largest;
    if (l<=H&& A[l]>A[i])
    {
        largest=l;
    }
    else
    {
        largest=i;
    }
    if (r<=H&& A[r]>A[largest])
    {
        largest=r;
    }
    if (largest!=i)
    {
        int br;
        br=A[largest];
        A[largest]=A[i];
        A[i]=br;
        maxHeapify(A,largest);
    }
}
void up(int* A,int i){//上浮
    int parent=i/2;
    if (A[i]>A[parent]&&parent!=0)
    {
        maxHeapify(A,parent);
        if (parent!=1)
        {
            up(A,parent);
        }
    }   
}
int main(){
    int* A=(int*)malloc(sizeof(int)*(H+1));
    int i=1;
    A[0]=-1;
    while (true)
    {
        string command;
        cin>>command;
        if (command=="insert")
        {
            int input;
            scanf("%d",&input);
            A[i]=input;
            up(A,i);
            i++;
        }
        else if (command=="extract")
        {
            i--;
            printf("%d\n",A[1]);
            A[1]=A[i];
            A[i]=-1;
            maxHeapify(A,1);
        }
        else if (command=="end")
        {
            return 0;
        }   
    }
}
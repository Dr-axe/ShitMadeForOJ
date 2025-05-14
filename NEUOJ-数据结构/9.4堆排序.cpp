#include <stdio.h>
#include <iostream>
int H;
void maxHeapify(int* A,int i){
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
int main(){
    scanf("%d",&H);
    int* A=(int*)malloc(sizeof(int)*(H+1));
    for (int i = 1; i <= H; i++)
    {
        scanf("%d",&A[i]);
    }
    for (int i = H/2; i >=1; i--)
    {
        maxHeapify(A,i);
    }
    for (int i=H; i>0;i--)
    {
            printf("%d ",A[1]);
            A[1]=A[i];
            A[i]=-1;
            maxHeapify(A,1);
    }
}
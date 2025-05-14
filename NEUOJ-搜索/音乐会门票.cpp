#include<iostream>
#include<stdio.h>
#include<stdlib.h>
void merge(int *A, int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;
    int *L = (int *)malloc((n1 + 1) * sizeof(int));
    int *R = (int *)malloc((n2 + 1) * sizeof(int));
    // 复制子数组
    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int i = 0; i < n2; i++) R[i] = A[mid + i];
    // 设置哨兵（极大值）
    L[n1] = 2000000000;
    R[n2] = 2000000000;
    int i = 0, j = 0;
    for (int k = left; k < right; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }

    free(L);
    free(R);
}
void merge_sort(int *A, int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        merge_sort(A, left, mid);
        merge_sort(A, mid, right);
        merge(A, left, mid, right);
    }
}
void pmerge(int *A,int*B, int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;
    int *L = (int *)malloc((n1 + 1) * sizeof(int));
    int *R = (int *)malloc((n2 + 1) * sizeof(int));
    int *bL = (int *)malloc((n1 + 1) * sizeof(int));
    int *bR = (int *)malloc((n2 + 1) * sizeof(int));
    // 复制子数组
    for (int i = 0; i < n1; i++) bL[i] = B[left + i],L[i] = A[left + i];
    for (int i = 0; i < n2; i++) bR[i] = B[mid + i],R[i] = A[mid + i];
    // 设置哨兵（极大值）
    L[n1] = 2000000000;
    R[n2] = 2000000000;
    bL[n1] = 2000000;
    bR[n2] = 2000000;
    int i = 0, j = 0;
    for (int k = left; k < right; k++) {
        if (L[i] <= R[j]) {
            B[k]=bL[i];
            A[k] = L[i];
            i++;
        } else {
            B[k]=bR[j];
            A[k] = R[j];
            j++;
        }
    }
    free(bL);
    free(bR);
    free(L);
    free(R);
}
void pmerge_sort(int *A,int *B, int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        pmerge_sort(A, B,left, mid);
        pmerge_sort(A, B,mid, right);
        pmerge(A,B, left, mid, right);
    }
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int* tickets=(int*)malloc(sizeof(int)*n);
    int* tourists=(int*)malloc(sizeof(int)*m);
    int* position=(int*)malloc(sizeof(int)*m);
    int* backpack=(int*)malloc(sizeof(int)*m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&tickets[i]);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d",&tourists[i]);
        position[i]=i;
        backpack[i]=-1;
    }
    merge_sort(tickets,0,n);
    pmerge_sort(tourists,position,0,m);
    // for (int i = 0; i < m; i++)
    // {
    // printf("%d",position[i]);
    // }
    int i=n-1,j=m-1,count=0;
    while (i>=0&&j>=0)
    {
        if (tourists[j]>=tickets[i])
        {
            count++;
            backpack[position[j]]=tickets[i];
            // printf("%d位置赋值%d\n",position[i],tickets[i]);
            j--;i--;
        }
        else
        {
            i--;
        }
    }
    for (int ii = 0; ii < m; ii++)
    {
        printf("%d\n",backpack[ii]);
    }
    
}
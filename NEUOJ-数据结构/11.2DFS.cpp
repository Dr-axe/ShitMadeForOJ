#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
int t=1,count=0;
class Node {
    public:
        int size,situation,time_find,time_over;
        int* neighbor;
        int* neighbor_size;
        Node(int size) : size(size) {
            situation=0;
            time_find=0;time_over=0;
            neighbor=(int*)malloc(sizeof(int)*size);
        }
};
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
int explore(Node* list,int p){
    list[p].time_find = t++;
    count++;
    list[p].situation=1;
    for (int i = 0; i < list[p].size; i++)
    {
        if (!list[list[p].neighbor[i]].situation)
        {
            // printf("explore %d",list[p].neighbor[i]);
            explore(list,list[p].neighbor[i]);
        }
    }
    list[p].time_over = t++;
}
int main(){
    int n;
    scanf("%d",&n);
    Node* list=(Node*)malloc(sizeof(Node)*(n+1));
    for (int i = 0; i <n; i++)
    {
        int num,size;
        scanf("%d %d",&num,&size);
        list[num]=Node(size);
        for(int j=0;j<size;j++){
            int in;
            scanf("%d",&in);
            list[num].neighbor[j]=in;
        }
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     printf("\n*%d,大小：%d* ",i,list[i].size);
    //     for (int ii = 0; ii < list[i].size; ii++)
    //     {
    //         printf("%d->%d ",list[i].neighbor[ii],list[i].neighbor_size[ii]);
    //     }
    // }
    int beginning=1;
    while (count<n)
    {
        explore(list,beginning);
        if (count<n){
            while (list[beginning].situation!=0&&beginning<=n){
                beginning++;
            }
        }
    }
    for (int i = 1; i <= count; i++)
    {
        printf("%d %d %d\n",i,list[i].time_find,list[i].time_over);
    }
}
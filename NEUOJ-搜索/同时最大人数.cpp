#include<stdio.h>
#include<iostream>
#include<stdlib.h>
void merge(int *A, int left, int mid, int right) {
    int n1 = mid - left;
    int n2 = right - mid;
    int *L = (int *)malloc((n1 + 1) * sizeof(int));
    int *R = (int *)malloc((n2 + 1) * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int i = 0; i < n2; i++) R[i] = A[mid + i];
    L[n1] = 1000000000;
    R[n2] = 1000000000;
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
int main(){
    int n;
    scanf("%d",&n);
    int* come=(int*)malloc(sizeof(int)*n);
    int* leave=(int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d",&come[i],&leave[i]);
    }
    merge_sort(come,0,n);
    merge_sort(leave,0,n);
    int j=0,count=0,max=0;
    for (int i = 0; i <n;)
    {
        if (come[i]<leave[j])
        {
            count++;
            max=max>count?max:count;
            //printf("At %d ++\n",come[i]);
            i++;
        }
        else if (come[i]>leave[j])
        {
            count--;
            j++;
            //printf("At %d --\n",leave[i]);
        }    
        else
        {
            i++;j++;
        }
    }
    printf("%d",max);
}
#include<stdio.h>
#include<stdlib.h>
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
    int * nums=(int*)malloc(sizeof(int)*n);
    int *position=(int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&nums[i]);
        position[i]=i;
    }
    pmerge_sort(nums,position,0,n);
    int l=0,r=n-1;
    while (nums[l]+nums[r]!=m&&l!=r)
    {
        if (nums[l]+nums[r]<m)
        {
            l++;
            int rr=r;
            while (nums[rr]+nums[l]<=m&&rr<n)
            {
                if (nums[rr]+nums[l]==m)
                {
                    r=rr;
                    break;
                }   
                rr++;
            }
        }
        else
        {
            r--;
            int ll=l;
            while (nums[ll]+nums[r]>=m&&ll>=0)
            {
                if (nums[r]+nums[ll]==m)
                {
                    l=ll;
                    break;
                }
                ll--;
            }
        }
    }
    if (nums[l]+nums[r]==m&&l!=r)
    {
        printf("%d %d",position[l]+1,position[r]+1);
    }
    else
    {
        printf("IMPOSSIBLE");
    }
    free(nums);
    free(position);
}
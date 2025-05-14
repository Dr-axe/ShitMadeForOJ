/*dp做的*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
int MaxVal = 9999;
int n;
void optimalBST(double *p, double *q, int n,double** w,double** e)
{
    for (int i = 1; i <= n + 1; ++i){
        w[i][i - 1] = q[i - 1];
        e[i][i - 1] = q[i - 1];
    }
    for (int len = 1; len <= n; ++len)
    {
        for (int i = 1; i <= n - len + 1; ++i)
        {
            int j = i + len - 1;
            e[i][j] = MaxVal;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int k = i; k <= j; ++k)
            {
                double temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
                if (temp < e[i][j])
                {
                    e[i][j] = temp;
                }
            }
        }
    }
    printf("%lf",e[1][n]);
}
int main()
{
    scanf("%d",&n);
    double* p=(double*)malloc(sizeof(double)*(n+1));
    p[0]=0;
    double* q=(double*)malloc(sizeof(double)*(n+1));
    double** w=(double**)malloc(sizeof(double*)*(n+2));
    for (int i = 0; i < n+2; i++){
        w[i]=(double*)malloc(sizeof(double)*(n+2));
    }
    double** e=(double**)malloc(sizeof(double*)*(n+2));
    for (int i = 0; i < n+2; i++){
        e[i]=(double*)malloc(sizeof(double)*(n+2));
    }
    for (int i = 1; i <= n; i++){
        scanf("%lf",&p[i]);
    }
    for(int i=0;i<=n;i++){
        scanf("%lf",&q[i]);
    }
    optimalBST(p, q, n,w,e);
}
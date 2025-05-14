/*prim解决最小生成树问题*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
using namespace std;
int MAX=1<<30;
class Node {
    public:
        int size,situation,time_find,time_over;
        vector<int>neighbor;
        vector<int>neighbor_distance;
        Node() {
            situation=1;
            time_find=0;time_over=0;
        }
};
int main(){
    int n;
    scanf("%d",&n);
    vector<Node> points;
    for (int i = 0; i < n; i++){
        int input;
        int count=0;
        points.push_back(Node());
        for(int j = 0;j<n;j++){
            scanf("%d",&input);
            if (input^-1){//即input!=-1,原题给的是邻接矩阵-1表示不连通，不用!=-1是因为这么做比较快
                points[i].neighbor.push_back(j);
                points[i].neighbor_distance.push_back(input);
                count++;
            }   
        }
        points[i].size=count;
    }
    int count=1;
    map<int,int> wayWeb;
    for(int i=0;i<n;i++){wayWeb[i]=MAX;}
    int wayChecker=127,lengChecker=2147483520;
    set<int> minCheck;
    int position=1;
    int sum=0;
    while (count<n){
        points[position].situation=0;
        for (int i = 0; i < points[position].size; i++){//更新网络距离
            int way=points[position].neighbor[i];
            int d=points[position].neighbor_distance[i];
            if (wayWeb[way]>d&&points[way].situation){
                minCheck.erase(wayWeb[way]<<7|way);
                minCheck.insert(d<<7|way);
                wayWeb[way]=d;
            }
        }
        auto it=minCheck.begin();
        int num=*it;
        //printf("num=%d,sum+=%d",num,(num&lengChecker)>>7);
        sum+=(num&lengChecker)>>7;
        position=num&wayChecker;
        minCheck.erase(num);
        wayWeb[position]=MAX;
        count++;
    }
    printf("%d",sum);
}
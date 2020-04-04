/*
translation:
    共有n个公交站点1~n(2<=n<=1000),不同站点之间存在不同距离的双向路线t条(1<=t<=2000)
    求从1站点到n站点的最短距离
solution:
    单源最短路径问题，dijkstra即可
note:
    1.注意相同两站点间可能有多条路线，邻接表无影响，邻接矩阵需要取最小值
    2.注意t的范围是双向通道的，所以最大范围要*2
    3.注意数组应该初始化的不要忘了，如head
    4.注意算法中两点最短距离dis[]和两点距离edge.val不要用混
    5.注意dijkstra 初始dis[s]要初始化为0
date:
    2019.08.06
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
struct Edge
{
    int to,val,next;
};
const int MAXN = 1010;
const int MAXT = 4010;
const int INF = 0x3f3f3f3f;
int dis[MAXN],visit[MAXN];
int head[MAXN];
Edge edge[MAXT];
int cnt;
int t,n;

void add(int a,int b,int v);
void dijkstra(int s);
int main(){
    memset(head,-1,sizeof(head));
    cnt = 0;
    int a,b,v;
    scanf("%d %d",&t,&n);
    for(int i=0;i<t;i++){
        scanf("%d %d %d",&a,&b,&v);
        add(a,b,v);
        add(b,a,v);
    }
    dijkstra(1);
    printf("%d\n", dis[n]);
}

void add(int a,int b,int v){
    edge[cnt].val = v;
    edge[cnt].to = b;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}

void dijkstra(int s){
    memset(visit,0,sizeof(visit));
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    for(int i=1;i<=n;i++){
        int mt = -1;
        int min_dis = INF;
        for(int j=1;j<=n;j++){
        // for(int j=0;j<n;j++){
            if(!visit[j] && dis[j] < min_dis){
                min_dis = dis[j];
                mt = j;
            }
        }
        if(mt==-1)
            return;
        // printf("mt %d\n", mt);
        visit[mt] = 1;
        for(int j=head[mt];~j;j=edge[j].next){
            int t = edge[j].to;
            int val = edge[j].val;

            if(dis[mt]+val < dis[t]){
                dis[t] = dis[mt]+val;
            }
        }
    }
}

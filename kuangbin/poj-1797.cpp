/*
translation:
    有n个城市，m条道路，每条道路(双向)上都有承载量，
    求从城市1到城市n能够运送货物量的最大值(承载量)，由于一条路径的最大承载量为组成该路径的每个*道路*对应承载量的最小值
    所以本题即先求从城市1到城市n每条路径中，*道路承载量*的最小值，作为该*路径的承载量*，然后求所有路径承载量中的最大值
solution:
    仔细观察发现路径承载量的更新方式和单源最短路径相似，所以使用变形的dijkstra求解
note:
    1.注意更新函数及dis数组含义的更换，这里dis[i]表示原点到i点所有路径的最大承载量，初始值为0
        更新条件为 if(dis[t]<min(dis[mt],val))  ->  dis[t] = min(dis[mt],val)
        dis[s] 初始值这里要定为INF 
    2.注意该重置的初始化要初始化，同时不要再错写成sizeof(0)了
    3.边是无向的或者说双向的，所以add函数每次要调用两次
    4.注意本题每个样例间要有空行
    5.及时去掉多余输出
    6.本题还可用最大生成树的最小边求解
date:
    2019.08.29
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
const int MAXM = 1e6+10;
const int INF = 0x3f3f3f3f;
int dis[MAXN],visit[MAXN];
int head[MAXN];
Edge edge[MAXM];
int cnt,n,m;

void dijkstra(int s);
void add(int a,int b,int v);
int main(){
    int T;
    int kase = 1;
    scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof(head));
        memset(visit,0,sizeof(visit)); //写成sizeof(0)
        memset(dis,0,sizeof(dis)); //写成sizeof(0)
        cnt = 0;
        scanf("%d %d",&n,&m);
        int a,b,v;
        for(int i=0;i<m;i++){
            scanf("%d %d %d",&a,&b,&v);
            add(a,b,v);
            add(b,a,v); //忘添加

        }
        dijkstra(1);
        printf("Scenario #%d:\n%d\n\n",kase++,dis[n]); //需要空行
    }
}

void add(int a,int b,int v){
    edge[cnt].to = b;
    edge[cnt].val = v;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}

void dijkstra(int s){
    dis[s] = INF;
    for(int i=1;i<=n;i++){
        int max_dis = -INF;
        int mt = -1;
        for(int j=1;j<=n;j++){
            if(!visit[j] && dis[j]>max_dis){
                max_dis = dis[j];
                mt = j;
            }
        }
        if(mt==-1)
            return;
        // printf("mt %d\n", mt); //及时去掉不必要输出
        visit[mt] = 1;
        for(int j=head[mt];~j;j=edge[j].next){
            int t = edge[j].to;
            int val = edge[j].val;
            if(!visit[t] && min(dis[mt],val)>dis[t]){
                dis[t] = min(dis[mt],val);
            }
        }
    }
}

/*
translation:
    火车轨道上有很多交叉点，每个交叉点由一个开关控制，切换开关选择通向与其连接的其它交叉点，
    开关默认指向第一个数字代表的交叉点，不需要切换开关，其他别的方向需要进行一次切换操作 ，
    给定一个起点一个终点 ，问最少进行几次切换操作，能够使火车完成这个历程 ，如果开不到，输出“－1”。
    
solution:
   将每个交叉点默认指向的方向的通路距离置为0，后面其他相连的置为1
   然后用最短路的方法进行求解，最短距离就是开关的次数。

note:
    1.注意考虑有些地点无法到达的情况
date:
    2019.09.02
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int,int> pr;
struct Edge
{
    int val,to,next;
};
const int INF = 0x3f3f3f3f;
const int MAXN = 110;
const int MAXM = 1e4+10;
int visit[MAXN],head[MAXN],dis[MAXN],times[MAXN];
Edge edge[MAXM];
int n;
int cnt = 0;

void add(int a,int b,int v);
void dijkstra(int s);
bool spfa(int s);
int main(){
    memset(head,-1,sizeof(head));
    int st,ed;
    scanf("%d %d %d",&n,&st,&ed);
    for(int i=1;i<=n;i++){
        int m,to;
        scanf("%d",&m);
        for(int j=0;j<m;j++){
            scanf("%d",&to);
            if(!j)
                add(i,to,0);
            else
                add(i,to,1);
        }
    }
    dijkstra(st);
    // spfa(st);
    if(dis[ed]==INF) //没考虑无法到达的情况
        printf("-1\n");
    else printf("%d\n",dis[ed] );
}

void add(int a,int b,int v){
    edge[cnt].to = b;
    edge[cnt].val = v;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}

void dijkstra(int s){
    memset(visit,0,sizeof(visit));
    memset(dis,INF,sizeof(dis));
    dis[s] = 0;
    priority_queue<pr,vector<pr>,greater<pr> > q;
    q.push(make_pair(dis[s],s));
    int t;
    while(!q.empty()){
        t = q.top().second;
        q.pop();
        if(visit[t])
            continue;
        visit[t] = 1;
        for(int i=head[t];~i;i=edge[i].next){
            int val = edge[i].val;
            int to = edge[i].to;
            if(!visit[to] && dis[t]+val<dis[to]){
                dis[to] = dis[t]+val;
                q.push(make_pair(dis[to],to));
            }
        }
    }
}

bool spfa(int s){
    memset(visit,0,sizeof(visit));
    memset(times,0,sizeof(times));
    memset(dis,INF,sizeof(dis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    visit[s] = 1;
    times[s]++;
    int t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        visit[t] = 0;
        for(int i=head[t];~i;i=edge[i].next){
            int val = edge[i].val;
            int to = edge[i].to;
            if(dis[t]+val<dis[to]){
                dis[to] = dis[t]+val;
                if(!visit[to]){
                    visit[to] = 1;
                    q.push(to);
                    times[to]++;
                    if(times[to]>=n)
                        return false;
                }
            }
        }
    }
    return true;
}

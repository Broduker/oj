/*
translation:
    给N个小朋友分糖, 给出M组约束a, b, c表示b的糖果不能比a多c个以上, 求1号和N号的最大糖果差异数
    
solution:
    显然的线性查分约束问题
    对于a, b, c表示b的糖果不能比a多c个以上 , 即cnt[b]-cnt[a] <= c , 可以理解为a指向b的一条权值为c的单向边.
    这样一来整个系统也就转换成了图, 而对于求1和N的最大差异数, 即cnt[N]-cnt[1] 的最大值, 即1到N的最*短*路
    使用堆优化Dijkstra和栈优化SPFA进行求解
note:
    1.搞清楚差分约束的是最短路还是最长路
    2.求最短路时可用堆优化Dijkstra和栈优化SPFA两种,spfa使用队列会被卡时间
    3.spfa的弹出顶部元素时visit = 0不要忘了
date:
    2019.09.01
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct  Edge
{
    int to,val,next;
};
const int MAXN = 30010;
const int MAXM = 1.5e5+10;
const int INF = 0x3f3f3f3f;
typedef pair<int,int> pr;

int visit[MAXN],dis[MAXN],times[MAXN];
int head[MAXN];
Edge edge[MAXM];
int m,n;
int cnt = 0;

void add(int a,int b,int v);
void dijkstra(int s);
bool spfa(int s);
int main(){
    memset(head,-1,sizeof(head));
    scanf("%d %d",&n,&m);
    int a,b,v;
    for(int i=0;i<m;i++){
        scanf("%d %d %d",&a,&b,&v);
        add(a,b,v);

    }
    dijkstra(1);
    // spfa(1);
    printf("%d\n", dis[n]);
    return 0;
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
    visit[s] = 1;
    times[s]++;
    queue<int> q;
    q.push(s);
    int t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        visit[t] = 0;
        for(int i=head[t];~i;i=edge[i].next){
            int val = edge[i].val;
            int to = edge[i].to;
            if(dis[t]+val<dis[to]){
                dis[to] = dis[t] + val;
                if(!visit[to]){
                    q.push(to);
                    visit[to] = 1;
                    times[to]++;
                    if(times[to]>=n){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

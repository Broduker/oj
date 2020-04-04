#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
typedef pair<int,int> pr;
struct Edge
{
    int val,to,next;
};
const int INF = 0x3f3f3f3f;
const int MAXN = 210; //范围设错
const int MAXM = 4e4+10;
int visit[MAXN],head[MAXN],dis[MAXN],times[MAXN],mns[MAXN];
int w[MAXN];
Edge edge[MAXM];
int n,m;
int cnt = 0;

void add(int a,int b,int v);
void dijkstra(int s);
bool spfa(int s);
int main(){
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    int T;
    int kase = 1;
    scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof(head));
        cnt = 0; // 没加
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&w[i]);
        }
        scanf("%d",&m);
        int a,b;
        for(int i=1;i<=m;i++){
            scanf("%d %d",&a,&b);
            add(a,b,pow((w[b]-w[a])*1.0,3)); //道路值求反
        }
        spfa(1);
        int q,ed;
        scanf("%d",&q);
        printf("Case %d:\n", kase++);
        for(int i=0;i<q;i++){
            scanf("%d",&ed);
            if(mns[ed]||dis[ed]==INF||dis[ed]<3) //距离小于3也要输出?
                printf("?\n");
            else printf("%d\n", dis[ed]);
        }
    }
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
    memset(mns,0,sizeof(mns));
    dis[s] = 0;
    priority_queue<int,vector<int>,less<int> > q;
    q.push(s);
    visit[s] = 1;
    times[s]++;
    int t;
    while(!q.empty()){
        t = q.top();
        q.pop();
        visit[t] = 0;
        // if(times[t]>=n){
        // if(q.size()==n) //可能有不可达的点，行不通
        // if(mns[t])
            // return false;
        if(dis[t]<0) //dis[t]写成t
            return false;
        if(dis[t]<0){ //解决判断处在负环路径的节点
            mns[t] = 1;
            // continue;
        }
        for(int i=head[t];~i;i=edge[i].next){
            int val = edge[i].val;
            int to = edge[i].to;
            if(dis[t]+val<dis[to]){
                dis[to] = dis[t]+val;
                if(!visit[to]){
                    visit[to] = 1;
                    q.push(to);
                    times[to]++;
                    // if(times[to]>=n)
                        // return false;
                }
            }
        }
    }
    return true;
}

int spfa(){
    
}

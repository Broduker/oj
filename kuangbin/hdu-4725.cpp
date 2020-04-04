#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int,int> pr;
struct Edge
{
    int val,to,next;
};
const int MAXN = 3e5+10;
const int MAXM = 3e5+10;
const int INF = 0x3f3f3f3f;
int visit[MAXN],dis[MAXN],head[MAXN],times[MAXN];
Edge edge[MAXM];
vector<int> layer[MAXN];
int n,m,c;
int cnt;
int T;

void add(int a,int b,int v);
void dijkstra(int s);
bool spfa(int s);
int main(){
    int kase = 1;
    scanf("%d",&T);
    while(T--){
        memset(head,-1,sizeof(head));
        cnt = 0;
        scanf("%d %d %d",&n,&m,&c);
        int ly;
        for(int i=1;i<=n;i++){
            scanf("%d",&ly);
            layer[ly].push_back(i);
            // locate[i] = ly;
        }
        int a,b,v;
        for(int i=1;i<=m;i++){
            scanf("%d %d %d",&a,&b,&v);
            add(a,b,v);
        }
        // printf("#1 yes\n");
        for(int i=1;i<n;i++){
            // printf("size %d:%d,%d:%d\n", i,layer[i].size(),i+1,layer[i+1].size());
            if(layer[i].size() && layer[i+1].size()){ //写成判0了
                add(n+i*2,n+(i+1)*2-1,c);
            }
            for(int j=0;j<layer[i].size();j++){ //遍历错误的从1开始
                add(n+i*2-1,layer[i][j],0);
                add(layer[i][j],n+i*2,0);
            }
        }
        // printf("#2 yes\n");
        for(int j=0;j<layer[n].size();j++){ //遍历错误的从1开始
            add(n+n*2-1,layer[n][j],0);
        }
        // printf("#3 yes\n");
        // dijkstra(1);
        spfa(1);
        printf("Case #%d: ", kase++);
        if(dis[n]==INF) // 忘了考虑
            printf("-1\n");
        else printf("%d\n", dis[n]);
        for(int i=1;i<=n;i++){
            layer[i].clear();
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

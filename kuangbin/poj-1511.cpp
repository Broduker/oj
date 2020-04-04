/*
translation:
    有n-1个人从1号点出发，到剩余n-1个宣传点进行宣传，然后再回到1号点汇报结果，求所有人往返路径之和的最小值
    输入由T个案例组成。输入的第一行只包含正整数T。
    接下来是N和M，1 <= N,M <= 1000000，表示N个点和连接N个点的M条边。
    然后有M行，每行包括三个值U,V,W，表示从点U到点V需要W的路程，注意是单向通道。
    边的范围之和不超过1000,000,000，实际表明结果需要用long long存储，否则会WA
solution:
    看作求解两次单源最短路径问题，其中返回路径要将边倒转，再求解
    使用dijkstra+堆优化 或者spfa
    边的存储使用vector会超时
note:
    小坑坑了很久
    1.由于需要使用两次spfa，各种数组需要准备两份，这里注意cnt的值不能混用，也要准备两份，否则会导致访问越界
    2.dijkstra中min_dis和mt的赋值不要放在循环外面，每轮循环都需要重置，且不要忘了赋初始值
    3.函数中的memset不要漏写
    4.遍历范围1~n不要弄错
    5.spfa需要弹出的节点重新visit[t] = 0
    6.结果需要long long存储，否则会WA
date:
    2019.08.31
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct Edge
{
    int val,to,next;
};
typedef long long LL;
// typedef int LL;
const int MAXN = 1e6+10;
const int INF = 0x3f3f3f3f;
int dis[2][MAXN];
int visit[MAXN],times[MAXN];
int head[2][MAXN];
Edge edge[2][MAXN];
int n,m;
int cnt[2];
int T;

void add(int a,int b,int v,int direct);
void dijkstra(int s,int direct);
bool spfa(int s,int direct);
LL calnum();
int main(){
    // printf("%d\n",MAXN);
    int a,b,v;
    scanf("%d",&T);
    while(T--){
        // cnt = 0;
        memset(cnt,0,sizeof(cnt));
        memset(head,-1,sizeof(head));
        scanf("%d %d",&n,&m);
        for(int i=0;i<m;i++){
            scanf("%d %d %d",&a,&b,&v);
            add(a,b,v,0);
            add(b,a,v,1);
        }
        // if(T&1){
            // dijkstra(1,0);
            // dijkstra(1,1);
        // }
        // else{
            spfa(1,0);
            spfa(1,1);
        // }
        LL ans = calnum();
        printf("%I64d\n", ans);
    }
    return 0;
}

void add(int a,int b,int v,int direct){
    edge[direct][cnt[direct]].val = v;
    edge[direct][cnt[direct]].to = b;
    edge[direct][cnt[direct]].next = head[direct][a];
    head[direct][a] = cnt[direct]++;
}
void dijkstra(int s,int direct){
    // printf("%d\n",sizeof(dis));
    memset(dis+direct,INF,sizeof(dis[direct]));
    memset(visit,0,sizeof(visit));
    dis[direct][s] = 0;
    for(int i=1;i<=n;i++){
        int mt = -1; //赋初始值 错误的放到循环外面
        int min_dis = INF; //错误的放到循环外面
        for(int j=1;j<=n;j++){
            if(!visit[j] && dis[direct][j]<min_dis){
                mt = j;
                min_dis = dis[direct][j];
            }
        }
        if(mt==-1)
            return;
        visit[mt] = 1;
        for(int j=head[direct][mt];~j;j=edge[direct][j].next){
            int val = edge[direct][j].val;
            int to = edge[direct][j].to;
            if(!visit[to] && dis[direct][mt]+val<dis[direct][to]){
                dis[direct][to] = dis[direct][mt]+val;
            }
        }
    }
}

bool spfa(int s,int direct){
    memset(dis+direct,INF,sizeof(dis[direct])); //没有加
    memset(visit,0,sizeof(visit));
    memset(times,0,sizeof(times));
    dis[direct][s] = 0;
    queue<int> q;
    q.push(s);
    visit[s] = 1;
    int t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        visit[t] = 0; // 不要忘了
        for(int i=head[direct][t];~i;i=edge[direct][i].next){
            int val = edge[direct][i].val;
            int to = edge[direct][i].to;
            if(dis[direct][t]+val<dis[direct][to]){
                dis[direct][to] = dis[direct][t]+val;
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

LL calnum(){
    LL num = 0;
    for(int i=1;i<=n;i++){ //注意遍历范围
        num += dis[0][i]+dis[1][i];
        // num += dis[0][i];
    }
    return num;
}

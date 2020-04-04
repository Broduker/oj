/*
translation:
    该市最多有200个地铁站。
solution:
    最小生成树问题，使用prime或kruskal求解
note:
    1.注意两点多边的情况

date:
    2019.09.08
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pr;
struct DctEdge
{
    int to,val,next;
};
struct UctEdge
{
    int a,b,val;
};
const int MAXM = 80;
const int MAXN = 30;
const int INF = 0x3f3f3f3f;
UctEdge uctedge[MAXM];
DctEdge dctedge[MAXM*2]; //不要忘了边的正确范围
int head[MAXN],visit[MAXN],dis[MAXN];
int father[MAXN];
int cnt_dct,cnt_uct;
int n;

void add_dct(int a,int b,int v);
void add_uct(int a,int b,int v);
void Union(int a,int b);
int findFather(int t);
int prime(int s);
int kruskal();
bool cmp(UctEdge e1,UctEdge e2);

int main(int argc, char const *argv[])
{
    char ch1,ch2;
    while(scanf("%d",&n) & n){
        // n--; //有问题
        cnt_uct = cnt_dct = 0;
        memset(head,-1,sizeof(head));
        for(int i=0;i<n-1;i++){
            int cn;
            cin>>ch1>>cn;
            ch1 = ch1-'0';
            for(int j=0;j<cn;j++){
                int val;
                cin>>ch2>>val;
                ch2 = ch2-'0';
                add_dct(ch1,ch2,val);
                add_dct(ch2,ch1,val);
                add_uct(ch1,ch2,val);
            }
        }
        int ans = kruskal();
        // int ans = prime(ch1);
        printf("%d\n", ans);
    }
    return 0;
}

int prime(int s){
    memset(visit,0,sizeof(visit));
    memset(dis,0x3f,sizeof(dis));
    int ans = 0;
    dis[s] = 0;
    priority_queue<pr,vector<pr>,greater<pr> > q;
    q.push(make_pair(dis[s],s));
    int t;
    while(!q.empty()){
        t = q.top().second;
        q.pop();
        if(visit[t])
            continue;
        // printf("t %d\n", t);
        visit[t] = 1;
        ans += dis[t];
        for(int i=head[t];~i;i=dctedge[i].next){
            int to = dctedge[i].to;
            int val = dctedge[i].val;
            // printf("to %d\n", to);
            if(!visit[to] && val<dis[to]){
                dis[to] = val;
                q.push(make_pair(dis[to],to));
            }
        }
    }
    return ans;
}

bool cmp(UctEdge e1,UctEdge e2){
    return e1.val<e2.val;
}

int kruskal(){
    int ans = 0,edge_cnt=0;
    for(int i=0;i<MAXN;i++){ //注意初始化的范围不是n
        father[i] = i;
    }
    sort(uctedge,uctedge+cnt_uct,cmp);
    for(int i=0;i<cnt_uct;i++){
        int p1 = uctedge[i].a;
        int p2 = uctedge[i].b;
        // printf("p1 %d p2 %d\n", findFather(p1),findFather(p2));
        if(findFather(p1)!=findFather(p2)){
            Union(p1,p2);
            ans += uctedge[i].val;
            edge_cnt++;
            if(edge_cnt==n-1)
                break;
        }
    }
    if(edge_cnt!=n-1){
        // printf("edge %d point %d\n", edge_cnt,n-1);
        return -1;
    }
    return ans;
}

int findFather(int t){
    if(t!=father[t])
        t = findFather(father[t]);
    return t;
}

void Union(int a,int b){
    int f1,f2;
    f1 = findFather(a);
    f2 = findFather(b);
    if(f1!=f2){
        father[f1] = f2;
    }
}

void add_dct(int a,int b,int v){
    // printf("head %d\n", a);
    dctedge[cnt_dct].to = b;
    dctedge[cnt_dct].val = v;
    dctedge[cnt_dct].next = head[a];
    head[a] = cnt_dct++;
}
void add_uct(int a,int b,int v){
    uctedge[cnt_uct].a = a;
    uctedge[cnt_uct].b = b;
    uctedge[cnt_uct].val = v;
    cnt_uct++;
}

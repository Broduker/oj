/*
translation:
    现在所有牛要到编号为x的牛那里去参加聚会，并且所有牛参加聚会后还要回来，
    第一行给出n,m,x。 n代表牛的数量(编号1~n),m代表边数,x代表前往开会的牛的编号
    接下来m组三元组 代表m条有向边，代表从牛a到牛b需要花费c时间，
    除了牛x之外的牛，他们参加聚会并且回来都有对应的最短时间，从这些最短时间里找出一个最大值输出 
    N<=1000,M<=100,000

solution:
    分别求出每只牛到x去和回来时的最短时间和，并取最大值
    如果使用floid的O(n^3)会超时，因为有许多不必要的距离被计算
    可以看作两次单源最短路径求解，使用dijkstra进行两次求解
    由于是单向边，去时的求解可看作反向的单源最短路径，即先把边反向，就能转化成正常的单源最短路径，再进行求解
note:
    1.dijkstra算法不要忘了!visit的判断
    2.顶点t和边的序号j一定不要写混
    3.本题的编号是从1~n，遍历时一定不要弄成0~n-1
    4.求最小值，最大值判断符号不要弄反
date:
    2019.08.29
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
struct Edge
{
    int to,val,next;
};
const int MAXN = 1010;
const int MAXM = 1e5+10;
const int INF = 0x3f3f3f3f;
int head[2][MAXN],cnt[2]={0,0};
Edge edge[2][MAXM];
int visit[2][MAXN],dis[2][MAXN];
int n,m;

void add(int a,int b,int v,int direct);
void dijkstra(int s,int direct);
int disMaxCal(int s);
int main(){
    memset(head,-1,sizeof(head));
    int x;
    scanf("%d %d %d",&n,&m,&x);
    for(int i=0;i<m;i++){
        int a,b,v;
        scanf("%d %d %d",&a,&b,&v);
        add(a,b,v,1);
        add(b,a,v,0);
    }
    dijkstra(x,1);
    dijkstra(x,0);
    int ans = disMaxCal(x);
    printf("%d\n", ans);
    return 0;
}

void add(int a,int b,int v,int direct){
    edge[direct][cnt[direct]].to = b;
    edge[direct][cnt[direct]].val = v;
    edge[direct][cnt[direct]].next = head[direct][a];
    head[direct][a] = cnt[direct]++;
}

void dijkstra(int s,int direct){
    memset(visit+direct,0,sizeof(visit[direct]));
    memset(dis+direct,0x3f,sizeof(dis[direct]));
    dis[direct][s] = 0;
    for(int i=1;i<=n;i++){
        int min_dis = INF;
        int mt = -1;
        for(int j=1;j<=n;j++){
            if(!visit[direct][j] && dis[direct][j]<min_dis){ //忘加!visit
                min_dis = dis[direct][j];
                mt = j;
            }
        }
        if(mt==-1){
            // printf("fail\n");
            return;
        }
        visit[direct][mt] = 1;
        for(int j=head[direct][mt];~j;j=edge[direct][j].next){
            int val = edge[direct][j].val;
            int t = edge[direct][j].to;
            if(!visit[direct][t] && dis[direct][mt]+val<dis[direct][t]){ //忘加!visit
                dis[direct][t] = dis[direct][mt]+val; // 顶点t错写为边序号j
                // printf("dis[%d][%d] %d\n",direct,t,dis[direct][t] );
            }
        }
        // printf("dis[%d][%d] %d\n",direct,mt,dis[direct][mt] );
    }
}

int disMaxCal(int s){
    int maxDis = -INF;
    for(int i=1;i<=n;i++){ //遍历坐标范围写错为0~n-1
        if(i==s)
            continue;
        if(dis[0][i]+dis[1][i]>maxDis){ // 符号写反
            maxDis = dis[0][i]+dis[1][i];
            // printf("max %d\n", maxDis);
        }
    }
    return maxDis;
}

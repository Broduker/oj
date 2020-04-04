/*
translation:
    给定一个地图，给出k次查询，每次去除某个点，以及该点与其他地点的边，求出使剩余联通分支相连需要的边的个数
    input:
        第一行:n,m,k n为点的个数(n<1000)，编号1~n m为边的个数 k为查询的个数
        后m行:具有边的两个顶点对应编号
        最后一行:k个查询每次要去除的点的编号

solution:
    建立图的数据结构，通过dfs统计联通分支数，边的个数=联通分支数-1
note:
    1.由于是无向边，建边或删除边时每次要处理双向边
    2.被占领的点要实现标记visit[t] = 1,防止被错误统计
    3.序号是从1开始统计的，遍历下标不要弄错
    4.每次需要初始化的变量不要遗漏
    5.需要的分支数等于联通分支数-1
    6.实际上每次查询不需要重新拷贝地图，只需将删除点visit[t]置1即可
date:
    2019.11.26
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1010;
int edge[MAXN][MAXN],restEdge[MAXN][MAXN];
int visit[MAXN];
int n,m,k;
void dfs(int st);
int main(int argc, char const *argv[])
{
    memset(edge,0,sizeof(edge));
    memset(restEdge,0,sizeof(restEdge));

    scanf("%d%d%d",&n,&m,&k);
    int a,b;
    for(int i=0;i<m;i++){
        scanf("%d %d",&a,&b);
        edge[a][b] = 1;
        edge[b][a] = 1; //忘写
    }
    while(k--){
        memcpy(restEdge,edge,sizeof(edge));
        memset(visit,0,sizeof(visit));
        int cnt = 0;
        int t;
        scanf("%d",&t);
        visit[t] = 1; //需要去除被占领的点
        for(int i=1;i<=n;i++){
            restEdge[t][i] &= 0;
            restEdge[i][t] &= 0;
        }
        for(int i=1;i<=n;i++){
            if(!visit[i]){
                dfs(i);
                cnt++;
            }
        }
        printf("%d\n", cnt-1);
    }
    return 0;
}

// void add(int a,int b,int v){
//     edge[cnt].to = b;
//     edge[cnt].val = v;
//     edge[cnt].next = head[a];
//     head[a] = cnt++;
// }

void dfs(int st){
    visit[st] = 1;
    for(int i=1;i<=n;i++){ //遍历序号从1开始
        if(edge[st][i] && !visit[i]){
            dfs(i);
        }
    }
}

/*
translation:
    欧拉路径是图中每条边只经过一次的路径。
    类似地，欧拉回路是由相同顶点开始和结束的欧拉路径。
    图论证明了具有所有顶点度数均为偶数的连通图具有欧拉回路，这种图称为欧拉图。
    如果恰好有两个奇数度的顶点，所有的欧拉路径都从其中一个顶点开始，在另一个顶点结束。
    有欧拉路径但没有欧拉回路的图称为半欧拉图。
    题目给定一个无向图的节点的连接关系，按节点升序输出对应度数，同时判断属于Non-Eulerian Eulerian Semi-Eulerian

    input:
        第一行:n m 节点个数n(n<=500) 边的个数m
        后n行: a b 具有边的两端顶点对应的序号
        
solution:
    初始化并读入数据，用链式前向星储存无向图，同时统计节点度数；
    用DFS检查连通性；
    按序号升序输出每个节点的度数；
    根据之前的判断确定其属性并输出；
note:
    注意边的最大范围为n^2，同时由于是无向边，范围要再*2
    注意变量的初始化不要遗漏
    注意变量的判断条件不要写错
date:
    2019.11.30
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
const int MAXN = 510;
const int MAXM = 5e5+10; //范围少个0
struct edge{
    int to,next;
}edge[MAXM];
int head[MAXN],degree[MAXN];
int visit[MAXN];
int flag = 1;
int oddsum = 0;
int cnt = 0;

void dfs(int st);
void add(int a,int b);
int main(int argc, char const *argv[])
{
    memset(head,-1,sizeof(head));
    memset(visit,0,sizeof(visit));
    memset(degree,0,sizeof(degree));
    int n,m;
    scanf("%d %d",&n,&m);
    int a,b;
    for(int i=0;i<m;i++){
        scanf("%d %d",&a,&b);
        add(a,b);
        add(b,a);
        degree[a]++;
        degree[b]++;
    }
    dfs(1);
    for(int i=1;i<=n;i++){
        if(!visit[i]){
            flag = 0;
            break;
        }
    }
    if(flag){
        for(int i=0;i<=n;i++){
            if(degree[i]&1){
                oddsum++;
            }
        }
        switch(oddsum){
            case 0:flag = 1;break;
            case 2:flag = 2;break;
            default:flag = 0;
        }
    }
    for(int i=1;i<=n;i++){
        if(i>1) printf(" ");
        printf("%d", degree[i]);
    }
    printf("\n");
    switch(flag){
        case 0:printf("Non-Eulerian\n");break;
        case 1:printf("Eulerian\n");break;
        case 2:printf("Semi-Eulerian\n");break; //写错成3
        default:break;
    }
    return 0;
}

void add(int a,int b){
    edge[cnt].to = b;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}

void dfs(int st){
    visit[st] = 1;
    for(int i=head[st];~i;i=edge[i].next){
        int to = edge[i].to;
        if(!visit[to]){
            dfs(to);
        }
    }
}

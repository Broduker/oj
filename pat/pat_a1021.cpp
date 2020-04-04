/*
translation:
    给定一组边的连接关系，判断是否能组成树，如果能，输出使树高度最高对应的根节点(可能不止一个)
    否则输出联通分支的个数
    input:
        第一行:节点个数n，n<10^4
        后n-1行:n-1条存在边的节点对
solution:
    1、并查集可以判断是够是连通图，并可通过统计father[t]==t的个数即为连通分支数
    2、寻找最深根：进行两次DFS即可；
    第一次任选一个结点作为根，找出它的最深叶节点（记为集合A）；
    第二次以集合A中任一点作为根再找出最深叶节点（记为B）；两次集合的并集即为最深根节点集合。
note:
    1.由于是无向边，建边时每次要处理双向边，因此边的范围要*2
    2.head不要忘记初始化-1
    3.father[i]不要忘记初始化为i
    4.Union函数内的变量不要写错
    5.set合并可使用s1.insert(s2.begin(),s2.end())
date:
    2019.11.26
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;
const int MAXN = 2e4+10; //双向边范围*2
struct Edge
{
    int next,to;
    // int val;
}edge[MAXN];
int visit[MAXN];
int head[MAXN],father[MAXN];
int cnt = 0;
int maxdepth = 0;
set<int> maxId1,maxId2;

int findFather(int t);
void add(int a,int b);
void Union(int a,int b);
void dfs(int t,int depth,set<int> &maxId);
int main(int argc, char const *argv[])
{
    memset(visit,0,sizeof(visit));
    memset(head,-1,sizeof(head)); //忘记初始化,dfs卡死
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        father[i] = i;
    }
    int a,b;
    for(int i=0;i<n-1;i++){
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a); //双向
        Union(a,b);
    }
    // printf("union over\n");
    int brsize = 0;
    for(int i=1;i<=n;i++){
        if(findFather(i)==i){
            brsize++;
        }
    }
    // printf("find branch over\n");
    if(brsize>1){
        printf("Error: %d components\n", brsize);
    }
    else{
        dfs(1,0,maxId1);
        // printf("1st dfs over\n");
        auto it = maxId1.begin();
        memset(visit,0,sizeof(visit));
        maxdepth = 0;
        dfs(*it,0,maxId2);
        // printf("2nd dfs over\n");
        maxId1.insert(maxId2.begin(),maxId2.end());
        for(it = maxId1.begin();it!=maxId1.end();it++){
            printf("%d\n", *it);
        }
    }
    return 0;
}


void add(int a,int b){
    edge[cnt].to = b;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}
int findFather(int t){
    return father[t]==t ? t : father[t] = findFather(father[t]);
}

void Union(int a,int b){
    int f1 = findFather(a);
    int f2 = findFather(b);
    if(f1!=f2){
        father[f1] = f2; //注意用哪个变量
    }
}

void dfs(int t,int depth,set<int> &maxId){
    if(depth>maxdepth){
        // printf("id %d depth %d\n",t,depth);
        maxdepth = depth;
        maxId.clear();
        maxId.insert(t);
    }
    else if(depth==maxdepth){
        maxId.insert(t);
    }
    visit[t] = 1;
    for(int i=head[t];~i;i=edge[i].next){
        int to = edge[i].to;
        if(!visit[to]){
            dfs(to,depth+1,maxId);
        }
    }
}

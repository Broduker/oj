/*
translation:
    给定一个具有n个节点的树，树上的边都具有权值。
    树中一条路径的长度被定义为路径上所有边的权值的异或和：
    输出异或长度最大值
    输入格式:
        第一行包含整数n，表示树的节点数目。
        接下来n-1行，每行包括三个整数u，v，w，表示节点u和节点v之间有一条边权重为w。
    数据范围:
        1≤n≤100000
        0≤u,v<n
        0≤w<231

solution:
    设D[x]表示根节点到x的路径上所有的边权的xor值,显然,D[x] = D[father[x]] ^ w[x][father[x]]
    我们可以通过DFS求出D[x]的全部值
    而x节点到y节点的路径上所有边权的异或结果等于 D[x] ^ D[y] 得到,
    因为"x到root"和"y到root"这两条路径重叠部分进行异或时恰好被抵消(a ^ a = 0)
    因此我们原问题就转换成为D[1]~D[n]中选择任意两个数,xor的结果值就会变成最大.也就是No.143题.

note:
    1.注意因为构造的是无向图，所以边的范围要*2
    2.注意问题转化的过程中，要把root到root的情况考虑进去！
    3.注意trie对应编号的初始值是1而非0 不要设置错
    4.注意异或运算的初始赋值是0 不是1
    5.注意循环范围不要设置错
date:
    2020.03.17
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1e5+10;
const int MAXE = MAXN*2;
struct Edge
{
    int next,to,val;
}edge[MAXE];

int head[MAXN];
int trie_cnt,str_cnt,tree_cnt;
int num[MAXN],visit[MAXN];
int trie[MAXN*32][2];


void add(int a,int b,int v){
    edge[tree_cnt].to = b;
    edge[tree_cnt].val = v;
    edge[tree_cnt].next = head[a];
    head[a] = tree_cnt++;
}

void dfs(int t,int last){
    visit[t] = 1;
    for(int i=head[t];~i;i=edge[i].next){
        int to = edge[i].to;
        if(!visit[to]){
            // visit[to] = 1;
            int w = edge[i].val;
            num[str_cnt++] = w^last;
            // printf("num %d\n", w^last);
            dfs(to, w^last);

        }
    }
}

void create(int t){
    int p = 1;
    for(int i=30;i>=0;i--){
        int b = (t>>i) & 1;
        if(!trie[p][b]){
            trie[p][b] = ++trie_cnt;
            // printf("insert %d %d\n",p,b);
        }
        p = trie[p][b];
    }
}

int search(int t){
    int p = 1, ans = 0;
    for(int i=30;i>=0;i--){
        int b = (t>>i)&1;
        // printf("b %d\n",b);
        if(trie[p][b^1]){
            ans |= (1<<i);
            p = trie[p][b^1];
            // printf("ans %d\n",ans);
        }
        else p = trie[p][b];

    }
    // printf("ans %d\n",ans);
    return ans;
}


int main(int argc, char const *argv[])
{
    memset(head,-1,sizeof(head));
    memset(visit,0,sizeof(visit));
    trie_cnt = 1; //错误设置成0
    str_cnt = tree_cnt = 0;

    int n;
    scanf("%d",&n);
    int u,v,w;
    for(int i=0;i<n-1;i++){
        scanf("%d %d %d",&u,&v,&w);
        add(u,v,w);
        add(v,u,w);
    }
    create(0);
    dfs(0,0); //初始值不要弄错
    int maxt = 0;
    for(int i = 0;i<str_cnt;i++){
        create(num[i]);
        maxt = max(search(num[i]), maxt);
    }
    printf("%d\n", maxt);
    return 0;
}

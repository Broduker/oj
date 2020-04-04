/*
translation:
    有多种汇币，汇币之间可以交换，同时需要手续费，
    当你用A币100交换B币时，A到B的汇率是29.75，手续费是0.39，那么你可以得到(100 - 0.39) * 29.75 = 2963.3975的B币。
    第一行四个数，N表示货币的总数；M为兑换点的数目；S为nick手上的钱的类型；V为nick手上的钱的数目；
    1<=S<=N<=100, 1<=M<=100, V是一个实数 0<=V<=103. 
    接下来M行，每行六个数，整数a和b表示两种货币，a到b的汇率，a到b的佣金，b到a的汇率，b到a的佣金
    （0<=佣金<=10^2，10^-2<=汇率<=10^2）
    问s币的金额经过交换最终得到的s币金额数能否增加 能输出YES,否则输出NO
solution:
    
    将不同的兑换点看成节点，汇率及手续费看成路的权值
    使用spfa求解，判断s到达各个点的路径中是否存在正环
    若s能到达某点，因为双向边，所以s也一定能回到s
    因此如果有正环，即使正环中有没有s,可以在这个正环中多走几次再回到s，一定能赚。
    ，
note:
    粗心写错了很多地方，尤其是int、double类型的定义
    1.初始金额sn为double，spfa传参时不要定义成int
    2.dis[i]表示将s货币兑换到i货币所能得到的最大值，为double，不要定义成int
    3.使用临变量rate、cms进行赋值时，记得为double，不要定义成int
    4.使用赋值表达式不要弄错，直接把复制过来的小于判断语句当赋值语句用了
    5.注意spfa更新与dijkstra略有不同，只要有更优的值就更新，不管是否已经访问过或已经加入队列中
    6.spfa返回值不要弄错，把两种返回值都写成一样的了
    7.这里变形的spfa中dis[s]初始要赋值成初始金额而不是0
    8.注意判断是否是正环的条件
date:
    2019.08.30
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

struct Egde
{
    int to,next;
    double rate,cms;
};

const int MAXN = 110;
const int MAXM = 210;
int visit[MAXN],times[MAXN];
double dis[MAXN]; // double写成int
int head[MAXN];
Egde edge[MAXM];
int cnt = 0;
int n,m;

void add(int a,int b,double rate,double cms);
bool spfa(int s,double sn); //sn定义成int了
int main(){
    memset(head,-1,sizeof(head));
    int s;
    double sn;
    scanf("%d %d %d %lf",&n,&m,&s,&sn);
    int a,b;
    double rate[2],cms[2];
    for(int i=0;i<m;i++){
        scanf("%d %d %lf %lf %lf %lf",&a,&b,&rate[0],&cms[0],&rate[1],&cms[1]);
        add(a,b,rate[0],cms[0]);
        add(b,a,rate[1],cms[1]);
    }
    if(spfa(s,sn)){
        printf("YES\n");
    }
    else printf("NO\n");
    return 0;
}

void add(int a,int b,double rate,double cms){
    edge[cnt].to = b;
    edge[cnt].rate = rate;
    edge[cnt].cms = cms;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}

bool spfa(int s,double sn){
    memset(visit,0,sizeof(visit));
    memset(dis,0,sizeof(dis));
    memset(times,0,sizeof(times));
    dis[s] = sn;
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
            int j = edge[i].to;
            double rate = edge[i].rate; // double写成int
            double cms = edge[i].cms; // double写成int
            if(dis[j]<(dis[t]-cms)*rate){
                dis[j] = (dis[t]-cms)*rate; //赋值写成小于号
                if(!visit[j]){ // 注意写法与dijkstra不同
                    visit[j] = 1;
                    q.push(j);
                    times[j]++;
                    if(times[j]>=n)
                        return true;
                }
            }
        }
    }
    return false; //写成true
}

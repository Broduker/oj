/*
translation:
    一群人通过通话来往组成一个无向图，边表示节点对应的两人的通话时间
    找出满足条件的连通图，要求连通图的结点个数必须大于2，并且总权重值大于阙值K，
    确定各个连通图中的头领对应的结点(头结点为该联通图中，与之连接的所有边的权重之和最大的那个节点)，
    最后按字典序输出各个头结点的名称以及头结点所在连通图的结点数。
    input:
        第1行:n,k n表示通话的边的个数n(n<1000)，K表示寻找连通图对应的阙值(k<1000)
        后n行:name1 name2 time name表示节点对应的名字，由三个字母组成，time表示通话时间(time<1000)

solution:
    通过map建立名字和序号的映射关系，建立无向图，建图时统计各个节点关联边的权值和
    dfs遍历统计联通分支节点总数、联通分支权重综合、权重总和最多的节点对应的序号
note:
    1.由于一个联通分支内的所有边都需要进行计算，如果在dfs时计算就会出现漏算边的情况
      所以可以在建边时就计算各个节点对应的权重总和，
      然后dfs计算连通分支的权重总和只需将节点的总和相加。最后除2即可(由于双向边节点的权重值会重复统计)
    2.注意双向边的范围*2，
    3.节点的范围上限也是边的范围
    3.输入参数不要忘
    4.各种计数值不要弄混
    5.该初始化的参数不要忘了初始化
date:
    2019.11.26
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>

using namespace std;
map<string,int> name;
map<int,string> rev;
const int MAXE = 2010; //双向边范围
const int MAXN = 35;
int head[MAXN];
int visit[MAXN];
int calltime[MAXN];

int headid,sbsum,callsum,maxcall;
int sbcnt = 0,ecnt = 0;
struct Cluster
 {
     string headname;
     int num;
     Cluster(){}
     Cluster(string name,int n):headname(name),num(n){}
 };
 struct Edge{
    int to,next,val;
 }edge[MAXE];
vector<Cluster> cluster;
//int cnt = 0;

bool cmp(Cluster c1,Cluster c2);
void add(int a,int b,int v);
void dfs(int st);
int main(int argc, char const *argv[])
{
    memset(visit,0,sizeof(visit));
    memset(head,-1,sizeof(head));
    memset(calltime,0,sizeof(calltime));
    int k,theta;
    scanf("%d %d",&k,&theta); //少参数
    string s1,s2;
    int t;
    for(int i=0;i<k;i++){
        cin>>s1>>s2>>t;
        if(name.find(s1)==name.end()){
            rev[sbcnt] = s1;
            name[s1] = sbcnt++; //写成cnt
        }
        if(name.find(s2)==name.end()){
            rev[sbcnt] = s2;
            name[s2] = sbcnt++;
        }
        add(name[s1],name[s2],t);
        add(name[s2],name[s1],t);
        calltime[name[s1]] += t;
        calltime[name[s2]] += t;
    }
    for(int i=0;i<sbcnt;i++){
        if(!visit[i]){
            sbsum = 0; //一个团伙的总人数
            callsum = 0; //一个团伙通话总时长
            maxcall = 0; //单人最多通话时间
            dfs(i);
            callsum /= 2;
            // printf("sbsum %d,callsum %d,maxcall %d headid %d\n", sbsum,callsum,maxcall,headid);
            // cout<<rev[headid]<<endl;
            if(sbsum>2 && callsum>theta){
                cluster.push_back(Cluster(rev[headid],sbsum));
            }

        }
    }
    printf("%d\n", cluster.size());
    if(cluster.size()){ //没有的情况要考虑到

        sort(cluster.begin(),cluster.end(),cmp);
        for(auto it = cluster.begin();it!=cluster.end();it++){
            cout<<(*it).headname<<" "<<(*it).num<<endl;
        }
    }
    return 0;
}

void dfs(int st){
    visit[st] = 1;
    callsum += calltime[st];
    sbsum++;
    for(int i=head[st];~i;i=edge[i].next){
        int to = edge[i].to;
        if(!visit[to]){
            // callsum += edge[i].val;
            // calltime[st] += edge[i].val;
            dfs(to);
        }
    }
    if(calltime[st]>maxcall){
        headid = st;
        maxcall = calltime[st];
        // printf("headid %d\n", headid);
    }
}

void add(int a,int b,int v){
    edge[ecnt].to = b;
    edge[ecnt].val = v;
    edge[ecnt].next = head[a];
    head[a] = ecnt++;
}

bool cmp(Cluster c1,Cluster c2){
    return c1.headname < c2.headname;
}

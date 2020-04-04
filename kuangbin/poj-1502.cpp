/*
translation:
    N个电脑(1~n)要进行信息传递，电脑传递信息给自己不需要时间，电脑i与电脑j之间双向传递信息的时间都是一样的，
    不同电脑之间传递信息所需要的时间由一个矩阵的下三角给出。由于自身到自身花费的时间为0，所以也没有给出。
    数字表示权值，x表示两点间不可达
    根据给定的时间矩阵，求从电脑1传递消息给其他所有电脑需要的时间(可同时发送信息)。

solution:
    建立邻接阵，特殊处理一下值为x的情况，运用单源最短路径算法
    求出第一个电脑到其他所有电脑的最短传递信息时间，然后取这些最短时间中的最大者即可
    使用spfa或dijkstra均可
    ，
note:
    1.数据输入遇到很多坑
        最佳方法使用string str配合cin进行字符串和数字转换，或者使用char str[]配合atoi进行转换
        由于输入不包括val[1][1]，所以若从1开始遍历，会多使用一个getchar
        使用getchar要注意数字可能不止一位
        使用getchar或scanf后面都要注意数字后面有空格要吸收(每行最后一个除外)
        ungetc回退字符时，如果是用int ch接收和回退的，再次读取是int值，所以要使用char ch接收和回退
    2.spfa初始点忘了times[s]++
    3.spfa每次弹出queue顶部值之后，忘了访问情况恢复 visit[t] = 0
    4.sizeof又写错

date:
    2019.08.30
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct Edge
{
    int val,to,next;
};
const int MAXN = 110;
const int MAXM = 1e4+10;
const int INF = 0x3f3f3f3f;
Edge edge[MAXM];
int head[MAXN],visit[MAXN],dis[MAXN],times[MAXN];
int n,cnt = 0;


bool spfa(int s);
void add(int a,int b,int v);
int main(){
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    // getchar();
    int v;
    char ch;
    char num[10];
    for(int i=2;i<=n;i++){ //i=1开始会多用一个getchar
        getchar();
        for(int j=1;j<i;j++){
            
            ch = getchar(); //数字可能不止两位
            // getchar(); //数字间有空格
            // printf("ch %c %d\n",ch,ch );
            if(ch=='x'){
                // printf("%d,%d\n",i,j);
                // continue;
            }
            else{
                ungetc(ch,stdin);
                scanf("%d",&v);
                // printf("%d->%d %d\n",i,j,v);
                add(i,j,v);
                add(j,i,v);
            }
            if(j!=i-1)
                getchar(); //有空格
            
            // scanf("%s",num);
            // if(num[0]!='x'){
            //     v = atoi(num);
            //     add(i,j,v);
            //     add(j,i,v);
            // }
        }
    }
    spfa(1);
    int ans = 0;
    for(int i=1;i<=n;i++){
        ans = max(ans,dis[i]);
    }
    printf("%d\n", ans);
    return 0;
}

void add(int a,int b,int v){
    edge[cnt].to = b;
    edge[cnt].val = v;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}
bool spfa(int s){
    memset(visit,0,sizeof(visit));
    memset(times,0,sizeof(times));
    memset(dis,INF,sizeof(dis)); //sizeof又写错
    queue<int> q;
    dis[s] = 0;
    visit[s] = 1;
    times[s]++; //忘了写
    q.push(s);
    int t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        visit[t] = 0; //没写
        for(int i=head[t];~i;i=edge[i].next){
            int val = edge[i].val;
            int j = edge[i].to;
            if(dis[t]+val<dis[j]){
                dis[j] = dis[t]+val;
                // printf("dis[%d] %d->%d %d\n",j,t,j,dis[j]);
                if(!visit[j]){
                    visit[j] = 1;
                    q.push(j);
                    times[j]++;
                    if(times[j]>=n){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

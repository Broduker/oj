/*
translation:
    小k要从家去学校，他可以选择步行或者地铁，步行的速度是10km/h，地铁的速度是40km/h。
    假设小k到地铁站可以随意上下地铁，并且可以在地铁线路之间转换。所有的地铁运行都是双向的。
    求上学所需要的最短时间，以分钟为单位，四舍五入输出整数。
    输入第一行包括家和学校的x，y坐标，接下来是若干条地铁线。
    每条地铁线包括站点的x，y坐标，有序排列，假设地铁在相邻的两站之间直线运行，每条地铁线至少有两个站，地铁线的描述以-1，-1结束。
    该市最多有200个地铁站。
solution:
    本题是典型的单源最短路径问题，主要关键问题是建图，使用spfa或dijkstra求解
    首先对于地铁，按照40km/h的速度求出每条地铁线相邻的两站之间需要的时间，并建立图
    然后对于包括地铁所有站点，家、学校的所有地点，利用O(n^2)，按照10km/h的速度求出不同地点之间需要的时间，并建图
    注意之前已经根据地铁求出时间的路线不要被走路的时间覆盖
    然后调用spfa或dijkstra求解

note:
    建图遇到坑
    1.首先建图要完全，除了每条地铁线相邻点需要建图，所有出现的点之间都可以以走路的方式联通
    2.由于本题用double保存距离，所以dis不能用memset初始化为INF，
      导致原程序先求出了初始dis，这样的后果就是while(!q.empty)第一次循环就不会有更新，相当于算法没有执行
      所以一定要按照步骤初始化
    3.注意要定义成double的地方不要弄成int
    4.注意本题所有道路为双向的
    5.spfa弹出顶部时visit[t] = 0不要忘了
    6.//dt[i][i] 的情况要考虑
    7.判断条件!visit不要忘写
    8.下标不要写错
date:
    2019.09.01
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
struct Point
{
    int x,y;
};
typedef pair<double,int> pr; //应该是double
const int MAXN = 210;
const int INF = 0x3f3f3f3f;
Point points[MAXN];
double dt[MAXN][MAXN];
int visit[MAXN],times[MAXN];
double dis[MAXN];
Point st,ed;
int cnt = 0;

bool spfa(int s);
void dijkstra(int s);
double disCal(Point &p1,Point &p2);
int main(){
    // fill(dt,dt+MAXN*MAXN,0);
    memset(dt,0,sizeof(dt)); //double可以这么用吗
    scanf("%d %d %d %d",&st.x,&st.y,&ed.x,&ed.y);
    points[cnt++] = st;
    Point p1,p2;
    while(~scanf("%d %d",&p1.x,&p1.y)){
        points[cnt++] = p1;
        while(scanf("%d %d",&p2.x,&p2.y) && ~p2.x && ~p2.y){
            points[cnt] = p2;
            dt[cnt-1][cnt] = dt[cnt][cnt-1] = disCal(points[cnt-1],points[cnt]) / 40000.0; //双向通路
            // printf("%d,%d %d,%d\n",points[cnt-1].x,points[cnt-1].y,points[cnt].x,points[cnt].y );
            // printf("%d,%d %lf\n", cnt-1,cnt,dt[cnt-1][cnt]);
            cnt++;
        }
        // for(int i=1;i<cnt;i++){
        //     dt[i][i+1] = dt[i+1][i] = disCal(points[i],points[i+1]) / 40000; //双向通路
        //     printf("dt%d %d %lf\n", i,i+1,dt[i][i+1]);
        // }
    }
    points[cnt++] = ed;
    for(int i=0;i<cnt;i++){
        for(int j=0;j<cnt;j++){
            if(!dt[i][j]){
                dt[i][j] = dt[j][i] = disCal(points[i],points[j]) / 10000; //注意min避免了走路覆盖原有地铁距离;
                // printf("dt%d %d %lf\n", i,j,dt[i][j]);
            }
        }
        // dis[i] = dt[0][i];
    }
    spfa(0);
    // dijkstra(0);
    printf("%d\n",int(dis[cnt-1]*60+0.5) );
}


bool spfa(int s){
    memset(visit,0,sizeof(visit));
    memset(times,0,sizeof(times));
    fill(dis,dis+cnt,INF);
    // memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    visit[s] = 1;
    times[s]++;
    int t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        visit[t] = 0; // 别忘了
        for(int i=0;i<cnt;i++){
            // printf("%lf+%lf %f\n",dis[t],dt[t][i],dis[i] );
            if(i!=t && dis[t]+dt[t][i]<dis[i]){ //dt[i][i] 的情况
                // printf("update %d\n", i);
                dis[i] = dis[t]+dt[t][i];
                if(!visit[i]){
                    q.push(i);
                    visit[i] = 1;
                    times[i]++;
                    if(times[t]>=cnt){
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

void dijkstra(int s){
    memset(visit,0,sizeof(visit));
    fill(dis,dis+cnt,INF);
    // memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    priority_queue<pr,vector<pr>,greater<pr> > q;
    q.push(make_pair(dis[s],s));
    int t;
    while(!q.empty()){
        t = q.top().second;
        q.pop();
        if(visit[t]) //标号别错
            continue;
        visit[t] = 1;
        for(int i=0;i<cnt;i++){
            if(!visit[i] && dis[t]+dt[t][i]<dis[i]){ //visit判断不要忘了
                // printf("update %d\n", i);
                dis[i] = dis[t]+dt[t][i];
                q.push(make_pair(dis[i],i));
            }
        }
    }
}

double disCal(Point &p1,Point &p2){
    // return sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)*1.0);
}

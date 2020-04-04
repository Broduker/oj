/*
translation:
    给定一个n*m字符矩阵,'#'代表障碍，'.'代表路，'@'代表KFC，Y、M分别代表两人位置
    Ｙ和Ｍ约在一家KFC碰面，问他俩到KFC所花费的路程之和最少是多少
solution:
    分别对Y、M进行BFS，求出其各自到不同KFC所需要的最短距离，然后对应相加找出最小值输出
 
note:
    1.除了墙的位置，他俩都可以走到，所以当到达一个'@'计算距离后可以继续遍历，而不是用else和遍历互斥
    2.可能出现KFC被墙围起来的情况，俩人都到不了，把时间赋初值的时候赋为INF即可
    3.注意dis要初始化为0
    4.注意min_dis在第二次BFS时统计的值才有效
    5.两个BFS之间注意要初始化需要重置的值

date:
    2019.08.26
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct Point
{
    int x,y;
    int depth;
    Point(int x_,int y_,int d_=0):x(x_),y(y_),depth(d_){}
    Point():depth(0){}
};
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
const int MAXN = 210;
const int INF = 0x3f3f3f3f;
char dt[MAXN][MAXN];
int visit[MAXN][MAXN],dis[MAXN][MAXN];
int n,m;
int min_dis;

void bfs(Point p);
bool isAvail(int x,int y);
int main(){

    cin.tie(0);
    cin.sync_with_stdio(false);
    Point p1,p2;
    while(~scanf("%d %d",&n,&m)){
        min_dis = INF;
        memset(dis,0,sizeof(dis)); // 忘记初始化
        for(int i=0;i<n;i++){
            getchar();
            for(int j=0;j<m;j++){
                dt[i][j] = getchar();
                if(dt[i][j]=='Y'){
                    p1.x = i;
                    p1.y = j;
                }
                if(dt[i][j]=='M'){
                    p2.x = i;
                    p2.y = j;
                }
            }
        }
        memset(visit,0,sizeof(visit));
        bfs(p1);
        memset(visit,0,sizeof(visit)); // 忘记重置
        min_dis = INF; //不能统计第一次的值
        bfs(p2);
        printf("%d\n", min_dis*11);
    }
    return 0;
}
void bfs(Point p){
    queue<Point> q;
    q.push(p);
    visit[p.x][p.y] = 1;
    while(!q.empty()){
        Point t = q.front();
        q.pop();
        if(dt[t.x][t.y]=='@'){
            dis[t.x][t.y] += t.depth;
            // printf("%d,%d dis %d\n", t.x,t.y,dis[t.x][t.y]);
            min_dis = min(min_dis,dis[t.x][t.y]);
        }
        // else{ //即使找到@也要继续遍历
            int x1,y1;
            for(int i=0;i<4;i++){
                x1 = t.x + dx[i];
                y1 = t.y + dy[i];
                if(isAvail(x1,y1) && dt[x1][y1]!='#' && !visit[x1][y1]) {
                    q.push(Point(x1,y1,t.depth+1));
                    visit[x1][y1] = 1;
                }
            }
        // }
    }
}

bool isAvail(int x,int y){
    if(x>=0 && x<n && y>=0 && y<m){
        return true;
    }
    return false;
}

/*
translation:
    给定一个矩阵，'@'代表石油资源，上下左右对角线相连的石油资源属于同一区域
    求共有多少不同的石油资源
solution:
    依此对每一个代表石油资源且还未被访问的点进行bfs进行统计即可
 
note:
    1.矩阵用char存储不要弄成int
    2.输入n,m不要弄混
    3.visit需要赋值的地方不要遗漏
    4.dt下标不要因为复制粘贴而弄错
    5.cnt的统计是每进行一次bfs加1
    6.进行dfs求解也可以

date:
    2019.08.27
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN = 110;
struct Point
{
    int x,y;
    Point(int x_,int y_):x(x_),y(y_){}
    Point(){}
};
int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,1,1,1,0,-1,-1,-1};
char dt[MAXN][MAXN];
int visit[MAXN][MAXN];
int cnt,n,m;

void bfs(int i,int j);
bool isAvail(Point p);
int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    // int n,m;
    while(~scanf("%d %d",&n,&m) && n && m){ //m写成n
        memset(visit,0,sizeof(visit));
        cnt = 0;
        for(int i=0;i<n;i++){
            scanf("%s",dt[i]);
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(dt[i][j]=='@' && !visit[i][j]){
                    // printf("%d,%d\n", i,j);
                    cnt++;
                    bfs(i,j);
                }
            }
        }
        printf("%d\n", cnt);
    }
}

void bfs(int i,int j){
    queue<Point> q;
    q.push(Point(i,j));
    visit[i][j] = 1; //忘写
    Point t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        Point tp;
        for(int i=0;i<8;i++){
            tp.x = t.x + dx[i];
            tp.y = t.y + dy[i];
            if(isAvail(tp) && dt[tp.x][tp.y]=='@' && !visit[tp.x][tp.y]){ //dt下标写成i,j
                // cnt++;
                q.push(tp);
                visit[tp.x][tp.y] = 1;
            }
        }
    }
}

bool isAvail(Point p){
    if(p.x>=0 && p.x<n && p.y>=0 && p.y<m){
        return true;
    }
    return false;
}

/*
translation:
    给定一个5*5矩阵，'0'代表可走，'1'代表不可走
    求出从(0,0)到(4,4)最短路径，并输出
solution:
    从(0,0) bfs即可 pre二维数组记录路径
 
note:
    1.输入一定要注意，使用int要有& ,且为二维数组
    2.注意路径输出函数的写法

date:
    2019.08.27
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct Point
{
    int x,y;
    int depth;
    Point(int x_,int y_,int d=0):x(x_),y(y_),depth(d){}
    Point():depth(0){}
};
int dt[5][5];
int visit[5][5];
Point pre[5][5];
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
// int ans  = 0;

void bfs(int i,int j);
bool isAvail(Point p);
void PrintPath(int i,int j);
int main(){
    memset(visit,0,sizeof(visit));
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            scanf("%d",&dt[i][j]); //忘加&，dt[i][j]写成dt[i]
        }
    }
    bfs(0,0);
    PrintPath(4,4);
}

void bfs(int i,int j){
    queue<Point> q;
    q.push(Point(i,j));
    visit[i][j] = 1;
    Point t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        if(t.x==4 && t.y==4){
            // ans = t.depth;
            break;
        }
        Point tp;
        for(int i=0;i<4;i++){
            tp.x = t.x + dx[i];
            tp.y = t.y + dy[i];
            if(isAvail(tp) && dt[tp.x][tp.y]==0 && !visit[tp.x][tp.y]){
                // printf("%d,%d\n",tp.x,tp.y );
                visit[tp.x][tp.y] = 1;
                // tp.depth = t.depth + 1;
                pre[tp.x][tp.y].x = t.x;
                pre[tp.x][tp.y].y = t.y;
                q.push(tp);
            }
        }
    }
}

bool isAvail(Point p){
    return (p.x>=0 && p.x<5 & p.y>=0 && p.y<5) ? true : false;
}

void PrintPath(int i,int j){
    if(i || j){
        PrintPath(pre[i][j].x,pre[i][j].y);
        printf("(%d, %d)\n",i,j);
    }
    else printf("(0, 0)\n");
}

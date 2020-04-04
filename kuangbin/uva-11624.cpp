/*
translation:
    给定一个n*m迷宫矩阵，'M'代表火源，'J'代表乔初始位置，'#'代表障碍，'.'代表通路 
    joe每次可向四个方向之一移动一格，火源每次向四个方向同时蔓延一格，无论是乔还是火都不会到达有墙的位置。
    计算joe是否可以从任意边界逃出，输出最小逃生步数，否则输出IMPOSSIBLE
solution:
    分别建立joe、火源的queue
    注意可能存在多个火源，初始将其都压入queue，进行bfs，并记录到达各个位置的时间
    然后对joe对应的queue进行bfs，-> 如果未有火源到达或者火源到达的时间大于Joe到达的时间，则可以行走
    输出到达边界时的路程+1即为结果，否则输出IMPOSSIBLE
note:
    踩了很多坑
    1.可能存在多个火源，初始时要都压入queue
    2.注意是否考虑到初始joe就在边界的情况
    3.当循环条件写为!q_fire.empty()||!q_joe.empty()时，内部q_joe/q_fire操作时要再具体是否为空
    否则如果为空没有判断，获取的值会是错误的
    4.本题实际上q_fire、q_joe要分别进行bfs而不能一起，因为要比较的joe到达之前对应位置是否有火源已经到达
    这个需要q_fire提前bfs记录对应时间
    5.如果用visit_fire记录时间的话，要注意他同时用来标记是否访问，默认值为0，
    所以t_joe.depth+1<visit_fire[tp_joe.x][tp_joe.y]会出现错误判断 所以需要结合！visit_fire[tp_joe.x][tp_joe.y]判断
    6.本题将T变量定义全局变量时间正常，而定义成局部变量程序会很慢，原因未知
date:
    2019.08.28
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 1010;
struct Point
{
    int x,y;
    int depth;
    Point(int x_,int y_,int d=0):x(x_),y(y_),depth(d){}
    Point():depth(0){}
};
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

int visit_fire[MAXN][MAXN],visit_joe[MAXN][MAXN];
Point fire[MAXN],joe;
char dt[MAXN][MAXN];
int cnt,n,m;
int ans;
int T;
void bfs();
bool isBound(Point p);
bool isAvail(Point p);
int main(){
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    // int T;
    scanf("%d",&T);
    while(T--){
        memset(visit_joe,0,sizeof(visit_joe));
        memset(visit_fire,0,sizeof(visit_fire));
        cnt = 0;
        scanf("%d %d",&n,&m);
        for(int i=0;i<n;i++){
            getchar();
            for(int j=0;j<m;j++){
                dt[i][j] = getchar();
                // printf("%d,%d, %c\n",i,j,dt[i][j]);
                if(dt[i][j]=='J'){
                    joe.x = i;
                    joe.y = j;
                }
                else if(dt[i][j]=='F'){
                    fire[cnt].x = i;
                    fire[cnt].y = j;
                    cnt++;
                }
            }
        }
        // if(T==666-64){
        //     printf("64\n");
        //     for(int i=0;i<n;i++){
        //         for(int j=0;j<m;j++){
        //             printf("%c",dt[i][j]);
        //         }
        //         printf("\n");
        //     }
        //     printf("joe %d %d\n",joe.x,joe.y);
        // }
        // printf("joe %d %d\n",joe.x,joe.y);
        bfs();
        if(~ans){
            // printf("T:%d %d\n",666-T, ans);
            printf("%d\n",ans);
        }
        else printf("IMPOSSIBLE\n");
    }
}

void bfs(){
    // if(isBound(Point(joe.x,joe.y))){
    //     ans = 1;
    //     return; //不要写成break
    // }
    queue<Point> q_fire,q_joe;
    q_joe.push(Point(joe.x,joe.y));
    visit_joe[joe.x][joe.y] = 1;
    for(int i=0;i<cnt;i++){
        Point p(fire[i].x,fire[i].y);
        q_fire.push(p);
        visit_fire[p.x][p.y] = 1;
    }
    Point t_fire,t_joe;
    // while(!q_fire.empty() || !q_joe.empty()){ //有坑，下面需要分别判断
    while(!q_fire.empty()){
        if(!q_fire.empty()){
            t_fire = q_fire.front();
            q_fire.pop();
            Point tp_fire;
            for(int i=0;i<4;i++){
                tp_fire.x = t_fire.x + dx[i];
                tp_fire.y = t_fire.y + dy[i];
                if(isAvail(tp_fire) && dt[tp_fire.x][tp_fire.y]!='#' && !visit_fire[tp_fire.x][tp_fire.y]){
                    tp_fire.depth = t_fire.depth + 1; //t写成tp
                    // printf("fire %d,%d\n", tp_fire.x,tp_fire.y);
                    q_fire.push(tp_fire);
                    visit_fire[tp_fire.x][tp_fire.y] = tp_fire.depth;
                }
            }
        }
    }
        // if(!q_joe.empty()){ //如果为空不能继续下去
        while(!q_joe.empty()){ //如果为空不能继续下去

            t_joe = q_joe.front();
            q_joe.pop();
            if(isBound(t_joe)){
                ans = t_joe.depth+1;
                // printf("Yes %d,%d %d\n",t_joe.x,t_joe.y,t_joe.depth );
                return; //不要写成break
            }
            Point tp_joe;
            for(int i=0;i<4;i++){
                tp_joe.x = t_joe.x + dx[i];
                tp_joe.y = t_joe.y + dy[i];
                // visit_fire[tp_joe.x][tp_joe.y]不要搞错变量和下标
                // if(isAvail(tp_joe) && dt[tp_joe.x][tp_joe.y]!='#' && !visit_fire[tp_joe.x][tp_joe.y] && !visit_joe[tp_joe.x][tp_joe.y]){
                if(isAvail(tp_joe) && dt[tp_joe.x][tp_joe.y]!='#' && (!visit_fire[tp_joe.x][tp_joe.y] || t_joe.depth+1<visit_fire[tp_joe.x][tp_joe.y]) && !visit_joe[tp_joe.x][tp_joe.y]){
                    tp_joe.depth = t_joe.depth + 1; //t写成tp
                    // printf("%d,%d %d\n", tp_joe.x,tp_joe.y,tp_joe.depth);
                    q_joe.push(tp_joe);
                    visit_joe[tp_joe.x][tp_joe.y] = 1;
                }
            }
        }

    ans = -1;
}

bool isBound(Point p){
    return (p.x==0 || p.x==n-1 || p.y==0 || p.y==m-1) ? true : false;
}
bool isAvail(Point p){
    return (p.x>=0 && p.x<n && p.y>=0 && p.y<m) ? true : false;
}

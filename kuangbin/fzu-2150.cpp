/*
translation:
    给出一个m*n矩阵，'#'表示草坪，'.'表示空地，然后可以选择在任意的两个草坪格子点火(可重合)，火每次向周围四个格子扩散，
    选择两个点，使得燃烧所有的草坪花费时间最小，并输出最小值
solution:
    第一种办法
        最多只可以点两次火，所以如果草的堆数超过2则肯定不可以。
        1.用深搜判断是否符合只有小于等于两堆草的规定，不符合直接输出-1；
        2.如果符合，则分两种情况 是一堆还是两堆，分别用广搜求出这两种情况的最短时间即可
            对于两个分开的草坪的情况来看，每个草坪都点一把火。
            每个草坪随机找到一点进行一次bfs，找到离开始bfs点最远的点，再从该店bfs一次，此次走过的步数除以2就是答案
            上述方法其实不正确(比如2*2都是草的区域)，所以应该用第二种方法的正常遍历去做
    第二种方法
        由于数据较小，枚举两个位置的所有情况，然后用bfs求解(初始都压入队列)
        如果dfs后仍有未点燃的草，则该情况无解，否则记录最小值，每次bfs最后遍历的点的深度即为所需时间

note:
    遇到很多坑
    1.sizeof(visit)写成sizeof(0)
    2.范围grass[MAXN*MAXN]错写成grass[MAXN]
    3.不论哪种方法，注意单独讨论一个草坪也没有的情况
    4.判断仍有未燃烧的草坪应写~unVisited()，而不是unVisited()==-1
    5.每次bfs前如果是重新开始的，一定要重置visit
    6.使用temp来传参和接受返回值两用时，由于返回值的depth会不为零，继续传参导致结果错误，所以传参前temp.depth重新置零
    7.两个草坪时，结果为两者的最大者，而非求和
    8.bfs遍历时，错误使用Point型变量，顶部t错写成传入的初始p，并且改正没有把所有使用的错处都修改完毕
    9.第一种方法中两个草坪对应的求解方法有问题 
date:
    2019.08.28
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
const int MAXN = 15;
const int INF = 0x3f3f3f;
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
char dt[MAXN][MAXN];
int visit[MAXN][MAXN];
Point grass[MAXN*MAXN]; //最大范围弄错
int n,m,cnt;
int ans;

int unVisited();
bool isAvail(Point p);
Point bfs(Point p1,Point p2);
Point bfs(Point p1);
int main(int argc, char const *argv[])
{
    // freopen("data.in","r",stdin);
    // freopen("data.out","w",stdout);
    int T;
    int kase = 1;
    scanf("%d",&T);
    while(T--){
        memset(visit,0,sizeof(visit)); // sizeof(visit)写成sizeof(0)
        cnt = 0,ans = INF;
        scanf("%d %d",&n,&m);
        // printf("n %d,m %d\n", n,m);
        for(int i=0;i<n;i++){
            getchar();
            for(int j=0;j<m;j++){
                dt[i][j] = getchar();
                // printf("%d,%d %c\n",i,j,dt[i][j] );
                if(dt[i][j]=='#'){
                    // printf("grass!\n");
                    grass[cnt].x = i;
                    grass[cnt++].y = j;
                    // printf("visit %d\n", visit[i][j]);
                }
            }
        }
        // printf("cnt %d\n",cnt );
        if(!cnt){ // 一个草坪也没有
            ans = 0;
        }
        else{
            bfs(grass[0]);
            int u = unVisited();
            // printf("u %d\n", u);
            if(~u){
                bfs(grass[u]);
                // u = unVisited();
                // printf("u %d\n", u);
                if(~unVisited()){ // 2个以上草坪 错写成u==-1
                    // printf("-1\n");
                    ans = -1;
                }
                else{ // 只有两个草坪
                    memset(visit,0,sizeof(visit)); //每个bfs前需要重置
                    Point temp = bfs(grass[0]);
                    // printf("temp %d,%d %d\n",temp.x,temp.y,temp.depth);
                    memset(visit,0,sizeof(visit));
                    temp.depth = 0; //共用变量depth会改变
                    temp = bfs(temp);
                    // printf("temp1 %d,%d %d\n",temp.x,temp.y,temp.depth);
                    ans = (temp.depth+1)/2;
                    u = unVisited();
                    temp.depth = 0;
                    temp = bfs(grass[u]);
                    memset(visit,0,sizeof(visit));
                    temp.depth = 0;
                    temp = bfs(temp);
                    ans = max((temp.depth+1)/2,ans); //原先写成两者求和
                    // printf("temp2 %d,%d %d\n",temp.x,temp.y,temp.depth);
                }
            }
            else{ // 只有一个草坪
                Point temp;
                for(int i=0;i<cnt;i++){
                    for(int j=i;j<cnt;j++){
                        // printf("md (%d,%d)(%d,%d)\n",grass[i].x,grass[i].y,grass[j].x,grass[j].y);
                        memset(visit,0,sizeof(visit));
                        temp = bfs(grass[i],grass[j]);
                        ans = min(ans,temp.depth);
                        // printf("ans %d\n", ans);
                    }
                }
            }
        }
        // if(!cnt){ // 忘了加，导致结果为0的输出-1
        //     ans = 0;
        // }
        // else{

        //     for(int i=0;i<cnt;i++){
        //         for(int j=i;j<cnt;j++){
        //             memset(visit,0,sizeof(visit));
        //             Point temp = bfs(grass[i],grass[j]);
        //             if(~unVisited())
        //                 continue;
        //             ans = min(ans,temp.depth);
        //         }
        //     }
        //     if(ans==INF){
        //         ans = -1;
        //     }
        // }

        // int k = 220;
        // if(kase==k){
        //     printf("case %d\n",k);
        //     printf("%d %d\n", n,m);
        //     for(int i=0;i<n;i++){
        //         for(int j=0;j<m;j++){
        //             printf("%c", dt[i][j]);
        //         }
        //         printf("\n");
        //     }
        // }
        printf("Case %d: %d\n",kase++, ans);

    }
    return 0;
}

Point bfs(Point p1,Point p2){
    queue<Point> q;
    q.push(p1);
    q.push(p2);
    visit[p1.x][p1.y] = 1;
    visit[p2.x][p2.y] = 1;
    Point t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        Point tp;
        for(int i=0;i<4;i++){
            tp.x = t.x + dx[i];
            tp.y = t.y + dy[i];
            if(isAvail(tp) && dt[tp.x][tp.y]=='#' && !visit[tp.x][tp.y]){
                tp.depth = t.depth + 1;
                q.push(tp);
                visit[tp.x][tp.y] = 1;
                // printf("%d,%d %d\n", tp.x,tp.y,tp.depth);
            }
        }
    }
    // printf("t %d,%d %d\n", t.x,t.y,t.depth);
    return t;
}

Point bfs(Point p){
    queue<Point> q;
    q.push(p);
    visit[p.x][p.y] = 1;
    Point t;
    while(!q.empty()){
        t = q.front();
        q.pop();
        Point tp;
        for(int i=0;i<4;i++){
            tp.x = t.x + dx[i]; //t写成p
            tp.y = t.y + dy[i]; //t写成p
            // printf("%d,%d %c\n", tp.x,tp.y,dt[tp.x][tp.y]);
            if(isAvail(tp) && dt[tp.x][tp.y]=='#' && !visit[tp.x][tp.y]){
                tp.depth = t.depth + 1; //又一个t写成p
                q.push(tp);
                visit[tp.x][tp.y] = 1;
                // printf("%d,%d %d\n", tp.x,tp.y,tp.depth);
            }
        }
    }
    // printf("t %d,%d %d\n", t.x,t.y,t.depth);
    return t;
}

int unVisited(){
    for(int i=0;i<cnt;i++){
        if(!visit[grass[i].x][grass[i].y])
            return i;
    }
    return -1;
}

bool isAvail(Point p){
    return (p.x>=0 && p.x<n && p.y>=0 && p.y<m) ? true : false;
}


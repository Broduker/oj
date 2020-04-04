/*
translation:
    给一个n×n的矩阵，老鼠从（1,1）出发，老鼠每次可以走1-k步然后暂停.
    停下的这个位置只能比上一个停留的位置大，并获取其价值，每次只能水平或垂直走，问从（0,0）出发最大能得到的价值

solution:
    正常求解：记忆化搜索dfs
    较麻烦的方法，也可以将矩阵按值从小到大排序(记录位置信息)，然后当作最长上升子序列求解
 
note:
    采用dp求解时有很多容易碰到的坑要注意
    1. 由于规定必须由原点出发，而实际求解的是任意点出发的最大值，所以每个位置对应dp的初始值不能赋值为矩阵值，而是-INF(也不能是0)
       否则，可能造成不能到达的点由于值更大而被当成最终解
    2. ans的值每次要初始化为dt[0][0]，否则如果可走路线只有起始点时最终答案错误输出为0
    3. 同样由于要求从起始点出发，要求比初始点小的值要被忽略
    4. cmp函数中变量不要写错，否则造成排序的错误
    5. memset不知是否可以用来赋值-INF,这题是成功AC的
    6. fill填充二维数组要使用*dp

date:
    2019.08.18
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
struct Hole
{
    int x,y,food;
    Hole(int x_,int y_,int food_):x(x_),y(y_),food(food_){}
    Hole(){}
};
Hole holes[MAXN*MAXN];
int dt[MAXN][MAXN];
int dp[MAXN][MAXN];
int n;

bool isAcess(int t);
bool cmp(Hole h1,Hole h2);
int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    int step;
    int cnt,ans;
    while(cin>>n>>step && ~n && ~step){
        memset(dp,-INF,sizeof(dp));
        // fill(*dp,*dp+MAXN*MAXN,-INF); //注意二维数组的写法略不同
        cnt = 0;
        ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>dt[i][j];
                holes[cnt].x = i;
                holes[cnt].y = j;
                holes[cnt++].food = dt[i][j];
            }
        }
        sort(holes,holes+cnt,cmp);
        for(int t=0;t<cnt;t++){
            int tx = holes[t].x;
            int ty = holes[t].y;
            // dp[tx][ty] = dt[tx][ty];
            if(!tx && !ty){
                ans = dp[tx][ty] = dt[0][0];
                continue;
            }
            if(dt[tx][ty]<dt[0][0])
                continue;
            for(int p=1;p<=step;p++){
                if(isAcess(tx-p) && dt[tx][ty]>dt[tx-p][ty]) dp[tx][ty] = max(dp[tx][ty],dp[tx-p][ty]+dt[tx][ty]);
                if(isAcess(tx+p) && dt[tx][ty]>dt[tx+p][ty]) dp[tx][ty] = max(dp[tx][ty],dp[tx+p][ty]+dt[tx][ty]);
                if(isAcess(ty-p) && dt[tx][ty]>dt[tx][ty-p]) dp[tx][ty] = max(dp[tx][ty],dp[tx][ty-p]+dt[tx][ty]);
                if(isAcess(ty+p) && dt[tx][ty]>dt[tx][ty+p]) dp[tx][ty] = max(dp[tx][ty],dp[tx][ty+p]+dt[tx][ty]);
            }
            ans = max(dp[tx][ty],ans);
            // printf("ans %d tx %d ty %d\n", ans,tx,ty);
        }
        cout<<ans<<endl;
    }
}

bool isAcess(int t){
    return t>=0 && t<n;
}

bool cmp(Hole h1,Hole h2){
    return h1.food < h2.food; //h2打成h1
}

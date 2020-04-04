/*
translation:
    给定一个n*n的字符矩阵，从中选出一个最大的子矩阵（m*m）满足关于斜对角线（左下角到右上角）对称，求出这个矩阵的大小m；

solution:
    dp求解
    我们可以用dp[i][j]表示当前位置(必包含，起始点)到右上角这个子矩阵所能表示对称的矩阵最大值； 
    if(m > dp[i-1][j+1]) dp[i][j] = dp[i-1][j+1]+1
    else dp[i][j] = m
note:
    注意这里数组的定义类型，要用char类型保存字符矩阵，同时输出也要用对应的%c,否则输出错误
    注意这里dp[i][j]含义，应该表示以i,j为子矩阵左下角顶点，所能表示的最大对称矩阵的边长
    这里注意m代表的含义，表示包括i,j在内顺序遍历连续值相同的个数，也就是最小为1
date:
    2019.08.19
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
char dt[MAXN][MAXN];
int dp[MAXN][MAXN];

int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    int ans;
    int n;
    while(~scanf("%d",&n) && n){
        // memset(dp,0,sizeof(dp));
        ans = 0;
        for(int i=0;i<n;i++){
            scanf("%s",dt[i]);
            // printf("%s\n",dt[i]);
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(!i || j==n-1){
                    dp[i][j] = 1;
                }
                int ti = i,tj = j;
                while(ti>=0 && tj<n && dt[ti][j]==dt[i][tj]){
                    // printf("dt[%d][%d] %c\n", ti,j,dt[ti][j]);
                    ti--;
                    tj++;
                }
                int m = i - ti;
                if(m > dp[i-1][j+1]){
                    dp[i][j] = dp[i-1][j+1] + 1;
                }
                else{
                    dp[i][j] = m;
                }
                // printf("m  %d\n",m );
                // printf("dp[%d][%d] %d\n",i,j,dp[i][j] );
                ans = max(ans,dp[i][j]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

bool isPhal(int x,int y,int n){
    for(int i=x;i<x+n;i++){
        for(int j=y;j<y+i;j++){
            if(dt[i][j]!=dt[n-j+x][n-i+y])
                return false;
        }
    }
    return true;
}

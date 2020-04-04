/*
translation:
    假设在接下来的一段时间里，馅饼都掉落在0-10这11个位置。开始时gameboy站在5这个位置，
    因此在第一秒，他只能接到4,5,6这三个位置中其中一个位置上的馅饼。问gameboy最多可能接到多少个馅饼
    每行有两个整数x,T(0<T<100000),表示在第T秒有一个馅饼掉在x点上。同一秒钟在同一点上可能掉下多个馅饼。n=0时输入结束
solution:
    参考题解认为这是类似数塔的dp
    第i秒第j位置的馅饼最大总数为dp[i][j],第i秒第j位置的馅饼数为pan[i][j]
    dp[i][j] = max(dp[i-1][j],max(dp[i-1][j-1],dp[i-1][j+1])) + pan[i][j]; //注意边界横坐标的讨论
note:
    第一道自己设计的dp，纪念一下
    注意每轮dp,pan的值需要初始化
    注意刚开始的起始位置是在5，所以dp[i][j]只有j=4 5 6可以非0,并且考虑ans的初始值要为三个中的最大值，防止循环maxt=1，循环没有进行
    题解的方法是从t=maxt递减遍历(这题遍历顺序没有影响)，最后输出dp[0][5]
    注意数组的范围尽量多开一些，这题开到11好像会WA
date:
    2019.08.07
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e5 + 10;
int pan[MAXN][12];
int dp[MAXN][12];
int main(int argc, char const *argv[])
{
    int n;
    int maxt;
    int ans;
    int x,t;
    while(scanf("%d",&n) && n){
        memset(dp,0,sizeof(dp));
        memset(pan,0,sizeof(pan));
        maxt = 0;
        for(int i=0;i<n;i++){
            scanf("%d %d",&x,&t);
            pan[t][x]++;
            maxt = max(maxt,t);
        }
        dp[1][5] = pan[1][5];
        dp[1][4] = pan[1][4];
        dp[1][6] = pan[1][6];
        ans = max(dp[1][5],max(dp[1][5-1],dp[1][5+1]));
        for(int i=2;i<=maxt;i++){
            for(int j=0;j<=10;j++){
                if(j==0)
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j+1])+pan[i][j];
                else if(j==10)
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j-1])+pan[i][j];
                else dp[i][j] = max(dp[i-1][j],max(dp[i-1][j-1],dp[i-1][j+1])) + pan[i][j];
                if(i==maxt)
                    ans = max(ans,dp[maxt][j]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

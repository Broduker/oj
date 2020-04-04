/*
translation:
    在给定的路线中，从start经过一系列带有数值的棋子(可跳跃甚至一个不经过)到达end，要求经过的棋子数值严格递增，求经过棋子数值和的最大值
solution:
    最长上升子序列
note:
date:
    2019.08.07
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1010;
int seq[MAXN];
int dp[MAXN];
int main(int argc, char const *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    int n,ans;
    while(cin>>n && n){
        ans=0;
        for(int i=0;i<n;i++){
            cin>>seq[i];
        }
        for(int i=0;i<n;i++){
            dp[i]=seq[i];
            for(int j=0;j<i;j++){
                if(seq[j]<seq[i]){
                    dp[i]=max(dp[i],dp[j]+seq[i]);
                }
            }
            ans=max(ans,dp[i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}

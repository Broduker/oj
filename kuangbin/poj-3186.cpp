/*
translation:
    给一行n个数，每次可以取出行首或者行末的数，如果第a[i]是第i次取出的，可以得到a[i]*i的收益，求最大的总收益；

solution:
    区间dp求解
    设dp[i][j] 为 取i到j后 的最大值，可能由d[i+1][j]或者d[i][j-1]转移而来。
    转移方程：dp[i][j]=max(dp[i+1][j]+p[i]*(n+i-j),dp[i][j-1]+p[j]*(n+i-j));  其中n-(j-i)是第几次取
 
note:
    注意题中给的不同范围的含义，数组的最大范围不要开错
    本题dp[i][i]需要初始化，并且值为v[i]*n
    本题为区间dp，循环的顺序不能随意 至少保证每层大循环内部的小循环，区间长度由小至大，外循环随意
    本题注意循环的范围不要越界
date:
    2019.08.17
*/

设dp[i][j] 为 取i到j后 的最大值，可能由d[i+1][j]或者d[i][j-1]转移而来。

转移方程：dp[i][j]=max(dp[i+1][j]+p[i]*(n+i-j),dp[i][j-1]+p[j]*(n+i-j));  其中n-(j-i)是第几次取
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 2010; //最大范围弄错
int dp[MAXN][MAXN],v[MAXN];
int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    // memset(dp,0,sizeof(dp));
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        dp[i][i] = v[i]*n; //没有初始化或者初始化弄错
    }
    for(int k=1;k<n;k++){
        for(int i=1;i+k<=n;i++){ //刚开始范围越界
            dp[i][i+k] = max(dp[i+1][i+k]+v[i]*(n-k),dp[i][i+k-1]+v[i+k]*(n-k));
        }
    }
    cout<<dp[1][n]<<endl;
    return 0;
}

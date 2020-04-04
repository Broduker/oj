/*
translation:
    现在给出空罐子的重量和最满能装到多重，然后给出每种硬币的价值和重量，我们要在不打破它的情况下确认罐子里最少有多少钱。
solution:
    完全背包问题
note:
    注意用一维数组进行操作时，完全背包和01背包的区别
    注意此题要求最小值，因此dp初始化为INF并使dp[0]=0;
date:
    2019.08.07
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
int w[MAXN],v[MAXN];
int dp[MAXN];
int main(int argc, char const *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    int T;
    int n;
    cin>>T;
    int num_a,num_b,num;
    while(T--){
        memset(dp,INF,sizeof(dp));
        dp[0] = 0;
        cin>>num_a>>num_b;
        num = num_b - num_a;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>v[i]>>w[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=w[i];j<=num;j++){
                dp[j] = min(dp[j],dp[j-w[i]]+v[i]);
                // dp[i][j] = max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);
            }
        }
        if(dp[num]==INF){
            printf("This is impossible.\n");
        }
        else{
            printf("The minimum amount of money in the piggy-bank is %d.\n",dp[num]);
        }
    }
    return 0;
}
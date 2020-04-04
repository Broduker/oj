/*
translation:
    给你一个数列，里面有一个元素一定会出现超过（n+1）/2次，输出这个数 
solution:
    第一种办法sort后输出，复杂度O(nlogn)
    第二种线性遍历一次，设置计数器cnt=0，当计数器为0时，令结果赋值为当前遍历到的值，
    此后遇到相同值+1，否则-1，当计数器变为0，重新赋值，只有个数大于1半的值最后计数不会减为0，即为答案
note:
    踩了很多坑
date:
    2019.08.06
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e6+10;
const int INF = 0x3f3f3f3f;
int dp[MAXN];
int pre[MAXN];
int seq[MAXN];
int main(int argc, char const *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    int m,n;
    int ans;
    while(cin>>m>>n){
        memset(dp,0,sizeof(dp));
        memset(pre,0,sizeof(pre));
        ans = -INF;
        for(int i=1;i<=n;i++){
            cin>>seq[i];
        }
        // pre[0] = -INF;
        for(int i=1;i<=m;i++){
            dp[i] = dp[i-1] + seq[i];//和下面的效果相同
            // dp[i] = max(dp[i-1],pre[i-1]) + seq[i];
            if(i==m) ans = dp[m];
            // printf("dp[%d][%d] %d\n",i,i, dp[i]);
            int tmp = -INF;
            pre[i-1] = tmp; //就差这一个语句，导致一直WA 否则dp[i][j]的第一个用到的是dp[i-2][k]的信息
            // tmp = max(pre[i-1],dp[i]);
            for(int j=i+1;j<=n;j++){ //j为i时单独讨论
                dp[j] = max(dp[j-1],pre[j-1])+seq[j];
                pre[j-1] = max(pre[j-2],dp[j-1]);

                // pre[j-1] = tmp;
                // tmp = max(pre[j-1],dp[j]);
                // printf("dp[%d][%d] %d\n",i,j, dp[j]);
                if(i==m){
                    ans = max(ans,dp[j]);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}

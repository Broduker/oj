#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e6+10;
const int INF = 0x3f3f3f3f;
int dp[2][MAXN];
int seq[MAXN];
int main(int argc, char const *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    int m,n;
    int ans;
    while(cin>>m){
        cin>>n;
        memset(dp,0,sizeof(dp));
        ans = -INF;
        for(int i=1;i<=n;i++){
            cin>>seq[i];
            // dp[i&1][i] = dp[i&1^1][i-1] + seq[i];
        }
        for(int i=1;i<=m;i++){
            dp[i&1][i] = dp[i&1^1][i-1] + seq[i];
            if(i==m) ans = dp[m&1][m];
            for(int j=i+1;j<=n;j++){
            // for(int j=i;j<=n;j++){
                dp[i&1][j] = dp[i&1][j-1] + seq[j];
                for(int k=i-1;k<=j-1;k++){
                    // dp[i][j] = max(dp[i][j],dp[i-1][k]+seq[j]);
                    // 这样写是找不到最大值的，后面的一定会覆盖前面的dp[i-1][k]
                    // dp[i][j] = max(dp[i][j-1],dp[i-1][k])+seq[j];
                    dp[i&1][j] = max(dp[i&1][j],dp[i&1^1][k]+seq[j]);
                    // printf("s dp[%d][%d] %d\n", i,j,dp[i&1][j]);

                }
                // printf("dp[%d][%d] %d\n",i,j, dp[i&1][j]);
                if(i==m){
                    ans = max(ans,dp[m&1][j]);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}

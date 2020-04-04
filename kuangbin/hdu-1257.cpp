/*
translation:
    求最长上升子序列

solution:
    经典dp
    dp[i] = max(dp[i],dp[k]) k:1~i-1 && seq[k]<seq[i]
 
note:
    dp[i]初始化为1

date:
    2019.08
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int MAXN = 30010;
int seq[MAXN],dp[MAXN];
using namespace std;
int main(){
    int n,ans;
    while(~scanf("%d",&n) && n){
        ans = 0;
        for(int i=1;i<=n;i++){
            scanf("%d",&seq[i]);
        }
        for(int i=1;i<=n;i++){
            dp[i]=1;
            for(int j=1;j<i;j++){
                if(seq[j]<seq[i]){
                    dp[i] = max(dp[i],dp[j]+1);
                }
            }
            ans=max(ans,dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}

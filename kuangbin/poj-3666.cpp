/*
translation:
    给出长度为n的整数数列,每次可以将一个数增加或减少，代价为变化的差值。
    求将其变成单调增或者单调减(不严格)所需的代价和最小为多少
solution:
    首先要推导出一个结论，每个数最后必然是原序列中的数
    所以可以将原序列排序，去重，枚举每个数变成那个数即可，使用dp求解
    dp[i][j]表示把前i个数变成单调增(不严格)且第i个数变成原来第j大的数的最小代价。
    dp[i][j]=min{dp[i-1][1...j]}+abs(a[i]-b[j]).
 
note:
    1.正常情况下dp的时间复杂度为O(n*m*m)，m为去重后的序列个数，这个会超时
    可以进一步优化，第三层循环改变成用一个变量记录最小值，时间复杂度降为O(n*m)
    2.可以使用滚动数组对空间复杂度进行优化
    3.注意由于dp的书写方便下标从1开始，排序也要注意从1开始排序
    4.注意去重，虽然不影响正确答案
    5.此题数据较水，只需考虑不严格递增情况就可通过
date:
    2019.08.25
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 2010;
const int INF = 0x3f3f3f3f;
int seq[MAXN],sortSeq[MAXN];
int dp[MAXN][MAXN];
int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    // memset(dp,0,sizeof(dp));
    int n;
    int ans = INF;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>seq[i];
        sortSeq[i] = seq[i];
    }
    sort(sortSeq+1,sortSeq+n+1); //忘记排序是从1开始
    for(int i=1;i<=n;i++){
        int minK = INF;
        for(int j=1;j<=n;j++){
            dp[i][j] = INF;
            minK = min(minK,dp[i-1][j]);
            dp[i][j] = min(dp[i][j],minK+abs(seq[i]-sortSeq[j]));
            // for(int k=1;k<=j;k++){
                // dp[i][j] = min(dp[i][j],dp[i-1][k] + abs(seq[i]-sortSeq[j]));
            // }
            if(i==n){
                ans = min(ans,dp[n][j]);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}

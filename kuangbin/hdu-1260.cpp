/*
translation:
    题意就是有n个人排队买票，每个人需要的时间是a[i] (1=< i <=N)，
    但是现在可以两个人合买， 合买只能和前面一个人或者后面一个人合买，
    所用时间已知，求n个人都买完票所需要的时间；

solution:
    dp求解
    dp[i]表示前i个人购买的最低价格，则有dp[i] = min(dp[i-2]+doublePrice[i-1],dp[i-1]+singlePrice[i]);
    doublePrice[i]为双人的购买价格，singlePrice[i]的购买价格，注意doublePrice的下标含义有所不同
note:
    混用cout printf,同时关闭缓冲cin.sync_with_stdio(false);导致输出一直错误
    dp[1]记得初始化为singlePrince[1] 从i=2开始遍历
    注意时间转换小时是12/24进制，同时应该超过12:00:00都算pm,这题数据没有涉及到该项争议
date:
    2019.08.08
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 2010;
int dp[MAXN],singlePrice[MAXN],doublePrice[MAXN];

void DatePrint(int st_h,int st_m,int st_s,int ds);
int main(int argc, char const *argv[])
{
    // cin.tie(0);
    // cin.sync_with_stdio(false);
    int T,n;
    cin>>T;
    while(T--){
        memset(dp,0,sizeof(dp));
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>singlePrice[i];
        }
        for(int i=1;i<=n-1;i++){
            cin>>doublePrice[i];
        }
        dp[1] = singlePrice[1];
        for(int i=2;i<=n;i++){
            dp[i] = min(dp[i-2]+doublePrice[i-1],dp[i-1]+singlePrice[i]);
        }
        DatePrint(8,0,0,dp[n]);

    }
    return 0;
}

void DatePrint(int st_h,int st_m,int st_s,int ds){
    int s = (st_s + ds%60) % 60;
    // int m = (st_m + ds/60) % 60;
    int m = (st_m + ds%3600) / 60;
    int dh = ds/3600 ;
    int h = (st_h+dh)%12;
    string flg;
    flg = (st_h+dh)%24 > 12 ? "pm" : "am";
    printf("%02d:%02d:%02d ",h,m,s );
    cout<<flg<<endl;
    // if(h>12)
    //     printf("%02d:%02d:%02d pm\n", h-12, m, s);
    // else
    //     printf("%02d:%02d:%02d am\n", h, m, s);
}

/*
translation:
    给出老鼠的体重和速度
    求最长的序列，使得体重递增，速度递减
solution:
    dp求解最长上升子序列
    首先根据体重按递增顺序对老鼠的序列进行排序，然后根据最长上升子序列进行求解
note:
    注意要输出原始老鼠对应的序列，排序后序号已变，需要在结构体中进行保存，输出的也必须为原始的序列号
    注意由于要求体重严格递增，速度严格递减，所以排序后的dp过程中仍要判断体重是否严格递
date:
    2019.08.09
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN = 1010;
struct Mouse
{
    int w,s,i;
}seq[MAXN];
int dp[MAXN],pre[MAXN];

bool cmp(Mouse m1,Mouse m2);
void printAns(int s);
int main(int argc, char const *argv[])
{
    int cnt = 1;
    int ans = 0,fi=0;
    memset(pre,-1,sizeof(pre));
    while(~scanf("%d %d",&seq[cnt].w,&seq[cnt].s)){
        seq[cnt].i = cnt;
        cnt++;
    }
    sort(seq,seq+cnt,cmp);
    for(int i=1;i<cnt;i++){
        dp[i] = 1;
        for(int j=1;j<i;j++){
            if(seq[j].s > seq[i].s && seq[j].w < seq[i].w && dp[i] < dp[j]+1){
                dp[i] = dp[j] + 1;
                pre[seq[i].i] = seq[j].i;
            }
        }
        if(dp[i]>ans){
            ans = dp[i];
            fi = seq[i].i;
        }
    }
    printf("%d\n", ans);
    printAns(fi);
    return 0;
}
bool cmp(Mouse m1,Mouse m2){
    return m1.w < m2.w;
}
void printAns(int s){
    if(~s){
        printAns(pre[s]);
        printf("%d\n",s);
    }
}

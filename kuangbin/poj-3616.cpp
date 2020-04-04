/*
translation:
    一头奶牛为n小时内的产奶做规划，共有m个时间段，每个时间段用三个字母表示，
    s：该时段开始时间，d：该时段结束时间，p：该时间段产奶量。(时间段可重叠)
    并且每次产完奶之后需要休息r小时休息才能进行下一次产奶。问最大产奶量是多少？

solution:
    dp求解 是最长上升子序列变形的题目
    先按工作的结束时间(开始时间也行)从小到大排序，再动态规划。
    dp[i]表示从头开始取到第i段所获得的最大值。
    dp[i] 更新条件：子序列中前一个元素的结束时间+休息时间 < 下一个元素的开始时间。然后仿照最长递增子序列的写法就可以了。

note:
    注意这题与最长上升子序列的相似之处，dp更新公式本质上是相同的
    注意题目中虽然先说时间用0~n-1标记，实际上后面是1~n，所以不需要加上溢出n-1的判断
    本题按照结束时间或者开始时间排序都能得到正解，因为正解中先进行的事件的结束时间和开始时间都应位于后进行的事件之前
date:
    2019.08.19
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXM = 1010;
struct Milk
{
    int start,end,efnt;
};
Milk milks[MAXM];
int dp[MAXM];


bool cmp(Milk m1, Milk m2);
int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    int n,m,r;
    int cnt = 0;
    int ans = 0;
    scanf("%d %d %d",&n,&m,&r);
    for(int i=0;i<m;i++){
        scanf("%d %d %d",&milks[cnt].start,&milks[cnt].end,&milks[cnt].efnt);
        cnt++;
    }
    sort(milks,milks+cnt,cmp);
    for(int i=0;i<m;i++){
        // if(milks[i].end<n){
            dp[i] = milks[i].efnt;
            for(int j=0;j<i;j++){
                if(milks[j].end+r<=milks[i].start){
                    dp[i] = max(dp[i],dp[j]+milks[i].efnt);
                }
            }
            ans = max(ans,dp[i]);
        // }
    }
    printf("%d\n", ans);
}

bool cmp(Milk m1, Milk m2){
    return m1.start < m2.start;
    // return m1.end < m2.end;
}

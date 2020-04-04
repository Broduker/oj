/*
translation:
    有n门课，每门课都要交作业，作业有时间花费和最晚提交日期，如果超过日期交作业，每超过一天就要扣一分，问最少扣多少分并且给出最少扣分的方案。
solution:
    本题使用状态压缩dp
    因为最多只有15门课程，可以使用二进制来表示所有完成的状况,记为s
    例如5，二进制位101，代表第一门和第三门完成了，第二门没有完成，那么我们可以枚举0~(1<<n)-1便可以得出所有的状态
    然后对于每一门而言，其状态是t = 1<<i，我们看这门在现在的状态s下是不是完成，可以通过判断s&t是否为1来得到这门课是否完成。
    我们可以枚举j 从 0~n-1 来枚举s状态的上一状态。即 s-(1<<j) 。比如11111-1=11110，11111-1<<1=11101
    可得公式dp[i] = min(dp[i],dp[i-(1<<j)]+score), score = max(0,cost[j] - ddl[j])
    
note:
    变量类型不要定义错，如string定义成int，不同数组范围不要定义错，比如MAXN和MAXBITN弄混
    注意本题循环的变化范围状态i 0~1<<n(0可以跳过) 作业j 0~1<<n-1
    注意1<<n和别的计算符号放一起时一定要加括号，否则优先级容易出问题
    注意数组初始化的值的区别
    注意值进行更新时下标不要弄错 比如cost[j]写成cost[i]
    注意存在多个最优解时，按字典序输出，由于二进制中字典序小的在高位，所以要么倒序枚举作业j，要么判断条件改成<=，允许字典序小的覆盖字典序大的
    输出函数注意cout<<courses[pre[t]]<<endl;//不要放在条件语句之外 否则会多输出courses[-1]
    注意string不能用printf输出
date:
    2019.08.07
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 20;
const int MAXBITN = (1<<15) +10;
string courses[MAXN]; //原先定义为int
int ddl[MAXN],cost[MAXN];
int pre[MAXBITN],dp[MAXBITN],time[MAXBITN]; //time[MAXBITN]写成time[MAXN]
void PrintAns(int t);
int main(){
    int T;
    int n;
    cin>>T;
    while(T--){
        memset(pre,-1,sizeof(pre));
        memset(dp,INF,sizeof(dp));
        memset(time,0,sizeof(time));
        dp[0] = 0;
        // cout<<dp[0]<<" "<<dp[1]<<endl;
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>courses[i]>>ddl[i]>>cost[i];
            // dp[1<<i] = max(0,cost[i]-ddl[i]);
        }
        int bitn = 1<<n;
        for(int i=1;i<bitn;i++){
            for(int j=0;j<n;j++){
            // for(int j=n-1;j>=0;j--){
                int t = 1<<j;
                if(i&t){
                    int score = max(0,time[i-t] + cost[j] - ddl[j]);
                    if(dp[i-t]+score<=dp[i]){
                        dp[i] = dp[i-t]+score;
                        time[i] = time[i-t]+cost[j]; //cost[j]写成cost[i]
                        pre[i] = j;
                        // printf("i=%d,dp=%d pre=%d\n",i,dp[i],pre[i]);
                    }
                }
            }
        }
        printf("%d\n",dp[(1<<n)-1]);
        PrintAns((1<<n)-1); //没加括号
    }
}
void PrintAns(int t){
    // printf("%d pre %d\n",t, pre[t]);
    if(~pre[t]){
        PrintAns(t-(1<<pre[t]));
        cout<<courses[pre[t]]<<endl;//不要放在条件语句之外
    }
}

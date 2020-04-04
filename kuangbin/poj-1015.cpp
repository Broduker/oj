/*
translation:
    陪审团从公众中挑选的。先随机挑选n个人作为陪审团的候选人，然后再从这n个人中选m人组成陪审团。
    选m人的办法是：控方和辩方会根据对候选人的喜欢程度，给所有候选人打分，分值从0到20。
    法官选出陪审团的原则是：选出的m个人，必须满足辩方总分D和控方总分P的差的绝对值|D-P|最小。
    如果有多种选择方案的|D-P| 值相同，那么选辩控双方总分之和D+P最大的方案即可。

output：
    选取符合条件的最优m个候选人后，要求输出这m个人的辩方总值D和控方总值P，并升序输出他们的编号。
    每个数字前需要有空格，每个样例间需要有空行，

solution:
    dp求解
    第i个候选人的辩方总分和控方总分之差记为diff(i)，辩方总分和控方总分之和记为sum(i)。
    dp(j, k)表示取j个候选人，使其辩控差为k的所有方案中，辩控和最大的那个方案的*辩控和*。
    并且如果没法选j 个人，使其辩控差为k，那么dp(j, k)的值就为-1。
    显然，方案dp(j, k)是由某个可行的方案dp(j-1, x)( -20×m ≤ x ≤ 20×m)演化而来的。

    若存在某个候选人i，i 在方案dp(j-1, k-diff[i])中没有被选上.且在所有满足该必要条件的dp(j-1, k-diff[i])中，
    选出 dp(j-1, x) + S(i) 的值最大的那个，那么方案dp(j-1, k-diff[i])再加上候选人i，就演变成了方案 dp(j, k)。
    不妨将方案dp(j, k)中最后选的那个候选人的编号，记在二维数组的元素path[j][k]中。
    那么方案dp(j, k)的倒数第二个人选的编号，就是path[j-1][k-diff[path[j][k]]]。
    假定最后算出了解方案的辩控差是k，那么从path[m][k]出发，就能回溯求出所有被选中的候选人。
    初始条件，只能确定dp(0, 0) = 0，其他均为-1。
    由于题目中辩控差的值k 可以为负数，而程序中数组下标不能为负数，所以，在程序中不妨将辩控差的值都加上修正值fix=400(20*40)，以免下标为负数导致出错。
    此时初始条件修正为dp(0, fix) = 0，其他均为-1。
    DP后，从第m行的dp(m, fix)开始往两边搜索最小|D-P| 即可，第一个不为dp[m][k]!=-1的位置k就是最小|D-P|的所在。
    最后就是求m个人的D和P，由于D+P = dp(m, |D-P| ) ，|D-P|已知。
    那么D= ( (D+P) + (D-P) ) / 2  ,  P=( (D+P) - (D-P)  / 2
    计算D和P时注意修正值fix
 
note:
    输出case标号的初始化赋值要放到循环外面，否则每个样例标号都为1
    要求样例间要输出空行，每个样例数字前要有空格，指定语句末尾不要有多余空格
    dp的三层循环限制变量不要弄错，最外层为m，中间层只需2*fix，最内层为n
    复制粘贴注意修改，赋值语句不要弄成大于小于的判断语句
    注意数组的初始化
    注意语句判断，非0即为1，即使为-1
    最后的输出d、p的求解公式不要弄错弄反
    注意同时修改两个变量，注意不要修改为新值后又需要使用旧值
    visit函数返回值不要弄反
    注意这里下标值的含义
date:
    2019.08.16
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXM = 25;
const int MAXN = 210;
int sum[MAXN],diff[MAXN],d[MAXN],p[MAXN];
int dp[MAXN][810],path[MAXN][810];
int sortPath[MAXM];
void PrintAns(int i,int j);
bool visit(int i,int j,int t);

int main(int argc, char const *argv[])
{
    int n,m;
    int kase = 0; // 之前放循环中导致每次都为1
    while(scanf("%d %d",&n,&m) && n && m){
        memset(path,-1,sizeof(path));
        memset(dp,-1,sizeof(dp));

        int fix = m*20;
        dp[0][fix] = 0;
        for(int i=1;i<=n;i++){
            scanf("%d %d",&d[i],&p[i]);
            sum[i] = d[i] + p[i];
            diff[i] = d[i] - p[i];
        }
        for(int i=1;i<=m;i++){ //和内层循环变量限制弄错
            for(int j=0;j<=2*fix;j++){ //不需要为800
                if(dp[i-1][j]>=0){
                    for(int k=1;k<=n;k++){
                        if(!visit(i-1,j,k) && dp[i][j+diff[k]]<dp[i-1][j]+sum[k]){
                            dp[i][j+diff[k]] = dp[i-1][j]+sum[k]; //赋值写成小于号
                            path[i][j+diff[k]] = k;
                            // printf("i %d j+... %d dp %d path %d\n", i,j+diff[k],path[i][j+diff[k]]);
                        }
                    }
                }
            }
        }
        int s;
        for(s=0;s<=fix;s++){
            if(dp[m][fix+s]>=0 || dp[m][fix-s]>=0){ //非0即为1，另外这里值为0也是有效的
                // printf("dp[%d][%d+%d] %d\n",m,fix,s, dp[m][fix-s]);
                break;
            }
        }
        s = dp[m][fix+s] > dp[m][fix-s] ? s : -s;
        int pro = (dp[m][fix+s]+s)/2; //两个公式弄反
        int defc = (dp[m][fix+s]-s)/2;
        printf("Jury #%d\n", ++kase);
        // printf("fix %d s %d\n",fix, s);
        printf("Best jury has value %d for prosecution and value %d for defence:\n",pro,defc); //刚开始输出末尾有空格
        PrintAns(m,s+fix);
        printf("\n"); //每次输出需要空行
    }
    return 0;

}

void PrintAns(int i,int j){
    int k = 0;
    while(i){
        sortPath[k++] = path[i][j];
        j -= diff[path[i][j]];
        i--;
    }
    sort(sortPath,sortPath+k);
    for(int t=0;t<k;t++){
        printf(" %d", sortPath[t]);
    }
    printf("\n");
}

bool visit(int i,int j,int t){
    while(i && path[i][j]!=t){
        j -= diff[path[i][j]];
        i--;
    }
    return i ? true : false;
}

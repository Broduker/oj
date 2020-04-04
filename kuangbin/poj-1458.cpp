/*
translation:
    给出两个字符串，求出这样的一个最长的公共子序列的长度：
    子序列中的每个字符都能在两个原串中找到，而且每个字符的先后顺序和原串中的先后顺序一致。
    输入有若干行，每行是两个字符串。对每一行输入的两个字符串，输出最长公共子串的长度。

solution:
    dp求解
    标准的最长公共子序列dp问题
    if(s1[i]==s2[j]) dp[i][j] = dp[i-1][j-1] + 1;
    else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
 
note:
    这题没有给范围，数组空间尽量开大些
    由于数组过大全部初始化可能过慢，可以只给dp[0][k]和dp[k][0]初始化
date:
    2019.08.16
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e3 + 10;
int dp[MAXN][MAXN];
int main(int argc, char const *argv[])
{
    string s1,s2;
    int len1,len2;
    while(cin>>s1>>s2){
        s1 = '\0' + s1;
        s2 = '\0' + s2;
        memset(dp,0,sizeof(dp));
        len1 = s1.length();
        len2 = s2.length();
        for(int i=1;i<len1;i++){
            for(int j=1;j<len2;j++){
                if(s1[i]==s2[j]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else{
                    dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                }

            }
        }
        printf("%d\n", dp[len1-1][len2-1]);
    }
    return 0;
}

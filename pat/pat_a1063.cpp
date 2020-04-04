/*
translation:
    给定n组序列，给定k个查询，每个查询输出其中两组序列交集/(并集-交集)的值，xx.x%格式输出
    input:
        第一行:序列个数n(n<=50)
        后n行: m s_1 s_2 ... s_m m代表序列的个数(m<=10^4) 后面跟着每个序列第i位的值
        第n+2行: k 代表查询数k(k<=2000)
        后k行: a b 代表要查询的两个序列的编号
        
solution:
    每个序列的可能包含多个相同的值，统计时要去除，可使用set保存
    对于每个查询，遍历其中一个序列，查找另一个序列是否存在对应的值，记录公共值个数
    common/(sum(a,b)-common)即为最终结果
    
note:
    1.一个序列可能包含多个重复的值
    2.查询给定的序号是从1开始的
date:
    2019.11.30
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
const int MAXN = 60;
set<int> seq[MAXN];
void cal(int s1,int s2);
int main(int argc, char const *argv[])
{
    int n,m;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&m);
        for(int j=0;j<m;j++){
            int t;
            scanf("%d",&t);
            seq[i].insert(t);
        }
    }
    int k;
    scanf("%d",&k);
    for(int i=0;i<k;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        cal(a-1,b-1);
    }
    return 0;
}

void cal(int s1,int s2){
    int com = 0;
     for(auto i = seq[s1].begin();i!=seq[s1].end();i++){
        if(seq[s2].find(*i)!=seq[s2].end()){
            com++;
        }
    }
    printf("%.1f%%\n",100*com*1.0/(seq[s1].size()+seq[s2].size()-com) );
}

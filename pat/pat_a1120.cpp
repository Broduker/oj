/*
translation:
    给定n个数字，每个数字各个位的和称为该数字的friend id，输出给定数字的所有friend id数目，并按升序输出具体值
    input:
        第一行:数字个数n
        第二行: 具体的n个数字的值
        
solution:
    对每个数字计算对应的friend id，保存到set中，会自动去重和排序，最后输出结果
    
note:
    注意输出friend id的总个数
date:
    2019.11.30
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
const int MAXN = 1e4+10;
set<int> id;

int cal(int t);
int main(int argc, char const *argv[])
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int t;
        scanf("%d",&t);
        id.insert(cal(t));
    }
    printf("%d\n",id.size() );
    int cnt = 0;
    for(auto it=id.begin();it!=id.end();it++,cnt++){
        if(cnt) printf(" ");
        printf("%d",*it );
    }
    return 0;
}

int cal(int t){
    int sum = 0;
    while(t){
        sum += t%10;
        t /= 10;
    }
    return sum;
}


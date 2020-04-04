/*
translation:
    给你两个四位的素数a，b。
    a可以改变某一位上的数字变成c，但只有当c也是四位的素数时才能进行这种改变。
    请你计算a最少经过多少次上述变换才能变成b。

solution:
    bfs求解
    对每一位的其余9个值的情况都进行讨论，满足是质数且未访问就压入队列，注意排除首位为0的情况
    当与目标值相等，数字遍历对应的深度即为答案，否则无解
 
note:
    1.这题又是在使用queue头元素t时错用成输入参数st
    2.注意每个样例visit初始化
    3.注意这题素数的范围是10000而不是1000
    4.了解线性筛的写法和原理
date:
    2019.08.29
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
struct Number
{
    int val,depth;
    Number(int v,int d=0):val(v),depth(d){}
    Number():depth(0){}
};
const int MAXN = 10010;
int ten[] = {1,10,100,1000};
int prime[MAXN];
int visit[MAXN];
bool number[MAXN];

void isPrime();
int bfs(int st,int ed);
int main(){
    int T;
    int a,b;
    int ans;
    isPrime();
    scanf("%d",&T);
    while(T--){
        memset(visit,0,sizeof(visit));
        scanf("%d %d",&a,&b);
        ans = bfs(a,b);
        if(~ans){
            printf("%d\n", ans);
        }
        else printf("Impossible\n");
    }
}

int bfs(int st,int ed){
    queue<Number> q;
    Number t;
    q.push(Number(st));
    visit[st] = 1;
    while(!q.empty()){

        t = q.front();
        q.pop();
        // printf("top %d\n", t.val);
        if(t.val==ed){
            return t.depth;
        }
        Number tp;
        for(int i=0;i<4;i++){
            int temp = t.val/ten[i] % 10; //t.val用成st
            // printf("temp %d\n",temp);
            for(int j=0;j<10;j++){
                if(j==temp || (!j&&i==3)){
                    continue;
                }
                int dt = t.val + (j - temp)*ten[i]; //t.val用成st
                // if(number[dt])
                    // printf("%d\n", dt);
                if(number[dt] && !visit[dt]){
                    Number tp(dt,t.depth+1);
                    q.push(tp);
                    visit[dt] = 1;
                }
            }
        }
    }
    return -1;
}

// prime[]数组中的素数是递增的,当i能整除prime[j]，那么i*prime[j+1]这个合数肯定被prime[j]乘以某个数筛掉。
// 因为i中含有prime[j],prime[j]比prime[j+1]小，即i=k*prime[j]，那么i*prime[j+1]=(k*prime[j])*prime
// [j+1]=k’*prime[j]，接下去的素数同理。所以不用筛下去了。因此，在满足i%prime[j]==0这个条件之前以及第一次
// 满足改条件时,prime[j]必定是prime[j]*i的最小因子。

void isPrime()
{
    int cnt=0;
    memset(number,true,sizeof(number));
    for(int i=2;i<=MAXN;i++)
    {
        if(number[i])
            prime[cnt++] = i;
        for(int j=0; j<cnt && prime[j]*i<=MAXN; j++)
        {
            number[prime[j]*i] = false;
            if(i%prime[j]==0) //保证每个合数只会被它的最小质因数筛去，因此每个数只会被标记一次
                break;
        }
    }
}

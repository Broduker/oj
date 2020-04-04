/*
translation:
    在给定的N个整数A1, A2...AN中选出两个进行xor（异或）运算，得到的结果最大是多少？
    input:
        第一行输入一个整数N。
        第二行输入NN个整数A1～ANA1～AN。

    数据范围
    1≤N≤10^5
    0≤Ai<2^31

solution:
    将整数转化为31位二进制字符串，用trie进行存储
    每一次检索时,都优先向与当前Ai这一位相反的位置走,
    如果说没有路可以走的话,那么就走相同的路,以此使Xor值最大
note:
    1.注意trie的节点范围不能是(2^32)-1 会超过数组最大范围 而应是MAXN*32
    2.注意不要把int型变量错定义为bool型
    3.注意c++中^符号代表异或而非幂运算
    4.注意<<和+-的优先级不要弄错，最好加括号
    5.注意循环范围不要设置错
date:
    2020.03.17
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 1e5+10;
const int MAXM = MAXN*32; //注意本题变量范围
int num[MAXN];
int bin[MAXN][31];
bool tail[MAXM];
int trie[MAXM][2]; //错定义为bool类型
int cnt = 1;
void insert(int t[]){
    // printf("test %d\n",trie[36][0]);
    int p = 1;
    for(int i=0;i<31;i++){
        int c = t[i];
        // printf("c %d\n",c);
        if(!trie[p][c]){
            // printf("Yes\n");
            trie[p][c] = ++cnt;
            // printf("insert %d %d %d\n", p,c,cnt);
            // cnt++;
        }
        // printf("add %d %d %d\n",trie[p][c],p,c);
        p = trie[p][c];
    }
    tail[p] = true;
}

int search(int t[]){
    int p = 1,ans = 0;
    for(int i=0;i<31;i++){

        int c = t[i]^1;
        if(!trie[p][c]){
            // printf("xxxx\n");
            c ^= 1;
        }
        // printf("trie %d %d %d\n",i,p,c);
        ans = ans + (c<<(31-i-1)); //<<和+的优先级要注意
        // printf("an %d\n",ans);
        p = trie[p][c];
    }
    // printf("ans %d\n",  ans);
    return ans;
}


void toBinary(int t,int idx){
    // int b[31] = {0};
    int n = 31;
    while(t && n){
        bin[idx][n-1] = t%2;
        t = t >> 1;
        // printf("bin %d\n",  bin[idx][n-1]);
        n--;
    }
    // return b;
}

int main(int argc, char const *argv[])
{
    // printf("size %d\n",sizeof(int));
    memset(trie,0,sizeof(trie));
    memset(bin,0,sizeof(bin));
    memset(tail,false,sizeof(tail));
    int n;
    int maxt = 0;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&num[i]);
    }
    toBinary(num[0],0);
    insert(bin[0]);
    for(int i=1;i<n;i++){
        toBinary(num[i],i);
        maxt = max(num[i]^search(bin[i]),maxt);
        insert(bin[i]);
    }
    printf("%d\n", maxt);
    return 0;
}

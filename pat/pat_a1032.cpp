/*
translation:
    给定两个由链表存储的单词，求两个单词公共后缀的头节点对应的地址
    若无公共后缀输出-1
    input:
        第一行:addr1,addr2,n 分别代表两个链表的首地址，以及节点的总个数(n<10^5)
        后n行:addr,alpha,next 分别代表节点的位置，字母，下一节点的位置
        
solution:
    遍历第一个链表，将遍历过的节点打上标记
    遍历第二个链表，当出现的第一个已打上标记的节点即为公共后缀的首地址
    否则输出-1
note:
    1.如果采用取巧方式，使用hash统计next对应id出现的次数，输出次数大于1的id是不行的
      一是有个测试点答案是头节点，这并不出现在next中
      二是实际还有一个测试点拥有不止一个次数>2的节点，导致输出的并不一定是第一个
    2.第二次遍历链表时循环条件是while(!visit[k] && ~[k])而非while(!visit[k] && ~addr[k])
      差别在于要考虑头节点是答案的情况
    3.保存最终结果的变量不要用错成中间其他临时变量
    4.注意-1直接输出，其他情况为%05d形式
    5.该注释掉的部分注意要注释掉
date:
    2019.11.28
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e5+10;
int addr[MAXN]={0};
int visit[MAXN]={0};
int main(int argc, char const *argv[])
{
    memset(addr,0,sizeof(addr));
    memset(visit,0,sizeof(visit));
    int st1,st2,n;
    int ans = -1; //可能没后缀
    scanf("%d %d %d",&st1,&st2,&n);
    int ad,id;
    char ch;
    int k;
    for(int i=0;i<n;i++){
        scanf("%d %c %d",&ad,&ch,&id);
        addr[ad] = id;
        /*
        if(~id)
            addr[id]++;
        if(addr[id]>1){
            ans = id;
            // printf("ans %05d %c %05d\n",ad,ch,id); //不要忘记注释
        }
        */
    }
    k = st1;
    while(~addr[k]){
        visit[k] = 1;
        k = addr[k];
    }
    k = st2;
    while(!visit[k] && ~k){
    // while(~addr[k]){
    //     if(visit[k]){
    //         printf("%05d\n",k);
    //         return 0;
    //     }
        visit[k] = 1; // 不加陷入死循环
        k = addr[k];
    }
    // printf("-1\n");
    if(visit[k]) //写成~addr[k]
        printf("%05d\n",k );
    else printf("-1\n");
    // if(~ans)
    //     printf("%05d\n",ans); //写成id了
    // else printf("-1\n"); //注意回车
    return 0;
}

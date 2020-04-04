/*
translation:
    给定一个链表，求将链表排序后的结果，按链表顺序输出结果
    input:
        第一行:节点个数n(n<10^5) 头地址head 地址由五位数字组成
        后n行:addr,val,next 分别为节点地址，对应值(val∈(-10^5,10^5)) 下一节点地址 若无则为-1
    output:
        第一行:链表长度n，排序后的头地址head
        后n行:与输入格式相同
        
solution:
    通过结构体存储链表节点，依照val值排序，按照保存的addr值依此输出结果
note:
    1.给出来的节点不一定都在链表上，所以需要在结构体中加入标志位
      之后遍历一遍标记有效的节点并统计个数
    2.更重要的是可能整个链表没有节点，所以这个时候需要特判输出
    3.注意由于需要按链表顺序遍历 保存节点的时候不能顺序保存，要以地址作hash
    4.由于是hash存储，排序的节点个数不是总结点数或有效节点数，而要全部排序maxn
    5.加入标志位的比较函数写法参考: return n1.flag!=n2.flag ? n1.flag : n1.val<n2.val;
    6.输入参数不要缺

date:
    2019.11.28
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN = 1e5+10;
int cnt = 0;
struct Node
{
    int addr,val,next;
    bool flag = false;
}node[MAXN];
// int cnt = 0;
bool cmp(Node n1,Node n2){
    return n1.flag!=n2.flag ? n1.flag : n1.val<n2.val;
}
int main(int argc, char const *argv[])
{
    int n,head;
    scanf("%d %d",&n,&head); //输入参数不要缺
    for(int i=0;i<n;i++){
        int adr;
        scanf("%d",&adr);
        node[adr].addr = adr;
        scanf("%d %d",&node[adr].val,&node[adr].next);
    }

    for(int i=head;~i;i=node[i].next){
        node[i].flag = true;
        cnt++;
        // printf("cnt %d\n",cnt );
    }
    if(!cnt){
        printf("0 -1\n");
    }
    else{

        sort(node,node+MAXN,cmp); //范围不能是n，因为下标代表地址，不连续
        head = node[0].addr;
        printf("%d %05d\n",cnt,head);
        for(int i=0;i<cnt;i++){
            printf("%05d %d ",node[i].addr,node[i].val);
            if(i<cnt-1)
                printf("%05d\n",node[i+1].addr);
            else printf("-1\n");
        }
    }
    return 0;
}

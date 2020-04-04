/*
translation:
    给定一个链表，将链表每k个位置为一段进行反转，最后一段不足k则保持不变，输出处理后的链表
    input:
        第一行:头地址head 地址由五位数字组成 节点个数n(n<10^5) 间隔k
        后n行:addr,val,next 分别为节点地址，对应值(val∈(-10^5,10^5)) 下一节点地址 若无则为-1
    output:
        处理后的链表，形式与输入相同
        
solution:
    借助静态链表，在遍历链表时将链表存储或转化为数组形式，然后每隔k个对数组元素进行反转操作
    可使用reverse函数实现，参数类似sort，最后输出结果
note:
    1.输入数据的可能包含无效节点，需要进行遍历统计
    2.转为数组形式既可以再遍历时桉顺序复制节点到数组中
      也可以在node中定义变量记录节点的位置，在遍历时赋值，然后按节点位置排序即可
    3.如果使用排序注意要对所有元素进行排序，因为存在无效节点
    4.注意输出考虑%05d形式

date:
    2019.11.29
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN = 1e5+10;
struct Node
{
    int addr,val,next;
};
Node node[MAXN],nodelist[MAXN];
int cnt = 0;
int main(int argc, char const *argv[])
{
    int n,head,d;
    scanf("%d %d %d",&head,&n,&d);
    int adr;
    for(int i=0;i<n;i++){
        scanf("%d",&adr);
        node[adr].addr = adr;
        scanf("%d %d",&node[adr].val,&node[adr].next);
    }
    for(int i = head;~i;i=node[i].next){
        memcpy(nodelist+cnt,node+i,sizeof(Node));
        cnt++;
    }
    for(int i=0;i<cnt;i++){
        if((i+1)%d==0){
            reverse(nodelist+i-d+1,nodelist+i+1);
        }
    }
    for(int i=0;i<cnt;i++){
        printf("%05d %d ",nodelist[i].addr,nodelist[i].val );
        if(i<cnt-1)
            printf("%05d\n",nodelist[i+1].addr );
        else printf("-1\n");
    }
    return 0;
}

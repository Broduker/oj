/*
translation:
    经典的LCA问题，即求两个节点的最小公共祖先

solution:
    上网查阅主要有四种解法：
    1.暴力法，这里采用记录每个节点的父亲节点，
      首先对两个节点中深度较高的不断递归找父亲节点，直至深度相同，如果值相同，则其中一个节点即为答案，
      否则同时向上继续寻找父亲节点，直到对应的值相同，即为答案
    2.离线算法 Tarjan
    3.倍增算法
    4.ST算法求解RMQ
note:
    1.节点的值是任意的，并不是按序号排列，甚至可能是负数，所以需要建立一个映射关系
    2.输入函数参数不要写错写漏
    3.不要忘了初始化根节点的深度值
    4.递归函数传递的起始位置终止位置不要弄错
    5.注意要在每层标注该层节点对应的父节点，而不是将节点的孩子标住父节点，
      因为这样会在最底层多标注一层，造成构建的树的结构错误
date:
    2019.11.26
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int MAXN = 1e4+10;
map<int,int> mp,rev;
struct Node
{
    int father,depth;
    // int child[2];
}nodes[MAXN];
int inorder[MAXN],preorder[MAXN];

void creatTree(int st,int end,int ft,int last);
int findFather(int s1,int s2);
int main(int argc, char const *argv[])
{
    int T,n;
    scanf("%d %d",&T,&n);//少写一个%d
    int ori;
    for(int i=0;i<n;i++){
        scanf("%d",&ori);
        mp[ori] = i;
        rev[i] = ori;
        inorder[i] = i;
    }
    for(int i=0;i<n;i++){
        scanf("%d",&ori);
        preorder[i] = mp[ori];
    }
    nodes[preorder[0]].depth = 0; //没加
    // printf("input over\n");
    creatTree(0,n-1,0,-1);
    // printf("creat tree over\n");
    int a,b;
    while(T--){
        int flag = 0;
        scanf("%d %d",&a,&b);
        // if(a>n || a<1) flag=2;
        if(mp.find(a)==mp.end()) flag=2;
        // if(b>n || b<1) flag++;
        if(mp.find(b)==mp.end()) flag++;
        if(!flag){
            int state = findFather(mp[a],mp[b]);
            switch(state){
                case -1:printf("%d is an ancestor of %d.\n",a,b );break;
                case -2:printf("%d is an ancestor of %d.\n",b,a );break;
                default:printf("LCA of %d and %d is %d.\n",a,b,rev[state] );//注意不是直接输出state
            }
        }
        else{
            switch(flag){
                case 1:printf("ERROR: %d is not found.\n",b );break;
                case 2:printf("ERROR: %d is not found.\n",a );break;
                case 3:printf("ERROR: %d and %d are not found.\n",a,b );break;
                default:break;
            }
        }
    }
    return 0;
}
void creatTree(int st,int end,int ft,int last){//中序遍历的起始和终止位置，前序遍历的父节点位置
    if(st>end) return;
    if(~last){
        nodes[preorder[ft]].father = preorder[last];
        nodes[preorder[ft]].depth = nodes[preorder[last]].depth+1;

    }
    int mid;
    for(int i=st;i<=end;i++){
        if(inorder[i]==preorder[ft]){
            mid = i;
            break;
        }
    }
    // nodes[preorder[ft]].child[0] = preorder[ft+1];
    // nodes[preorder[ft]].child[1] = preorder[ft+mid-st+1];
    // printf("father %d left %d right %d\n",preorder[ft],preorder[ft+1],preorder[ft+mid-st+1] );
    // nodes[preorder[ft+1]].father = preorder[ft];
    // nodes[preorder[ft+1]].depth = nodes[preorder[ft]].depth+1;
    // nodes[preorder[ft+mid-st+1]].father = preorder[ft];
    // nodes[preorder[ft+mid-st+1]].depth = nodes[preorder[ft]].depth+1;

    creatTree(st,mid-1,ft+1,ft);
    creatTree(mid+1,end,ft+mid-st+1,ft);//参数写错
}

int findFather(int s1,int s2){
    int d1 = nodes[s1].depth;
    int d2 = nodes[s2].depth;
    int d = min(d1,d2);
    int f1=s1,f2=s2;
    while(d1>d){
        f1 = nodes[f1].father;
        d1 = nodes[f1].depth;
    }
    while(d2>d){
        f2 = nodes[f2].father;
        d2 = nodes[f2].depth;
    }
    // printf("f1 %d,f2 %d\n",f1,f2 );
    if(f1==f2){
        if(s1==f1) return -1;
        if(s2==f2) return -2;
    }
    else{
        while(f1!=f2){
            f1 = nodes[f1].father;
            f2 = nodes[f2].father;
        }
        return f1;
    }
}

/*
translation:
    给定一颗二叉树，求出对应*反转*二叉树的层次遍历和中序遍历结果
    input:
        第一行:根节点个数n,n<15，节点序号0~n-1
        后n行:序号i的节点的左右孩子对应的序号，若为空记为-

solution:
    根据输入将二叉树存储，并找到根节点对应序号，反转只需遍历时先访问右子树，再访问左子树
    层次遍历通过queue实现，中序遍历通过递归实现
note:
    1.这题二叉树不能通过数组存储，因为实现不知道每个节点应该存储的位置
      注意区分存储位置和节点序号的区别
    2.本题需要找到根节点对应序号，可以根据n先求出节点序号总和sum，然后在建树过程中记录孩子节点总和idsum
      sum-idsum即为根节点序号
    3.使用queue做层次遍历时不要忘了每次pop
    4.别忘了该注释的地方注释掉
date:
    2019.11.25
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <queue>
using namespace std;
const int MAXN = 15;
struct Node
{
    int child[2];
}nodes[MAXN];
int cnt = 0;
int n,sum,idsum=0;

void levelorder(int ft);
void inorder(int ft);
int main(int argc, char const *argv[])
{
    memset(nodes,-1,sizeof(nodes));
    int root;
    stringstream ss;
    cin>>n;
    sum = (n-1)*n/2;
    string child;
    int id;
    for(int i=0;i<n;i++){
        for(int j=0;j<2;j++){
            cin>>child;
            ss.clear();
            ss.str(child);
            if(child!="-"){
                ss>>id;
                idsum += id;
                nodes[i].child[j^1] = id;
                // cout<<id<<endl;
            }
        }
    }
    root = sum-idsum;
    // printf("root %d\n", root); //别忘了注释
    levelorder(root);
    inorder(root);
    return 0;
}

void levelorder(int ft){
    int k = 0;
    queue<int> q;
    q.push(ft);
    int t;
    while(!q.empty()){
        t = q.front();
        q.pop(); //忘记pop
        printf("%d",t );
        if(k<n-1)
            printf(" ");
        k++;
        if(~nodes[t].child[0])
            q.push(nodes[t].child[0]);
        if(~nodes[t].child[1])
            q.push(nodes[t].child[1]);
    }
    printf("\n");
}

void inorder(int ft){
    if(ft>=n) return;
    if(~nodes[ft].child[0])
        inorder(nodes[ft].child[0]);
    printf("%d",ft);
    if(cnt<n-1) printf(" ");
    cnt++;
    if(~nodes[ft].child[1])
        inorder(nodes[ft].child[1]);
}

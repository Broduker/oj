/*
translation:
    二叉树的中序遍历可以用栈这种非递归的方式来执行,通过对栈的push和pop来唯一确定了一棵树，
    观察例子可以发现push的顺序也就是这棵树的先序遍历的顺序，pop的顺序则是中序遍历
    根据输入的栈操作输出树的后序遍历结果
    input:
        第一行:树的节点数n(n<30)
        后2*n行:Push、Pop的栈操作

solution:
    我们就可以根据题目输入的push pop来得到一棵树的先序和中序遍历，从而得到题目中最终要求的后序遍历。
note:
    1.可以用sstream处理输入数据，注意stringstream的用法
      多次使用每次务必要ss.clear(),赋值使用ss.str(xxx)，如若清空内存stream.str("");
    2.getline会读取一行，并抛弃回车(不会留在缓冲区)，但是如果前面有cin或scanf，需要使用getchar先清除缓冲区的回车
      否则会被getline读取到
    3.注意根据前序、中序得到后序遍历的递归函数所需参数，需要定位子树的前序、中序序列范围
      因此需要中序遍历的起始和终止位置，前序遍历的父节点位置
    4.下标不要用错,比如preorder[ft]写成preorder[st]
date:
    2019.11.25
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <stack>
using namespace std;
const int MAXN = 35;
int preorder[MAXN];
int midorder[MAXN];
int postorder[MAXN];
int cto = 0;

void postOrder(int st,int end,int ft);
int main(int argc, char const *argv[])
{
    int n;
    int ctm = 0,ctp = 0;
    stringstream ss;
    stack<int> tree;
    string op;
    int node;
    cin>>n;
    getchar();
    for(int i=0;i<2*n;i++){
        getline(cin,op);
        ss.clear();
        ss.str(op);
        if(op.length()>5){
            ss>>op>>node;
            preorder[ctp++] = node;
           tree.push(node);
        }
        else{
            midorder[ctm++] = tree.top();
            tree.pop();
        }
    }
    // printf("Yes\n");
    postOrder(0,ctm-1,0);
    for(int i=0;i<cto;i++){
        if(i) printf(" ");
        printf("%d", postorder[i]);
    }
    printf("\n");
    return 0;
}
void postOrder(int st,int end,int ft){ //中序遍历的起始和终止位置，前序遍历的父节点位置
    if(st>end) return;
    int idm; //中序遍历的父节点位置
    for(int i=st;i<=end;i++){
        if(midorder[i]==preorder[ft]){ //preorder[ft]写成preorder[st]
            idm = i;
            break;
        }
    }
    postOrder(st,idm-1,ft+1); //左子树递归
    postOrder(idm+1,end,idm-st+ft+1); //右子树递归
    postorder[cto++] = preorder[ft];
}

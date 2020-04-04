/*
translation:
    给出数的后序遍历和中序遍历，求层序遍历的结果
    input:
        第一行:n 节点个数(n<30)
        后两行:后序遍历和中序遍历的节点对应值，题目没明确说按0~n-1给值
solution:
    通过map建立名字和序号的映射关系，建立二叉树，然后通过queue得到层序遍历结果
note:
    1.一定注意后序遍历与前序遍历相比需要修改的地方，
      一是后序遍历每棵子树父节点的序号是序列末尾对应的序号，不管是初始传参，还是递归传参不要写错
      二是后续遍历递归求左子树的父节点时，减去的差值是右子树的大小end-idm，而不是左子树的大小idm-st
    2.好像不能把层序遍历和建树的过程合二为一，因为一个有递归，一个无递归
    3.层序遍历左右子树的参数不要写错，是t而不是st
    4.inorder和postorder不要用错、用反
    5.映射map、rev赋值注意顺序
date:
    2019.11.26
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <queue>
using namespace std;
int const MAXN = 35;
struct Node
{
    int child[2];
}node[MAXN];

int postorder[MAXN],inorder[MAXN],levelorder[MAXN];
int cnt = 0;
map<int,int> mp,rev;
queue<int> q;
void LevelOrder(int st){
    // queue<int> q;
    q.push(st);
    int t;
    while(!q.empty()){
        t = q.front();
        // printf("top %d\n",t);
        q.pop();
        levelorder[cnt++] = t;
        if(~node[t].child[0]) //写成st
            q.push(node[t].child[0]); //写成st
        if(~node[t].child[1]) //写成st
            q.push(node[t].child[1]); //写成st
    }

}

int creatTree(int st,int end,int ft){//中序遍历的起始终止位置，*后*序遍历的父节点位置
    if(st>end) return -1;
    // queue<int> q;
    // q.push(inorder[ft]);
    // int t;
    // if(!q.empty()){
    int idm;
    // t = q.front();
    // levelorder[cnt++] = inorder[ft];
    // q.pop();
    for(int i=st;i<=end;i++){
        if(inorder[i]==postorder[ft]){ //两个数组用反
            idm = i;
            break;
        }
    }
    // printf("idm %d\n", idm);
    node[ft].child[0] = creatTree(st,idm-1,ft-(end-idm)-1); //这里的差要减去右子树的大小，而不是左子树的大小
    node[ft].child[1] = creatTree(idm+1,end,ft-1);

    // printf("st %d,end %d,ft %d\n",st,end,ft);
    // printf("ft %d,left %d,right %d\n",ft,node[ft].child[0],node[ft].child[1]);
    return ft;
    // }
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d",&n);
    int t;
    for(int i=0;i<n;i++){
        scanf("%d",&t);
        rev[cnt] = t;
        postorder[i] = cnt;
        mp[t] = cnt++; //注意顺序
    }
    for(int i=0;i<n;i++){
        scanf("%d",&t);
        inorder[i] = mp[t];
    }
    // printf("input over\n");
    cnt = 0;
    creatTree(0,n-1,n-1);
    // printf("creatTree over\n");
    LevelOrder(postorder[n-1]); //数组错用成inorder[0]
    // printf("LevelOrder over\n");
    for(int i=0;i<n;i++){
        if(i) printf(" ");
        printf("%d",rev[levelorder[i]] );
    }
    return 0;
}

/*
translation:
    给定一颗二叉树，判断是否为完全二叉树，如果是，输出完全二叉树的最后一个节点的序号，否则输出二叉树的跟几点
    input:
        第一行:n 节点的个数(n<=20) 序号0~n-1
        后n行: left right 第i个节点的孩子节点对应的序号,如果为空表示为'-'
        
solution:
    完全二叉树判断思路：通过层序遍历，当遍历到某个结点没有子结点时，那么它后面的所有结点都应该没有子结点。
note:
    1.由于节点可能表示为'-',需要加以判断再保存，注意节点序号可能为两位数，所以不能通过char保存再判断
    2.int保存char类型再进行后续转换操作会出错
    3.由于节点序号0~n-,通过计算节点序号总和idsum=(n-1)*n/2,以及出现的所有孩子节点和leafsum
      idsum - leafsum即为根节点对应的序号
    4.注意使用%c或getline要清除回车缓存
    5.注意该初始化的变量要进行初始化
date:
    2019.12.02
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <sstream>
using namespace std;
const int MAXN = 50;
struct Node
{
    int child[2]={-1,-1};
}node[MAXN];

int levelorder(int st);
int main(int argc, char const *argv[])
{
    int n;
    int root,leafsum = 0,idsum;
    scanf("%d",&n);
    idsum = (n-1)*n/2;
    stringstream ss;
    for(int i=0;i<n;i++){
        // str chd[2]; //int类型不行
        // string chd[2];
        string str;
        // getchar(); //去除回车
        // getline(cin,str);
        // scanf("%c %c",&chd[0],&chd[1]);
        for(int j=0;j<2;j++){
            cin>>str;
            if(str!="-"){
                ss.clear();
                ss.str(str);
                ss>>node[i].child[j];
            // if(chd[j]!='-'){
                // printf("chd%d %d\n",j,chd[j]-'0');
                // node[i].child[j] = chd[j] - '0';
                leafsum += node[i].child[j];
                // printf("leafsum %d\n",leafsum);
            }
        }
    }
    root = idsum - leafsum;
    // root = GetRootIndex();
    int ans = levelorder(root);
    if(~ans){
        printf("YES %d\n", ans);
    }
    else{
        printf("NO %d\n", root);
    }
        // printf("NO %d\n", root);
    return 0;
}


int levelorder(int st){
    int flag = 0;
    // bool flag = false;
    queue<int> q;
    q.push(st);
    int t = -1;
    while(!q.empty()){
        t = q.front();
        // printf("t %d\n",t);
        q.pop();
        for(int i=0;i<2;i++){
            if(flag && ~node[t].child[i])
                return -1;
            if(node[t].child[i]==-1){
                flag = 1;
            }
            else{
                q.push(node[t].child[i]);
            }
        }

        // if(node[t].child[0]==-1 || node[t].child[1]==-1){
        //     flag = 1;
        // }
        // if(flag && (~node[t].child[0] || ~node[t].child[1])){
        //     return -1;
        // }
        // if(~node[t].child[0]){
        //     q.push(node[t].child[0]);
        // }
        // if(~node[t].child[1]){
        //     q.push(node[t].child[1]);
        // }
    }
    return t;
}

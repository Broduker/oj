/*
translation:
    给定一颗非空多叉树，每个节点都有对应的id和权重w，给出一个目标值s，找出所有符合
    从根节点到叶节点的路径中每个节点权重值总和等于k的路径，输出路径对应节点对应的权重值，
    如果有多条符合条件的路径，按照非递增顺序输出。如{10 5 2 7} > {10 4 10}
    input:
        第一行:n,m,s n代表节点数(0<n<=100)，m代表非叶子节点数,s代表目标值
        第二行:n个正数wi代表第i个节点的权重值，(wi<1000)
        后m行: id k id[1] id[2] ... id[k] 代表第id个节点有k个子节点，序号分别为id[1],id[2]...
solution:
    使用树的深度遍历即可，将每遍历一个节点求出权重和，输出符合条件的路径
    为了非递增顺序输出，可以先将每个符合条件的路径保存，然后排序
    更好地方式是在输入每个节点的孩子节点时，将每个节点的孩子节点按权重值降序排序，
    这样dfs找到的符合条件的路径就是按照非递增顺序，直接输出即可
note:
    1.解决非递增顺序输出，可以在输入节点就对子节点进行降序排序
    2.数组起别名的方式typedef char Path[MAXN];
    3.函数定义参数值更改后，声明一定要同步修改
    4.统计符合条件路径个数的kase值不要放到递归函数中，否则计数值错误
    5.注意string初始值赋值成"\0"后面拼接字符串是否会造成错误
    6.~t的含义别弄反，并且注意判断终止条件是pre[t]==-1还是t==-1
    7.注意string是如何比较大小的
    8.注意输出的是节点对应的权值，而不是节点序号，而权值的范围是[0,1000)
date:
    2019.11.24
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 110;
struct Node
{
    int w;
    vector<int> child;
};
// typedef char Path[MAXN];
typedef string Path;
Node nodes[MAXN];
vector<Path> paths;
int pre[MAXN];
int n,m;
int aim;
int kase = 0;
void dfs(int father,int valsum);
void PrintPath(int t,int cnt);
bool cmp(const Path &s1,const Path &s2); //md参数写成char[]没改

int main(){

    memset(pre,-1,sizeof(pre));
    scanf("%d %d %d",&n,&m,&aim);
    for(int i=0;i<n;i++){
        scanf("%d",&nodes[i].w);
    }
    int id,subn,t;
    for(int i=0;i<m;i++){
        scanf("%d%d",&id,&subn);
        for(int j=0;j<subn;j++){
            scanf("%d",&t);
            nodes[id].child.push_back(t);
            // printf("child %d\n",t);
        }
    }

    dfs(0,nodes[0].w);
    sort(paths.begin(),paths.end(),cmp);//忘了取消注释
    for(int i=0;i<paths.size();i++){
        // printf("%s\n", paths[i]);
        int len = paths[i].length();
        int flag;
        for(int j=0;j<len;j++){
            if(j%3==0){
                flag = 0;
                if(j>0) printf(" ");
            }
            if(paths[i][j]=='0' && !flag) continue;
            printf("%c",paths[i][j] );
            flag = 1;
        }
        printf("\n");
        // cout<<paths[i]<<endl;
    }
    return 0;
}

void dfs(int father,int valsum){
    // printf("id %d,valsum %d\n",father,valsum);
    if(valsum>aim){
        return;
    }
    if(valsum==aim && !nodes[father].child.size()){
        // printf("Yes\n");
        paths.push_back("\0");//是\0还是空没有影响
        PrintPath(father,0);
        kase++;
    }
    for(int i=0;i<nodes[father].child.size();i++){
        int id = nodes[father].child[i];
        valsum += nodes[id].w;
        pre[id] = father;
        // printf("pre id %d\n",id);
        dfs(id,valsum);
        valsum -= nodes[id].w;
    }
}

void PrintPath(int t,int cnt){
    // printf("t %d\n", t);
    // printf("path %d\n",t);
    if(t==-1){ //应该用t而不是pre[t],正好写反成~pre[t]
        // paths[kase][cnt] = '\0';
        // paths[kase] += "\0";
        // cout<<"t "<<t<<"path "<<paths[kase]<<endl;
        // kase++; //放这里由于递归，导致一个路径中值就会不断增加
        return;
    }
    PrintPath(pre[t],cnt+2);
    char num[5]; //权值的范围是<1000
    // fprintf(paths[kase]+cnt,"%02d",t);
    sprintf(num,"%03d",nodes[t].w);//权值的范围是<1000
    // printf("num %s\n", num);
    paths[kase] += num;
    //cout<<"path "<<paths[kase-1]<<endl;
}

bool cmp(const Path &s1,const Path &s2){
    // return strcmp(s1,s2) < 0;
    return s1>s2;
}

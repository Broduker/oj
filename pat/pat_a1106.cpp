/*
translation:
    一条供应链中包含零售商、经销商、供应商三个角色。
    根节点供应商的序号为0，给出起始价格，并将产品卖给下家，经销商或零售商从他们各自供应商拿货，
    并再以r%的加价卖给下家。
    求零售商所能卖到的最低价格(保留4位小数)，即对应的人数
    input:
        第一行:供应链总人数n，起始价格p，加价率r，其中n<10^5，编号0~n-1
        后m行: k id[1] id[2] ... id[k] 代表第i个供应商的有k个下家，序号分别为id[1],id[2]...

solution:
    建立多叉树，深度遍历求出最高深度对应的价格以及r人数
note:
    1.本题要求输出最高价格的零售商个数，而非对应的id
    2.各个值的初始值不要弄错
    3.不要忘记递归
    4.注意输入参数的顺序
date:
    2019.11.25
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1e5+10;
const int INF = 0x3f3f3f3f;
double minPrice = INF;
int minsum = 0;
int n;
double rate,st_price;
struct Node
{
    double price;
    vector<int> child;
}nodes[MAXN];

void dfs(int ft);
int main(int argc, char const *argv[])
{
    scanf("%d %lf %lf",&n,&st_price,&rate); //注意顺序
    nodes[0].price = st_price;
    for(int i=0;i<n;i++){
        int k,id;
        scanf("%d",&k);
        for(int j=0;j<k;j++){
            scanf("%d",&id);
            nodes[i].child.push_back(id);
        }
    }
    dfs(0);
    printf("%.4lf %d",minPrice,minsum);
    return 0;
}

void dfs(int ft){
    if(!nodes[ft].child.size()){
        if(nodes[ft].price<minPrice){
            minPrice = nodes[ft].price;
            minsum = 1;
        }
        else if(nodes[ft].price==minPrice){
            minsum++;
        }
    }
    for(int i=0;i<nodes[ft].child.size();i++){
        int t = nodes[ft].child[i];
        nodes[t].price = nodes[ft].price*(1+0.01*rate);
        dfs(t); //又忘了dfs
    }
}
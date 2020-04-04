/*
translation:
    给出n中不同类型的石块，每种类型的石块长宽高都不一样。对于两块石块a,b。只有当a的底面的长宽严格小于b的长宽时，
    a才能摆放在b的上面。问最多能够将石块叠加到多高。
solution:
    最长上升子序列的变形
    具体做法是先按照长宽或者宽长对各类的长方体进行排列。然后在直接套上lis的模型即可。
    注意每个长方体有6种不同的摆放状态。所以可以将其看成6个类型的长方体，通过长宽的排列可以缩减到3种。
    然后按照长宽由小到大的顺序进行排列，再使用LIS即可
note:
    在写构造函数时，错写了高对应的变量又没有报错，导致赋值有误
    关键时如何转换为LIS的形式，一个是由于同一类型的长方形可以使用n次，所以将序列中一个长方形可以扩展为3个
    另一个是LIS是事先顺序已定，这里就要把长方形按照长宽的大小进行预先排序，再使用dp
date:
    2019.08.06
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 95;
int dp[MAXN];
struct rect
{
    int a,b,h;
    rect(int a,int b,int h){
        this->a = a;
        this->b = b;
        this->h = h;
    }
    rect(){}
};
bool cmp(rect r1,rect r2){
    if(r1.a==r2.a){
        return r1.b < r2.b;
    }
    else{
        return r1.a < r2.a;
    }
}
vector<rect> blocks;
int main(int argc, char const *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    int n;
    int kase = 0;
    int dim[3];
    int ans;
    while(cin>>n && n){
        for(int i=0;i<n;i++){
            cin>>dim[0]>>dim[1]>>dim[2];
            sort(dim,dim+3);
            // printf("%d %d %d\n", dim[0],dim[1],dim[2]);
            blocks.push_back(rect(dim[0],dim[1],dim[2]));
            blocks.push_back(rect(dim[0],dim[2],dim[1]));
            blocks.push_back(rect(dim[1],dim[2],dim[0]));

        }
        sort(blocks.begin(),blocks.end(),cmp);
        ans = 0;
        for(int i=0;i<3*n;i++){
            dp[i] = blocks[i].h;
            // cout<<"h "<<blocks[i].h<<endl;
            for(int j=0;j<i;j++){
                if(blocks[j].a < blocks[i].a && blocks[j].b < blocks[i].b){
                    dp[i] = max(dp[i],dp[j]+blocks[i].h);
                }
            }
            ans = max(ans,dp[i]);
        }
        printf("Case %d: maximum height = %d\n",++kase,ans);
        blocks.clear();
    }
    return 0;
}

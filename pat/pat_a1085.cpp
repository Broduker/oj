/*
translation:
    给定参数p，若一个序列seq中，max(seq)<=min(seq)*p,则称该序列为完美序列
    给定一个含有n个数字的序列，求出含有数量最多的子序列，满足完美序列的条件
    输出子序列的长度
    input:
        第1行:n p n表示序列长度(n<=10^5) p为给定参数(p<=10^9)
        第2行:序列值
solution:
    将给定序列排序，寻找满足条件的子序列中，子序列长度最大的
    如果暴力搜索，复杂度O(n^2) 可以采用二分查找，
    每输入子序列起点t，通过二分查找t~n-1中满足条件的最大值，

note:
    1.注意序列最短长度可为1，即最大值最小值可为同一个值，二分查找的范围要注意
    2.二分查找的写法要写对，要有返回值，将递归结果保存，最后返回，或直接返回
    3.本题采用相除的方式进行不等式判断，注意将结果转为浮点数
      采用相除的方法注意可能超过int的范围
    4.默认*1.0的类型是float需要用%f输出而非%lf
    5.二分查找的返回值注意不要因为没写条件判断被覆盖
    6.输入参数不要少
    7.本题可使用lower_bound()和upper_bound() 默认是第一个>= / >的值的地址，可通过greater重载
      注意返回为地址，减去数组首地址才是坐标
date:
    2019.11.27
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN = 1e5+10;
int seq[MAXN];
int n,p;

int biSearch(int st,int end,int id){
    // 刚开始没有定义返回值
    // printf("st %d,end %d\n",st,end);
    if(st>end){
        return st-1;
    }
    int idm = (st+end)/2;
    int ans;
    if(1.0*seq[idm]/seq[id]>p)
        ans = biSearch(st,idm-1,id);
    if(1.0*seq[idm]/seq[id]<p)
        ans = biSearch(idm+1,end,id);
    // printf("none\n");
    if(1.0*seq[idm]/seq[id]==p){
        ans = idm; //写在判断外面了，导致不管情况如何都会覆盖前面的结果
        // printf("(%d,%d) result %d %d %f\n",id,idm,seq[idm],seq[id],1.0*seq[idm]/seq[id]);
    }
    return ans;
}

int main(int argc, char const *argv[])
{

    scanf("%d %d",&n,&p); //少写参数
    for(int i=0;i<n;i++){
        scanf("%d",&seq[i]);
    }
    sort(seq,seq+n);
    int ans = 0;
    for(int i=0;i<n;i++){
        // int to = lower_bound(seq,seq+i,1.0*seq[i]/p)-seq;
        // ans = max(ans,i-to+1);
        int to = biSearch(i,n-1,i);
        ans = max(ans,to-i+1);
        // printf("left %d,right %d\n",i,to);
    }
    printf("%d\n", ans);
    return 0;
}


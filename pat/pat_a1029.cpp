/*
translation:
    求两个序列合并成非递减序列后的中值
solution:
    合并后排序求中值
note:
    中值位置注意奇数偶数情况不同
date:
    2019.11.27
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int MAXN = 4*1e5+10;
int seq[MAXN];
int main(int argc, char const *argv[])
{
    int n1,n2;
    scanf("%d",&n1);
    for(int i=0;i<n1;i++){
        scanf("%d",&seq[i]);
    }
    scanf("%d",&n2);
    for(int i=0;i<n2;i++){
        scanf("%d",&seq[n1+i]);
    }
    sort(seq,seq+n1+n2);
    printf("%d",seq[(int)ceil((n1+n2)*1.0/2)-1]);
    return 0;
}

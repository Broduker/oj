/*
translation:
    给你一个数列，里面有一个元素一定会出现超过（n+1）/2次，输出这个数 
solution:
    第一种办法sort后输出，复杂度O(nlogn)
    第二种线性遍历一次，设置计数器cnt=0，当计数器为0时，令结果赋值为当前遍历到的值，
    此后遇到相同值+1，否则-1，当计数器变为0，重新赋值，只有个数大于1半的值最后计数不会减为0，即为答案
note:
    尝试使用每次删除不同的两个数，但是结果超时
date:
    2019.08.06
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAXN = 1e6+10;
int seq[MAXN];
// char chrseq[MAXN];
// string seq;
int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    int n;
    // int seq;
    int ans,cnt;
    while(cin>>n){
        cnt = 0;
        // cin>>seq;
        for(int i=0;i<n;i++){
            cin>>seq[i];
        }

        for(int i=0;i<n;i++){
            if(cnt==0){
                ans = seq[i];
                cnt++;
            }
            else{
                if(ans==seq[i]){
                    cnt++;
                }
                else{
                    cnt--;
                }
            }

        }

        cout<<ans<<endl;
        // sort(seq,seq+n);
        // cout<<seq[(n+1)/2]<<endl;
    }
    return 0;
}

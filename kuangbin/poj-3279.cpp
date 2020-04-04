/*
translation:
    给定一个m*n的01矩阵(1 <= m,n <= 15)
    每次操作选择一个格子，使得该格子与上下左右四个格子的值翻转。
    至少多少次操作可以使得矩阵中所有的值变为0？
    请输出翻转方案，若没有方案，输出"IMPOSSIBLE” 。
    若有多种方案符合题意，请首先输出翻转次数最少的方案；若方案个数仍不唯一，则输出字典序最小的方案。

solution:
    实际上如果给出第一行格子的翻转情况，即可确定剩下格子的翻转情况。
    因为当第i行翻转完毕后，要想使第i行格子剩下不为0的全变为0，只能依赖第i+1行
    因此，当操作dt[i+1][k],即第i+1行时的第k个格子时，若dt[i][k]为1，则该格子必须翻转，依此类推
    当最后一行也翻转完毕后，只需判断最后一行是否全为0，若为0则输出对应翻转结果(每个格子只能为0、1),否则输出IMPOSSIBLE
    因为方案由第一行的结果唯一确定，所以按字典序枚举第一行的所有方案，输出便是最小字典序。

note:
    1.注意遍历时下标不要弄错，比如k++写成i++
    2.注意复制粘贴时对应的下标也需要更改
    3.不要忘了在翻转四周前，中心的格子先要进行翻转
    4.第一行和其余行的操作可以合并在一起写
    5.每一个格子其实最多主动翻转一次
date:
    2019.08.29
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN = 20;
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};
int dt[MAXN][MAXN],cp[MAXN][MAXN];
int times[MAXN][MAXN];
int m,n;

int search();
bool isAllZero(int t);
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&dt[i][j]);
        }
    }
    if(search()){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(j) printf(" ");
                printf("%d",times[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("IMPOSSIBLE\n");
    }
    return 0;
}

bool isAllZero(int t){
    for(int i=0;i<m;i++){
        if(cp[t][i])
            return false;
    }
    return true;
}

bool isAvail(int x,int y){
    return (x>=0 && x<n && y>=0 && y<m) ? true : false;
}

int search(){
    int bitn;
    bitn = 1<<m;
    // printf("bitn %d\n",bitn);
    for(int i=0;i<bitn;i++){
        memcpy(cp,dt,sizeof(dt));
        // printf("op\n");
        // for(int j=0;j<m;j++){
        //     // cp[0][j] = dt[0][j];
        //     int op = (i>>j)&1;
        //     times[0][j] = op;
        //     // printf("%d ",op);
        //     // printf("cp %d\n", cp[0][j]);
        //     cp[0][j] = cp[0][j] ^ op;
        //     int tp;
        //     for(int k=0;k<4;k++){ // k++写成i++
        //         // printf("k %d\n", k);
        //         int x = 0 + dx[k];
        //         int y = j + dy[k];
        //         if(isAvail(x,y)){
        //             cp[x][y] = cp[x][y] ^ op;
        //         }
        //     }
        // }
        // printf("\n");
        for(int j=0;j<n;j++){
            for(int k=0;k<m;k++){
                // cp[i][j] = dt[i][j];
                int op;
                if(!j) 
                    op = (i>>k)&1; //复制粘贴下标要改
                else 
                    op = cp[j-1][k];
                times[j][k] = op;
                cp[j][k] = cp[j][k] ^ op; //忘了写
                for(int h=0;h<4;h++){
                    int x = j + dx[h];
                    int y = k + dy[h];
                    if(isAvail(x,y)){
                        cp[x][y] = cp[x][y] ^ op;
                    }
                }
            }
        }
        if(isAllZero(n-1)){
            return 1;
        }
    }
    return 0;
}

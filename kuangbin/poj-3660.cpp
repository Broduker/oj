/*
translation:
    有n头牛， 给你m对关系（a, b）表示牛a能打败牛b， 求在给出的这些关系下， 最多能确定多少牛的排名。
solution:
    如果一头牛被x头牛打败，并且可以打败y头牛，并且x+y=n-1，则这头牛的排名就被确定了，
    所以我们只要将任一头牛，可以打败其他的牛的个数x， 和能打败该牛的牛的个数y求出来，并判断一下是否满足x+y=n-1，就知道这个牛的排名是否能确定了
    遍历所有牛，进行如上操作并统计，就可以知道排名被确定的牛的个数
    floyd-warshall求解传递闭包，能将所有能得出关系都求出来， 再将满足这个条件的牛数目加起来就是所求解。 x可以看成是入度， y是出度。
    这里dis[i][j] = 1,表示牛i可以击败牛j,或者说存在i到j的路径，统计任意牛i的入度和初度,并判断in[i]+out[i]==n-1，即可判断是否排名确定
    更新条件我们可以修改为if(d[i][j] == 1 || (d[i][k] == 1 && d[k][j] == 1))   d[i][j] = 1;
note:
    一个小坑坑了很久
    1.定义了全局变量m,n 又定义局部变量m,n 导致全局变量没有被赋值 一直为0，结果出错
    2.更新表达式+=不要写成=
    3.注意考虑dis[i][i]的情况会不会影响结果，这里的写法暂时不会
date:
    2019.08.31
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstring>
using namespace std;
const int MAXN = 110;
const int MAXM = 4510;
int dis[MAXN][MAXN];
int in[MAXN],out[MAXN];
int n,m;
void floid();
int main(int argc, char const *argv[])
{
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    memset(dis,0,sizeof(dis));
    // int n,m;
    scanf("%d %d",&n,&m);
    // printf("n %d\n", n);
    int a,b;
    for(int i=1;i<=m;i++){
        scanf("%d %d",&a,&b);
        dis[a][b] = 1;
        out[a]++;
        in[b]++;
    }
    floid();
    // printf("dis42 %d dis25 %d\n",dis[4][2],dis[2][5]);
    // printf("dis45 %d\n",dis[4][5] | (dis[4][2]&dis[2][5]));
    int ans = 0;
    for(int i=1;i<=n;i++){
        // printf("i %d in %d out %d\n", i,in[i],out[i]);
        if(in[i]+out[i]==n-1){
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}

void floid(){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                // printf("Yes %d %d %d\n",i,k,j );
                out[i] += !dis[i][j] & (dis[i][k]&dis[k][j]); //+=写成=
                in[j] += !dis[i][j] & (dis[i][k]&dis[k][j]);
                dis[i][j] = dis[i][j] | (dis[i][k]&dis[k][j]);
            }
        }
    }
}

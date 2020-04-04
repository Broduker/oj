/*
translation:
    给定三个杯子，容量分别为s,n,m,满足s=n+m，初始s装满，
    求相互倒可乐，使得任意两个杯子平分n+m的最小次数，无法平分输出NO
solution:
    因为是平分可乐，那么s必须是偶数
    设三个容器的编号分别为1,2,3，
    可乐的六种倒法：1倒2，1倒3，2倒1，2倒3，3倒1,3倒2，模拟这六种道倒法即可
    用一个三维数组表示这三个瓶子时时刻刻的状态，广搜枚举各个状态下的操作
    判断达到平分状态：n和m是不可能平分的s的，除非n=m，但是max（n，m）和s一定能平分可乐，所以最后只要判断k1=k2，k3=0即可
 
note:
    1.注意构造体，如果初始化函数参数有默认值，设置后仍需要赋值给结构体对应变量
    2.注意结构体内部变量和形参不要写错写混
    3.注意调用状态转移函数参数s是引用，会改变值，如果后面要用到原始值需要重新赋值
    4.注意临时变量和用来赋值的原始变量不要写混
    5.本题还有神仙的数论解法
        if s/gcd(n,m) % 2 == 1 -> NO
        else ans = s/gcd(n,m) - 1

date:
    2019.08.27
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN = 110;
struct State
{
    int rest[3];
    int times;
    // State(int s1_,int s2_,int s3_,int times_=0):rest[0](s1_),rest[1](s2_),rest[2](s3_),times(times_){}
    State(int s1,int s2,int s3,int times_=0){
        rest[0] = s1,rest[1] = s2,rest[2] = s3,times = times_; //times_写成times
    }
    State(int times_=0):times(times_){}
};
int visit[MAXN][MAXN][MAXN];
int cpt[3];

int bfs(int s1,int s2,int s3);
void trans(int s1,int s2,State &s);
int main(){
    cin.tie(0);
    cin.sync_with_stdio(false);
    // int a,b,n;
    int ans;
    while(~scanf("%d %d %d",&cpt[0],&cpt[1],&cpt[2]) && cpt[0] && cpt[1] && cpt[2]){
        memset(visit,0,sizeof(visit));
        if(cpt[0]&1 || (ans=bfs(cpt[0],0,0))==-1){
            printf("NO\n");
        }
        else{
            printf("%d\n",ans);
        }
    }

}

int bfs(int s1,int s2,int s3){
    State t(s1,s2,s3);
    // printf("times %d\n", t.times);
    queue<State> q;
    q.push(t);
    visit[s1][s2][s3] = 1;
    while(!q.empty()){
        State t = q.front();
        q.pop();
        if((t.rest[0]==t.rest[1] && !t.rest[2]) || (t.rest[0]==t.rest[2] && !t.rest[1])){
            // printf("Yes %d %d %d %d\n",t.rest[0],t.rest[1],t.rest[2],t.times );
            return t.times;
        }
        for(int i=0;i<3;i++){
            State temp = t; //忘了会被改变
            // printf("test %d %d %d %d\n",temp.rest[0],temp.rest[1],temp.rest[2],temp.times );
            // printf("address %d %d\n",&temp,&t);
            trans(i,(i+1)%3,temp); //t忘改temp
            if(!visit[temp.rest[0]][temp.rest[1]][temp.rest[2]]){
                temp.times += 1;
                q.push(temp);
                visit[temp.rest[0]][temp.rest[1]][temp.rest[2]] = 1;
                // printf("%d %d %d %d\n",temp.rest[0],temp.rest[1],temp.rest[2],temp.times );
                // printf("i %d\n",i );
            }
            temp = t;
            // printf("test %d %d %d %d\n",temp.rest[0],temp.rest[1],temp.rest[2],temp.times );

            trans(i,(i+2)%3,temp);
            if(!visit[temp.rest[0]][temp.rest[1]][temp.rest[2]]){
                temp.times += 1;
                q.push(temp);
                visit[temp.rest[0]][temp.rest[1]][temp.rest[2]] = 1;
                // printf("%d %d %d %d\n",temp.rest[0],temp.rest[1],temp.rest[2],temp.times );
                // printf("i %d\n",i );
            }
        }
    }
    return -1;
    // printf("fail\n");
}

void trans(int s1,int s2,State &s){
    if(s.rest[s1]>cpt[s2]-s.rest[s2]){
        s.rest[s1] -= (cpt[s2]-s.rest[s2]);
        s.rest[s2] = cpt[s2];
    }
    else{
        s.rest[s2] += s.rest[s1];
        s.rest[s1] = 0;
    }
}

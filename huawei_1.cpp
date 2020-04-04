#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 110;
long long seq[MAXN];
int cnt=0;
bool judge_1();
bool judge_2();
bool judge_3();
int cal(long long t);
int main(){
    int ch;
    int kase = 0;
    while(~scanf("%lld",&seq[cnt++])){
        // cnt = 1;
        ch = getchar();
        // scanf("%d",&seq[cnt++]);
        // printf("seq %d cnt %d ch %c\n",seq[cnt-1],cnt, ch);
        if(ch=='\n'){
            if(kase){
                printf(" ");
            }
            // printf("over\n");
            if(judge_1()||judge_2()||judge_3()){
                printf("true");
            }
            else printf("false");
            cnt = 0;
            kase++;
        }
    }
    printf("\n");
}

bool judge_1(){
    for(int i=0;i<cnt-1;i++){
        // printf("ii %d\n",i);
        // printf("yihuo %d %d i %d\n",seq[i],cal(seq[i+1]),i );
        if(cal(seq[i])^cal(seq[i+1])){ //括号没写全导致 seq[i]^cal(seq[i+1])整体当成了第一个函数的参数
            continue;
        }
        // printf("i %d\n",i);
        return false;
    }
    // printf("j1\n");
    return true;
}

bool judge_2(){
    if(cal(seq[0]) && cal(seq[cnt-1])){
        for(int i=1;i<cnt-1;i++){
            if(!cal(seq[i]))
                continue;
            return false;
        }
        // printf("j2\n");
        return true;
    }
    return false;
}
bool judge_3(){
    if(!cal(seq[0]) && !cal(seq[cnt-1])){
        for(int i=1;i<cnt-1;i++){
            if(cal(seq[i]))
                continue;
            return false;
        }
        // printf("j2\n");
        return true;
    }
    return false;
}

int cal(long long t){
    if(t/10>0)
        return 1;
    return 0;
}

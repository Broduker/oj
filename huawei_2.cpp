#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1010;

char seq[MAXN];
int cnt = 0;
void trans();
int main(int argc, char const *argv[])
{
    int ch;
    while((ch=getchar())!='\n'){
        // printf("ch %c\n", ch);
        seq[cnt++] = ch;
    }
    trans();
    for(int i=cnt-1;i>=0;i--){
        printf("%c", seq[i]);
    }
    printf("\n");
    return 0;
}

void trans(){
    for(int i=0;i<cnt;i++){
        if(seq[i]==' ')
            seq[i] = '0';
        else if(seq[i]>='A' && seq[i] <='Z'){
            seq[i] = seq[i] + 'a' - 'A';
        }
    }
}
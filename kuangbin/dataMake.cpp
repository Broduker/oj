#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15;
int main()
{
    freopen("data.in","w",stdout);//设置 cout printf 这些输出流都输出到 test.in里面去
    srand(unsigned(time(0)));
    int T;
    char str[] = {".#"};
    int len = strlen(str);
    // printf("len %d\n",len);
    scanf("%d",&T);
    printf("%d\n",T);
    int n,m;
    for(int i=0;i<T;i++){
        n = rand()%MAXN+1;
        m = rand()%MAXN+1;
        printf("%d %d\n", n,m);
        for(int j=0;j<n;j++){
            for(int k=0;k<m;k++){
                int bt = rand()%len;
                printf("%c", str[bt]);
            }
            printf("\n");
        }
    }
    return 0;
}

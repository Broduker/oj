#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int ten[] = {1,10,1000,10000};


int case_1(char str[]){
    int len = strlen(str);
    int i = len-1;
    int t = 0;
    int num = 0;
    while(str[i]>='0' && str[i]<='9'){
        num += (str[i]-'0')*ten[t];
        i--;
        t++;
    }
    return (num-1)*50;
}

int case_2(char str[]){
    int len = strlen(str);
    int num = 0;
    for(int i=0;i<len;i++){
        num+=str[i];
        num%999;
    }
    return num;
}
/*
int case_3(char str1[],char str2[]){
    int t1 = case_1(str1);
    int t2 = case_2(str2);
    if(avail[t2] && t1!=t2){
        return t2;
    }
    else

}
*/
// int next(int addr){
//     for(int i=addr;i<999;i++){
//         if(avail[i]==1){
//             return i;
//         }
//     }
// }

int main(int argc, char const *argv[])
{
    int k;
    char str1[50][10000];
    char str2[10000];
    scanf("%d:",&k);
    scanf("%s",str2);
    if(str2[0]=='r'){
        printf("%d\n",case_1(str2));
    }
    else{
        printf("%d\n",case_2(str2) );
    }
    // int cnt = 0;
    // int ch;
    // ch =getchar();

    // while(ch!=','){
    //     while(ch!=','){

    //     }
    //     str[cnt][i] = ch;
    //     i++;
    //     if(ch=='\n'){
    //         break;
    //     }
    //     if(ch==';'){
    //         int j = 0;
    //         ch = getchar();
    //         while(ch!='\n'){
    //             str2[j] = ch;
    //             j++;
    //         }
    //     }
    // }
    return 0;
}

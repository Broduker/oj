/*
translation:
    给定n个字符串，m个查询，对于每个查询，给定一个字符串，输出n个字符串里是待查询字符串前缀的数目
    input:
        第一行:n,m
        接下来n行：字符串s[i] 最大不超过1e6
        接下来m行: 待询问字符串t
    输出:
        对于每个待查询的字符串t输出前缀数目

solution:
    针对n个字符串建立trie树，每个节点标记以该节点为结尾的字符串数目,
    对于每个查询字符串t 遍历trie 累加途径节点标记的字符串数目即为前缀的总数目
note:
    1.节点标记记录数目而非bool是为了避免重复字符串没有统计的情况
    2.数据量有问题导致溢出异常 如果去掉memset的初始化则不会溢出报错
date:
    2020.03.15
*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1e6+10;
int cnt = 1;
int n,m;
int tail[MAXN*26];
int trie[MAXN][26];

void create(string str);
int search(string str);
int main(){
    memset(tail,0,sizeof(tail));
    memset(trie,0,sizeof(trie));
    scanf("%d %d",&n,&m);
    string s;
    for(int i=0;i<n;i++){
        cin>>s;
        create(s);
    }
    for(int i=0;i<m;i++){
        cin>>s;
        int ans = search(s);
        printf("%d\n",ans);
    }
}

int search(string str){
    bool flag = true;
    int p = 1, n = 0;
    int len = str.length();
    for(int i=0;i<len;i++){
        int c = str[i] - 'a';
        if(!trie[p][c]){
            break;
        }
        else{
            p = trie[p][c];
            n += tail[p];
        }
    }
    return n;
}

void create(string str){
    // int cnt = 0;
    int p = 1;
    int len = str.length();
    for(int i=0;i<len;i++){
        int c = str[i] - 'a';
        if(!trie[p][c]){
            trie[p][c] = ++cnt;
        }
        p = trie[p][c];
    }
    tail[p]++; // 防止单词重复
}

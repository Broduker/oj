/*
translation:
    给定一个原始序列，和对其进行部分排序后的结果
    判断是归并排序还是插入排序，并输出
    同时输出再进行一次相同排序子操作后的结果
solution:
    分别建立插入排序和归并排序的函数进行排序模拟
    在每一步判断和部分排序后的结果是否相同，
    如果相同，打上标记，再进行一次排序操作后输出相应结果
note:
    1.这里需要把排序的每步操作进行分离，因此归并排序的递归写法不能使用
      另外也是因为递归的写法对应的合并操作数组大小不唯一
    2.memcpy第三个参数对应的是字节数，要乘上对应变量所占字节
      同时最好复制整个数组，否则复制部分数组容易出错
    3.归并排序注意每次操作的子数组的开始位置不一定是0，
      变量初始化的值不要弄错
    4.注意归并排序的写法要考虑数组不会刚好整除的情况，写好判断条件
      同时注意合并的子数组长度和合并后的数组长度两个变量不要用混
    5.这里插入排序，在判断是否和部分排序结果相同时，
      如果不排除一次排序操作也没进行的情况，有一个测试点过不去，感觉有问题
date:
    2019.11.27
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN = 110;
int seq[MAXN],sortseq[MAXN];
int miseq[MAXN],backup[MAXN];
int flag = 0;
int n;

void InsertSort();
void MergeSort(int st,int end);
bool isSame(int s1[],int s2[]);
void NoRecMergeSort(int st,int end);
void merge(int st,int end,int mid);
int main(int argc, char const *argv[])
{
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&seq[i]);
        backup[i] = seq[i];
    }
    for(int i=0;i<n;i++){
        scanf("%d",&sortseq[i]);
    }
    InsertSort();
    if(flag==1){
        printf("Insertion Sort\n");
    }
    else{
        memcpy(seq,backup,sizeof(int)*n);
        NoRecMergeSort(0,n-1);
        printf("Merge Sort\n");
    }
    for(int i=0;i<n;i++){
        if(i) printf(" ");
        printf("%d",seq[i]);
    }
    return 0;
}

void InsertSort(){
    for(int i=1;i<n;i++){
        if(flag) break;
        // if(flag==1) flag++;
        if(i!=1 && isSame(sortseq,seq)){// 这里不加i!=1有一个测试点过不去
        // if(isSame(sortseq,seq)){
            flag = 1;
        }
        int k = i;
        while(seq[k]<seq[k-1] && k>0){
            swap(seq[k],seq[k-1]);
            k--;
        }
    }
    // printf("insert sort over\n");
}

void MergeSort(int st,int end){
    // printf("st %d,end %d\n",st,end);
    if(st>=end) return;
    // if(flag==2) return;
    int mid = (st+end)/2;
    MergeSort(st,mid);
    MergeSort(mid+1,end);
    memcpy(miseq,seq,sizeof(int)*n); //第三个参数是字节数
    int i=st,j=mid+1,k=st; //k不能设为0
    while(i<=mid && j<=end){
        // printf("st %d,end %d,i %d,j %d,k %d\n",st,end,i,j,k);
        // printf("misseq %d %d\n",miseq[i],miseq[j]);
        if(miseq[i]<miseq[j]){
            seq[k++] = miseq[i++];
        }
        else{
            seq[k++] = miseq[j++];
        }
    }
    int t = (i<=mid) ? i : j;
    while(k<=end){
        seq[k++] = miseq[t++];
    }
    for(int i=st;i<=end;i++){
        // printf("%d ",seq[i]);
    }
    // printf("\n");
    if(flag==1) flag++;
    if(isSame(sortseq,seq)){
        flag = 1;
        // printf("it is same\n");
        // system("pause");
    }
}

void NoRecMergeSort(int st,int end){
    int deta = 2,h = 1;
    while(h<(end-st+1)){ //不应该是deta
        // if(flag==2) break;
        if(flag==1) break;
        // if(h!=1 && isSame(seq,sortseq)){
        if(isSame(seq,sortseq)){
            flag = 1;
        }
        for(int i=st;i<=end;i+=deta){
            if(i+h-1<end){
                merge(i,min(i+deta-1,end),i+h-1);
            }
        }
        h = h*2; //写成deta*2了
        deta = deta*2;
    }
}

void merge(int st,int end,int mid){
    memcpy(miseq,seq,sizeof(int)*n);
    int i=st,j=mid+1,k=st;
    while(i<=mid && j<=end){
        if(miseq[i]<miseq[j])
            seq[k++] = miseq[i++];
        else seq[k++] = miseq[j++];
    }
    int t = (i<=mid) ? i : j;
    while(k<=end){
        seq[k++] = miseq[t++];
    }

}
bool isSame(int s1[],int s2[]){
    for(int i=0;i<n;i++){
        if(s1[i]!=s2[i])
            return false;
    }
    return true;
}


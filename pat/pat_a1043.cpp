#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN = 1010;
struct Node
{
    int key;
    Node *left,*right;
};

bool cmp(int t1,int t2);
Node* buildTree(int st,int ed,int ft,int last,int flag);
void PostOrder(Node *ft);

int preorder[MAXN],inorder[MAXN],postorder[MAXN];
int cnt = 0;
bool notTree = false;
int mirror = 0; //是搜索树还是搜索树的镜像树
int main(int argc, char const *argv[])
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&preorder[i]);
        inorder[i] = preorder[i];
    }
    sort(inorder,inorder+n); //忘记排序
    Node *root = buildTree(0,n-1,0,-1,0);
    // printf("build over\n");
    if(notTree){
        notTree = false;
        mirror = 1;
        reverse(inorder,inorder+n);
        root = buildTree(0,n-1,0,-1,0);

    }
    PostOrder(root);
    if(notTree){
        printf("NO\n");
    }
    else{
        printf("YES\n");
        for(int i=0;i<n;i++){
            if(i) printf(" ");
            printf("%d",  postorder[i])  ; //忘加下标
        }
    }
    return 0;
}

Node* buildTree(int st,int ed,int ft,int last,int flag){ //中序遍历的起始和终止位置，前序遍历的父节点位置
    if(st>ed || notTree) return nullptr;
    if(~last){
        if(!flag){
            if(preorder[last] <= preorder[ft]){
                notTree = true;
                return nullptr;
            }
        }
        else if(preorder[last] > preorder[ft]){
            notTree = true;
            return nullptr;
        }
    }
    // printf("st %d,ed %d,ft %d\n",st,ed,ft);
    int k;
    for(int i=st;i<=ed;i++){
        if(inorder[i]==preorder[ft]){ //i写成k
            k = i;
            break;
        }
    }
    if(inorder[k]!=preorder[ft]){
        notTree = true;
        return nullptr;
    }
    Node *t = new Node();
    t->key = preorder[ft];
    t->left = buildTree(st,k-1,ft+1,ft,0^mirror);
    if(notTree) return nullptr;
    t->right = buildTree(k+1,ed,ft+k-st+1,ft,1^mirror);
    if(notTree) return nullptr;
    return t;
}

void PostOrder(Node *ft){
    if(!ft) return;
    PostOrder(ft->left);
    PostOrder(ft->right);
    postorder[cnt++] = ft->key;
}

bool cmp(int t1,int t2){
    return t1>t2;
}

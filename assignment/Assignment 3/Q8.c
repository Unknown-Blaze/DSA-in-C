#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}


int findarr(char* arr, int val, int low, int high){
    for (int i = low; i <= high; i++){
        if (arr[i] == val) return i;
    }
    return -1;
}

BTNode* build(char* preO, char* postO, int* pre, int post_low, int post_high, int size){
    if (*pre >= size || post_low > post_high) return NULL;
    BTNode* btnode = (BTNode*)malloc(sizeof(BTNode));
    btnode->id = preO[(*pre)++];
    btnode->left = NULL;
    btnode->right = NULL;

    if (*pre < size){
        int curr_post = findarr(postO, preO[*pre], post_low, post_high);
        if (curr_post != -1){
            btnode->left = build(preO, postO, pre, post_low, curr_post, size);
            btnode->right = build(preO, postO, pre, curr_post+1, post_high-1, size);
        }
    }
    return btnode;
} 

void buildTree(BTNode** node, char* preO, char* postO)
{
    int size = 0;
    while (preO[size] != '\0'){
        size++;
    }
    int pre = 0;
    *node = build(preO, postO, &pre, 0, size-1, size);
}
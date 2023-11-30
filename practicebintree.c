#include <stdio.h>
#include <stdlib.h>

typedef struct BTNode{
    int data;
    struct BTNode* left;
    struct BTNode* right;
}BTNode;

typedef struct ListNode{
    BTNode* data;
    struct ListNode* next;
}node;

typedef struct LinkedList{
    int size;
    node* head;
}Stack;

int isEmpty(Stack s){
    if (s.size == 0) return 1;
    return 0;
}

void push(Stack* s, BTNode* btnode){
    
    node* newNode = malloc(sizeof(node));
    newNode->data = btnode;
    newNode->next = s->head;
    s->head = newNode;
    s->size++;
}

BTNode* peek(Stack s){
    if (isEmpty(s)){
        // printf("Stack is empty\n");
        return NULL;
    }
    return s.head->data;
}

void pop(Stack* s){

    if (isEmpty(*s)){
        // printf("Stack is empty\n");
        return;
    }
    node* temp = s->head;
    s->head = s->head->next;
    free(temp);
    s->size--;
}

Stack* createStack(){
    Stack* stack = (Stack *)malloc(sizeof(node));
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

BTNode* createBTree(int data){
    BTNode* bthead = malloc(sizeof(BTNode));
    bthead->data = data;
    bthead->left = NULL;
    bthead->right = NULL;
    return bthead;
}

void insertLeft(BTNode* btroot, int data){
    if (btroot == NULL) {
        printf("Not a valid node.\n");
        return;
    }
    BTNode* btnode = malloc(sizeof(BTNode));
    btnode->data = data;
    btnode->left = NULL;
    btnode->right = NULL;
    btroot->left = btnode;
}

void insertRight(BTNode* btroot, int data){
    if (btroot == NULL) {
        printf("Not a valid node.\n");
        return;
    }
    BTNode* btnode = malloc(sizeof(BTNode));
    btnode->data = data;
    btnode->left = NULL;
    btnode->right = NULL;
    btroot->right = btnode;
}

void preorder(BTNode* root){
    if (root == NULL) return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void preorderIterative(BTNode* root){
    Stack* stack = createStack();
    if (root){
        push(stack, root);
        while(!isEmpty(*stack)){
            BTNode* curr = peek(*stack);
            printf("%d ", curr->data);
            pop(stack);
            if (curr->right) push(stack, curr->right);
            if (curr->left) push(stack, curr->left);  
        }
    }
}

void postorderIterative(BTNode* root){
    if (root == NULL) return;
    Stack* stack = createStack();
    do{
        while(root) {
            if (root->right) push(stack, root->right);
            push(stack, root);
            root = root->left;
        }
        root = peek(*stack);
        pop(stack);

        if (root->right && peek(*stack) == root->right){
            pop(stack);
            push(stack, root);
            root = root->right;
        }else{
            printf("%d ", root->data);
            root = NULL;
        }

    }while(!isEmpty(*stack));
}

void postorderIterative_2s(BTNode* root){
    if (root == NULL) return;
    Stack* stack1 = createStack();
    Stack* stack2 = createStack();

    push(stack1, root);

    while(!isEmpty(*stack1)){
        BTNode* curr = peek(*stack1);
        push(stack2, curr);
        pop(stack1);
        if(curr->left) push(stack1, curr->left);
        if(curr->right) push(stack1, curr->right);
    }

    while(!isEmpty(*stack2)){
        printf("%d ", peek(*stack2)->data);
        pop(stack2);
    }
}

int height(BTNode* node){
    if (node == NULL) return 0;
    
    int l = height(node->left);
    int r = height(node->right);
    return 1 + ((l > r) ? l : r);
}

int main(){
    BTNode* bthead = createBTree(3);
    insertLeft(bthead, 1);
    insertRight(bthead, 2);
    insertLeft(bthead->left, 7);
    insertRight(bthead->left, 4);
    insertRight(bthead->left->right, 5);
    insertLeft(bthead->left->right, 6);
    insertRight(bthead->right, 10);

    // preorder(bthead);
    // printf("\n");
    // preorderIterative(bthead);
    // printf("\n");
    postorderIterative(bthead);
    printf("\n%d\n", height(bthead->left));
    postorderIterative_2s(bthead);

        /*
                        3
                1               2
              7   4               10
                 6 5           
    
    */

}
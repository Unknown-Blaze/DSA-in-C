#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList{
    int size;
    struct ListNode* head;
    struct ListNode* tail;
}Queue;

typedef struct BTNode{
    int data;
    struct BTNode* left;
    struct BTNode* right;
}BTNode;

typedef struct ListNode{
    BTNode* data;
    struct ListNode* next;
}queueNode;

// All Queue Functions

Queue* createQueue(){
    Queue* queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

int isEmpty(Queue* queue){
    if (queue->tail == NULL || queue->size == 0) return 1;
    return 0;
}

BTNode* getFront(Queue* queue){
    if (isEmpty(queue)) return 0;
    return queue->head->data;
}

void enqueuebt(Queue* queue, BTNode* data){
    queueNode* newNode = malloc(sizeof(queueNode));
    if (newNode == NULL) {
        printf("Overflow!\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;
    
    if (queue->head == NULL){
        queue->tail = newNode;
    }else{
        queue->head->next = newNode;
    }
    queue->head = newNode;
    queue->size++;
}

void dequeue(Queue* queue){
    if (queue->tail == NULL){
        printf("Underflow!\n");
        return;
    }
    queueNode* temp = queue->tail;
    queue->tail = queue->tail->next;
    free(temp);
    queue->size--;
}

// Binary Tree Functions

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

void preorderTraversal(BTNode* bthead){
    BTNode* cur = bthead;
    if (cur == NULL) return;

    preorderTraversal(cur->left);
    printf("%d ", cur->data);
    preorderTraversal(cur->right);
}

void inorderTraversal(BTNode* bthead){
    BTNode* cur = bthead;
    if (cur == NULL) return;

    printf("%d ", cur->data);
    inorderTraversal(cur->left);
    inorderTraversal(cur->right);
}

void postorderTraversal(BTNode* bthead){
    BTNode* cur = bthead;
    if (cur == NULL) return;
    
    postorderTraversal(cur->left);
    postorderTraversal(cur->right);
    printf("%d ", cur->data);
}

void searchNode(BTNode* bthead, int data){

    BTNode* cur = bthead;
    if (cur == NULL) return;
    if (cur->data == data) {
        printf("Yes, node found\n");
        return;
    };
    searchNode(bthead->left, data);
    searchNode(bthead->right, data);
    return;
}

void findgrandchildren(BTNode *cur, int c, int k){
    if (cur == NULL) return;
    if (c == k){
        printf("%d ", cur->data);
        return;
    }
    if (c < k){
        findgrandchildren(cur->left, c+1, k);
        findgrandchildren(cur->right, c+1, k);
    }
}

void bft(BTNode* bthead){
    Queue* queue;
    BTNode* node;

    queue = createQueue();

    if (bthead){
        enqueuebt(queue, bthead);
        while(!(isEmpty(queue))){
            node = getFront(queue);
            printf("%d ", node->data);
            dequeue(queue);
            if (node->left) enqueuebt(queue, node->left);
            if (node->right) enqueuebt(queue, node->right);
        }
    }
}



int countNode(BTNode *cur){
    if (cur == NULL) return 0;
    return (countNode(cur->left) + countNode(cur->right) + 1);
}

int main(){

    // Queue* queue = createQueue();
    // enqueue(queue, 1);
    // enqueue(queue, 2);
    // enqueue(queue, 3);
    // enqueue(queue, 4);
    // printf("%d\n", getFront(queue));
    // dequeue(queue);
    // printf("%d\n", getFront(queue));
    // dequeue(queue);
    // printf("%d\n", getFront(queue));
    // dequeue(queue);
    // printf("%d\n", getFront(queue));
    // dequeue(queue);
    // printf("%d\n", getFront(queue));
    // dequeue(queue);
    // printf("%d\n", getFront(queue));

    Queue* bintreeQueue = createQueue();
    BTNode* bthead = createBTree(3);
    insertLeft(bthead, 1);
    insertRight(bthead, 2);
    insertLeft(bthead->left, 7);
    insertRight(bthead->left, 4);
    insertRight(bthead->left->right, 5);
    insertLeft(bthead->left->right, 6);
    insertRight(bthead->right, 10);

    // preorderTraversal(bthead);
    // printf("\n");
    // inorderTraversal(bthead);
    // printf("\n");
    postorderTraversal(bthead);
    printf("\n");

    // searchNode(bthead, 10);
    // printf("%d\n", countNode(bthead));

    // findgrandchildren(bthead, 0, 2);
    bft(bthead)
;

    /*
                        3
                1               2
              7   4               10
                 6 5           
    
    
    
    
    */

    return 0;
}













#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}
void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}


int existsInTree(BTNode* root, int item){
    if (root == NULL) return 0;
    if (root->nodeV == item) return 1;
    if(existsInTree(root->left, item)) return 1;
    if(existsInTree(root->right, item)) return 1;
    return 0;

}

BTNode* findNode(BTNode* node, int item, int* sum){
    if (node == NULL) return NULL;
    *sum += node->nodeV;
    if (node->nodeV == item) return node;
    if (existsInTree(node->left, item)){
        node = node->left;
        return findNode(node, item, sum);
    }else if(existsInTree(node->right, item)){
        node = node->right;
        return findNode(node, item, sum);
    }
    return NULL;
}

BTNode* betterFindNode(BTNode* node, int item){
    if (node == NULL) return NULL;
    
    if (node->nodeV == item) return node;

    BTNode* l = betterFindNode(node->left, item);
    BTNode* r = betterFindNode(node->right, item);

    if (l) return l;
    return r;
}



BTNode* common(BTNode* node, int nodeV1, int nodeV2){
    if (node == NULL) return NULL;
    if (node->nodeV == nodeV1 || node->nodeV == nodeV2) return node;

    BTNode* left = common(node->left, nodeV1, nodeV2);
    BTNode* right = common(node->right, nodeV1, nodeV2);

    if (left != NULL && right != NULL) return node;
    if (left != NULL) {
        return left;
    }else{
        return right;
    }
}

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{

    BTNode* commonNode = common(node, nodeV1, nodeV2);

    if (commonNode == NULL) return 0;
    
    int sum = 0;
    findNode(commonNode, nodeV1, &sum);
    findNode(commonNode, nodeV2, &sum);
    return sum - commonNode->nodeV;
}
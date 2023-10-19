#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}

BTNode* createNode(int item) {
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void createExpTree(BTNode** root, char* prefix) {
    int i = 0;
    createExpTreeWithIndex(root, prefix, &i);
}

void createExpTreeWithIndex(BTNode** root, char* prefix, int* i) {

    while (prefix[*i] == ' '){
        (*i)++;
    }
    char op[4];
    int index = 0;

    while (prefix[*i] != ' ' && prefix[*i] != '\0') {
        op[index] = prefix[*i];
        (*i)++;
        index++;
    }
    op[index] = '\0';

    if (op[0] >= '0' && op[0] <= '9') {
        int operandValue = atoi(op);
        *root = createNode(operandValue);
    } else if (op[1] == '\0' && (op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/')) {
        *root = createNode(op[0]*-1);
        (*i)++; 
        createExpTreeWithIndex(&((*root)->left), prefix, i);
        createExpTreeWithIndex(&((*root)->right), prefix, i);
    }
}

void printTree(BTNode* node) {
    if (node == NULL) return;

    printTree(node->left);

    if (node->item < 0){
        printf("%c ", (char)(node->item*-1));
    }else{
        printf("%d ", node->item);
    }

    printTree(node->right);
}


void printTreePostfix(BTNode* node) {
    if (node == NULL) return;

    printTreePostfix(node->left);
    printTreePostfix(node->right);

    if (node->item < 0){
        printf("%c ", (char)(node->item*-1));
    }else{
        printf("%d ", node->item);
    }
}

double computeTree(BTNode* node) {
    if (node == NULL) return 0.0;
    double answer = 0;

    if (node->item > 0) {
        return node->item;
    }

    switch ((char)(node->item*-1)) {
        case '+':
            answer += computeTree(node->left) + computeTree(node->right);
            break;
        case '-':
            answer += computeTree(node->left) - computeTree(node->right);
            break;
        case '*':
            answer += computeTree(node->left) * computeTree(node->right);
            break;
        case '/':
            answer += computeTree(node->left) / computeTree(node->right);
            break;
        default:
            break;
    }
    return answer;
}
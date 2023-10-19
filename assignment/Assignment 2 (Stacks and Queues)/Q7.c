#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

int getPrio(char opt){
    switch(opt){
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 2;
            break;
        case '/':
            return 2;
            break;
        default:
            return 0;
    }
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{

    LinkedList expression;
    expression.head = NULL;
    expression.size = 0;
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->size = 0;

    int len = 0;
    while (infix[len] != '\0'){
        len++;
    }
    int flag = 0;

    char str[len+1];
    int str_index = 0;
    for(int i = 0; i < len; i++){
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%' || infix[i] == '(' || infix[i] == ')'){
            flag = 0;
            str[str_index] = '\0';
            if (str_index != 0) insertNode(&expression, atoi(str), OPERAND);
            insertNode(&expression, infix[i], OPT);
            
            str_index = 0;
        }
        else{
            flag = 1;
            str[str_index] = infix[i];
            str_index++;
        }
    }
    str[str_index] = '\0';
    if (flag){
        insertNode(&expression, atoi(str), OPERAND);
    }
    ListNode* ptr = expression.head;

    
    // inExpLL->head = expression.head;
    // return;
    // ListNode* ptr = expression.head;
    ptr = expression.head;
    while (ptr != NULL){
        if (ptr->item == '('){
            ptr->item = ')';
        }else if(ptr->item == ')'){
            ptr->item = '(';
        }
        ptr = ptr->next;
    }

    ptr = expression.head;

    for (int i = 1; i <= expression.size; i++){
        int llitem = ptr->item;
        if (ptr->type == OPERAND){
            insertNode(inExpLL, llitem, OPERAND);
        }else if(llitem == '('){
            push(stack, llitem);
        }else if(llitem == ')'){
            while(!isEmptyStack(*stack) && peek(*stack) != '('){
                insertNode(inExpLL, peek(*stack), OPT);
                pop(stack);
            }
            pop(stack);
        }else if(ptr->type == OPT){

            if (!isEmptyStack(*stack) && getPrio(llitem) < getPrio(peek(*stack))){
                while(!isEmptyStack(*stack) && getPrio(peek(*stack)) > getPrio(llitem)){
                    insertNode(inExpLL, peek(*stack), OPT);
                    pop(stack);
                }
            }
            push(stack, llitem);
        }
        ptr = ptr->next;
    }
    
    while (!isEmptyStack(*stack)){
        insertNode(inExpLL, peek(*stack), OPT);
        pop(stack);
    }
    return;
  //Write your code here

}


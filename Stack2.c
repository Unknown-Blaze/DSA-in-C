#include <stdio.h>
#include <stdlib.h>

typedef struct listNode{
    int data;
    struct ListNode* next;
} stackNode;

typedef struct linkedList{
    stackNode* head;
    int size;
}Stack;

int isEmpty(Stack s){
    if (s.size == 0) return 1;
    if (s.head == NULL) return 1;
    return 0;
}

void push(Stack* s, int data){
    
    stackNode* newNode = malloc(sizeof(stackNode));
    newNode->data = data;
    newNode->next = s->head;
    s->head = newNode;
    s->size++;
}

int peek(Stack s){
    if (isEmpty(s)){
        printf("Stack is empty\n");
        return -1;
    }
    return s.head->data;
}

void pop(Stack* s){

    if (isEmpty(*s)){
        printf("Stack is empty\n");
        return;
    }
    stackNode* temp = s->head;
    s->head = s->head->next;
    free(temp);
    s->size--;
}

Stack createStack(){
    Stack stack;
    stack.head = malloc(sizeof(stackNode));
    stack.size = 0;
    return stack;
}

int main(){

    Stack stack = createStack();
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3); // 3, 2, 1
    printf("%d\n", isEmpty(stack)); // 0
    printf("%d\n", peek(stack)); // 3
    pop(&stack);
    printf("%d\n", peek(stack)); // 2
    pop(&stack);
    printf("%d\n", peek(stack)); // 1
    pop(&stack);
    printf("%d\n", peek(stack)); // -1
    pop(&stack);
    printf("%d\n", peek(stack)); // -1

    Stack stack2;
    stack2.head = malloc(sizeof(stackNode));

    printf("%d\n", peek(stack2));

    return 0;
}
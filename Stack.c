#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* nextPtr;
} node;

void print_data(node* top){
    node* ptr = top;
    if (ptr == NULL){
        printf("Stack is empty\n");
        return;
    }
    printf("The Stack is: ");
    while(ptr != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->nextPtr;
    }
    printf("\n");
}
int count_nodes(node* top){
    node* ptr = top; 
    if (ptr == NULL){
        printf("Stack is empty\n");
        return 0;
    }
    int count = 0;
    while(ptr != NULL){
        ptr = ptr->nextPtr;
        count++;
    }
    return count;
}
void push(node** top, int data){
    node* ptr = (node *)malloc(sizeof(node));
    ptr->data = data;
    ptr->nextPtr = *top;
    *top = ptr;
}

void pop(node**top){
    if (*top == NULL) {
        printf("Warning: Stack Underflow\n");
        return;
    }
    node* temp = *top;
    *top = (*top)->nextPtr;
    free(temp);
}

int main(){

    node* top = malloc(sizeof(node));
    top->data = 1;
    top->nextPtr = NULL;

    print_data(top);
    push(&top, 2);
    push(&top, 3);
    push(&top, 4);
    push(&top, 5);
    push(&top, 6);
    
    // print_data(top);
    printf("%d", count_nodes(top));

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int x;
    struct node* next;
}node;

node* front;

void print_data(node* rear){
    node* ptr = rear;
    if (ptr == NULL){
        printf("Queue is empty\n");
        return;
    }
    printf("The Queue is: ");
    while(ptr != NULL){
        printf("%d ", ptr->x);
        ptr = ptr->next;
    }
    printf("\n");
}

void append(node** rear, int x){

    node* ptr = malloc(sizeof(node));
    if (ptr == NULL){
        printf("Error: Overflow");
        return;
    }else{
        if(front == NULL){
            *rear = ptr;
            front = ptr;
        }else{
            ptr->next = *rear;
            *rear = ptr;
        }
        ptr->x = x;
    }
}
void delete(node** front){

}

int main(){

    node* rear = malloc(sizeof(node));
    
    append(&rear, 1);
    append(&rear, 2);
    append(&rear, 1);
    append(&rear, 2);

    print_data(rear);


    return 0;
}
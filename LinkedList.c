#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_circular = 0;

typedef struct node{
    int x;
    int y;
    struct node *next;
} node;

void free_all(node* head){
    node* ptr = head;
    node* temp = head;
    while (ptr != NULL){
        ptr = ptr->next;
        free(temp);
        node* temp = ptr;
    }
}

int count_nodes(node* head){
    if (head == NULL) {
        printf("Linked List is Empty\n");
        return 0;
    }
    int count = 0;
    node* ptr = head;
    do {
        count++;
        ptr = ptr->next;
    }while(ptr != NULL && ptr != head);

    return count;
}

void print_data(node* head){
    if (head == NULL) {
        printf("Linked List is empty\n");
        return;
    }
    node* ptr = head;
    do{
        // printf("x, y: %d, %d\n", ptr->x, ptr->y);
        printf("(%d, %d) ", ptr->x, ptr->y);
        ptr = ptr->next;
    }while(ptr != NULL && ptr != head);
    printf("\n");
}

void append_node(node* head, int x, int y){

    node* ptr = head;
    if (is_circular == 1){
        printf("Cannot append to a circular Linked List.\n");
        return;
    }
    while (ptr->next != NULL){
        ptr = ptr->next;
    }

    node* current = malloc(sizeof(node));
    current->x = x;
    current->y = y;
    ptr->next = current;
    current->next = NULL;
}

void add_to_start(node** head, int x, int y ){
    // **head coz of pass by reference  
    node* new_head = malloc(sizeof(node));
    new_head->x = x;
    new_head->y = y;
    new_head->next = *head;
    *head = new_head;
}

void insert_node(node** head, int index, int x, int y){
    
    int n = count_nodes(*head);
    if (index == 1) add_to_start(head, x, y);
    else if (n < index){
        append_node(*head, x, y);
        printf("Index out of bounds, node appended instead.\n");
    }else if (n == index){
        append_node(*head, x, y);
    }else{
        node* ptr = *head;

        for (int i = 0; i < index-1; i++){
            ptr = ptr->next;
        }
        node* ptr2 = ptr->next;
        
        node* current = malloc(sizeof(node));
        current->x = x;
        current->y = y;
        current->next = ptr2;
        ptr->next = current;
    }
}

void delete_node(node** head, int index){

    int n = count_nodes(*head);

    if (index == 0){
        node* temp = *head;
        *head = (*head)->next;
    }else if (index >= n){
        printf("Error: Index passed larger than length of linked list.\
        Pass an index from 0 to %d\n", n-1);
        return;
    }else{
        node* ptr = *head;

        for (int i = 0; i < index-1; i++){
            ptr = ptr->next;
        }
        node* temp = ptr->next;

        if (index == n-1) {
            ptr->next = NULL;
        }else{
            ptr->next = ptr->next->next;
        }

        free(temp);
        temp = NULL;
    }
}

node* pop(node** head){
    node* temp;
    if (*head == NULL){
        return NULL;
    }else if((*head)->next == NULL){
        temp = *head;
        *head = NULL;
        free(temp);
        return NULL;
    }else{
    node* ptr = *head;
    int n = count_nodes(*head);
        for (int i = 0; i < n-2; i++){
            ptr = ptr->next;
        }
        node* temp = ptr->next;
        node* ret = malloc(sizeof(node *));
        ret->x = temp->x;
        ret->y = temp->y;
        ptr->next = NULL;
        free(temp);
        return ret;
    }
    
}

void concat(node** head1, node* head2){
    
    node* temp;
    if (*head1 == NULL){
        temp = *head1;
        *head1 = head2;
    }else if (head2 == NULL){
        return;
    }else{
        int n = count_nodes(*head1);
        node* ptr = *head1;
        for (int i = 0; i < n-1; i++){
            ptr = ptr->next;
        }
        ptr->next = head2;
    }
}

void make_circular(node** head){
    node* ptr = *head;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = *head;
    is_circular = 1;
}

void value_at_index(node* head, int index){
    node* ptr = head;
    int n = count_nodes(head);
    if (index < 0){
        while (index < 0) index += n;
    }
    if (index >= n){
        printf("Error: index is greater than length of Linked List. Please use between 0 and %d\n", n-1);
        return;
    }
    for (int i = 0; i < index; i++){
        ptr = ptr->next;
    }
    printf("(%d, %d)\n", ptr->x, ptr->y);
}

int find_value_x(node* head, int value){
    
    node* ptr = head;
    int count = 0;
    while (ptr->next != NULL && ptr->x != value){
        ptr = ptr->next;
        count++;
    }
    if (ptr->x == value) return count;
    else if (ptr->next->x == value) return count+1;
    else{
        return -1;
    }
}
int find_value_y(node* head, int value){
    
    node* ptr = head;
    int count = 0;
    while (ptr->next != NULL && ptr->y != value){
        ptr = ptr->next;
        ++count;
    }
    if (ptr->y == value) return count;
    else if (ptr->next->y == value) return count+1;
    else{
        return -1;
    }
}

int main(){

    node *head = malloc(sizeof(node));

    head->x = 1;
    head->y = 2;
    head->next = NULL;

    node* current = malloc(sizeof(node));
    current->x = 3; 
    current->y = 4;
    current->next = NULL;
    head->next = current;

    current = malloc(sizeof(node));
    current->x = 5;
    current->y = 6;
    current->next = NULL;
    head->next->next = current;

    node *head2 = malloc(sizeof(node));

    head2->x = 100;
    head2->y = 200;
    head2->next = NULL;

    node* current2 = malloc(sizeof(node));
    current2->x = 300; 
    current2->y = 400;
    current2->next = NULL;
    head2->next = current2;

    current2 = malloc(sizeof(node));
    current2->x = 500;
    current2->y = 600;
    current2->next = NULL;
    head2->next->next = current2;
 
    // printf("%d", count_nodes(head));
    // print_data(head);


    // Trying out stuff
    
    // append_node(head, 7, 8);
    // add_to_start(&head, 9, 10);
    // insert_node(&head, 2, 11, 12);
    // print_data(head);
    // printf("\n\n\n");

    // delete_node(&head, 2);
    // print_data(head);

    // printf("\n\n\n");
    // print_data(head);
    // printf("\n\n");
    // print_data(head2);
    // printf("\n\n\n");
    concat(&head, head2);
    // int n = count_nodes(head);
    // for (int i = 0; i < n; i++){
    //     pop(&head);
    //     print_data(head);
    //     printf("\n");
    // }

    // make_circular(&head);
    // printf("%d\n", count_nodes(head));
    // print_data(head);
    // print_data(head);
    // value_at_index(head, -2);
    print_data(head);
    printf("%d\n", find_value_y(head, 400));
    node* popped = pop(&head);
    printf("(%d, %d)\n", popped->x, popped->y);
    print_data(head);

    return 0;
}
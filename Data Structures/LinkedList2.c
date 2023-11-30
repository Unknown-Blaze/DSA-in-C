#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_circular = 0;

typedef struct node{
    int x;
    int y;
    struct node *next;
} node;

typedef struct LinkedList{
    node* head;
    int size;
} LinkedList;

void free_all(LinkedList ll){
    node* ptr = ll.head;
    node* temp = ll.head;
    while (ptr != NULL){
        ptr = ptr->next;
        free(temp);
        node* temp = ptr;
    }
    ll.size = 0;
    ll.head = NULL;
}

int count_nodes(LinkedList ll){
    return ll.size;
}

void print_data(LinkedList ll){
    if (ll.head == NULL) {
        printf("Linked List is empty\n");
        return;
    }
    node* ptr = ll.head;
    do{
        // printf("x, y: %d, %d\n", ptr->x, ptr->y);
        printf("(%d, %d) ", ptr->x, ptr->y);
        ptr = ptr->next;
    }while(ptr != NULL && ptr != ll.head);
    printf("\n");
}

void append_node(LinkedList* ll, int x, int y){

    node* ptr;
    if (ll->head == NULL){
        ll->head = malloc(sizeof(node));
        ptr = ll->head;
        ptr->next = NULL;
    }else{
        ptr = ll->head;
    }

    if (is_circular){
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
    ll->size++;
}

void add_to_start(LinkedList* ll, int x, int y ){

    node* new_head = malloc(sizeof(node));
    new_head->x = x;
    new_head->y = y;
    new_head->next = ll->head;
    ll->head = new_head;

    ll->size++;
}

void insert_node(LinkedList* ll, int index, int x, int y){
    
    int n = ll->size;
    if (index == 1) add_to_start(ll, x, y);
    else if (n < index){
        append_node(ll, x, y);
        printf("Index out of bounds, node appended instead.\n");
    }else if (n == index){
        append_node(ll, x, y);
    }else{
        node* ptr = ll->head;

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
    ll->size++;
}

void delete_node(LinkedList* ll, int index){

    int n = ll->size;

    if (index == 0){
        node* temp = ll->head;
        ll->head = ll->head->next;
    }else if (index >= n){
        printf("Error: Index passed larger than length of linked list.\
        Pass an index from 0 to %d\n", n-1);
        return;
    }else{
        node* ptr = ll->head;

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
    }
    ll->size--;
}

node* pop(LinkedList* ll){
    node* temp;
    if (ll->head == NULL){
        return NULL;
    }else if((ll->head)->next == NULL){
        temp = ll->head;
        ll->head = NULL;
        free(temp);
        ll->size--;
        return NULL;
    }else{
    node* ptr = ll->head;
    int n = ll->size;
        for (int i = 0; i < n-2; i++){
            ptr = ptr->next;
        }
        node* temp = ptr->next;
        node* ret = malloc(sizeof(node *));
        ret->x = temp->x;
        ret->y = temp->y;
        ptr->next = NULL;
        free(temp);
        ll->size--;
        return ret;
    }
}

void concat(LinkedList* ll1, LinkedList* ll2){
    
    node* temp;
    if (ll1->head == NULL){
        temp = ll1->head;
        ll1->head = ll2->head;
    }else if (ll2->head == NULL){
        return;
    }else{
        int n = ll1->size;
        node* ptr = ll1->head;
        for (int i = 0; i < n-1; i++){
            ptr = ptr->next;
        }
        ptr->next = ll2->head;
    }
    ll1->size += ll2->size; 
}

void make_circular(LinkedList* ll){
    node* ptr = ll->head;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = ll->head;
    is_circular = 1;
}

void value_at_index(LinkedList ll, int index){
    node* ptr = ll.head;
    int n = ll.size;
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

int find_value_x(LinkedList ll, int value){
    
    node* ptr = ll.head;
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
int find_value_y(LinkedList ll, int value){
    
    node* ptr = ll.head;
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

LinkedList createll(){
    LinkedList ll;
    ll.size = 0;
    ll.head = NULL;
    return ll;
}

int main(){

    LinkedList ll = createll();
    ll.size = 0;
    node *head = malloc(sizeof(node));
    ll.head = head;
    

    head->x = 1;
    head->y = 2;
    head->next = NULL;
    ll.size++;

    append_node(&ll, 3, 4);
    append_node(&ll, 5, 6);


    node *head2 = malloc(sizeof(node));
    LinkedList ll2 = createll();
    ll2.head = head2;
    head2->x = 100;
    head2->y = 200;
    head2->next = NULL;
    ll2.size++;

    append_node(&ll2, 300, 400);
    append_node(&ll2, 500, 600);
 
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
    // concat(&head, head2);
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
    // print_data();
    // printf("%d\n", find_value_y(head, 400));
    // node* popped = pop(&head);
    // printf("(%d, %d)\n", popped->x, popped->y);
    print_data(ll);
    print_data(ll2);
    concat(&ll, &ll2);
    print_data(ll);
    for (int i = 0; i < 6; i++){
        pop(&ll);
        print_data(ll);
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int data;
    struct ListNode* next;
} queueNode;

typedef struct LinkedList{
    int size;
    queueNode* tail;
    queueNode* head;
} Queue;

int isEmpty(Queue queue){
    if (queue.size == 0) return 1;
    return 0;
}

int getFront(Queue queue){
    if (isEmpty(queue)) return 0;
    return queue.tail->data;
}

// Queues: Add to head and remove from tail.
// Queue structure: head - - - - - - - - - - - - tail.
void enqueue(Queue* queue, int data){
    queueNode* newNode = malloc(sizeof(queueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (queue->tail == NULL){
        queue->tail = newNode;
    }else{
        queue->head->next = newNode;
    }
    queue->head = newNode;
    queue->size++;
}

void dequeue(Queue* queue){
    if (isEmpty(*queue)){
        printf("Underflow!\n");
        return;
    }
    queueNode* temp = queue->tail;
    queue->tail = queue->tail->next;
    free(temp);
    queue->size--;
}

Queue* createQueue(){
    Queue* queue = malloc(sizeof(Queue));
    queue->tail = NULL;
    queue->head = NULL;
    queue->size = 0;
    return queue;
}

int main(){

    Queue* queue = createQueue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    printf("%d\n", getFront(*queue));
    dequeue(queue);
    printf("%d", getFront(*queue));
    dequeue(queue);
    printf("%d", getFront(*queue));
    dequeue(queue);
    printf("%d", getFront(*queue));
    return 0;
}
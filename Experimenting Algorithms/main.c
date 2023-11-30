#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 1000

typedef struct _queueNode
{
    int item;
    struct _queueNode *next;
}QueueNode;

typedef struct _queue{
    int size;
    QueueNode *head;
    QueueNode *tail;
}Queue;

typedef struct _stackNode{
    int item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, int item);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);

void enqueue (Queue *qptr, int item);
int dequeue(Queue *qPtr);
QueueNode* getFront(Queue q);
int isEmptyQueue(Queue q);

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

void bfs(Graph g){
    int start = -1;
    for (int i = 0; i < g.V; i++){
        for (int j = 0; j < g.V; j++)
            if (g.matrix[i][j] == 1){
                start = i+1;
                break;
            }
        if (start != -1) break;    
    }           

    if (start == -1) {
        printf("No valid node found");
        return;
    }
    Queue* q = (Queue *)malloc(sizeof(Queue));
    q->head = NULL;
    q->size = 0;
    q->tail = NULL;

    g.visited[start-1] = 1;
    enqueue(q, start);
    while (!isEmptyQueue(*q)){
        int curr = getFront(*q)->item;
        dequeue(q);
        printf("%d ", curr);

        for (int i = 1; i <= g.V; i++){
            if (g.matrix[curr-1][i-1] == 1 && g.visited[i-1] != 1){
                g.visited[i-1] = 1;
                enqueue(q, i);
            }
        }
    }
}

void dfs(Graph g){
    int start = -1;
    for (int i = 0; i < g.V; i++){
        for (int j = 0; j < g.V; j++){
            if (g.matrix[i][j] == 1){
                start = i+1;
                break;
            }
        }
        if (start != -1) break;
    }
    if (start == -1) {
        printf("Graph is empty");
        return;
    }

    Stack* s = (Stack *)malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;

    push(s, start);
    g.visited[start-1] = 1;

    while (!isEmptyStack(*s)){
        int curr = peek(*s);
        pop(s);
        printf("%d ", curr);
        for (int i = 1; i <= g.V; i++){
            if (g.matrix[curr-1][i-1] == 1 && g.visited[i-1] != 1){
                g.visited[i-1] = 1;
                push(s, i);
            }
        }
    }
}

void dfs_util(Graph g, int start){
    g.visited[start-1] = 1;
    printf("%d ", start);
    for(int i = 1; i <= g.V; i++){
        if (g.matrix[start-1][i-1] == 1 && !g.visited[i-1]){
            dfs_util(g, i);
        }
    }
}

void dfs_recursive(Graph g){
    int start = -1;
    for (int i = 0; i < g.V; i++){
        for (int j = 0; j < g.V; j++){
            if (g.matrix[i][j] == 0){
                start = i+1;
                break;
            }
        }
        if (start != -1) break;
    }
    if (start == -1){
        printf("Graph not found");
        return;
    }
    dfs_util(g, start);
}


void sd(Graph g, int start, int end) {
    if (start < 0 || start >= g.V || end < 0 || end >= g.V) {
        printf("Invalid start or end node\n");
        return;
    }

    int distances[g.V];
    for (int i = 0; i < g.V; i++) {
        distances[i] = -1;  // Initialize distances as -1 (unreachable)
        g.visited[i] = 0;   // Reset visited array
    }

    Queue* q = (Queue *)malloc(sizeof(Queue));
    q->head = NULL;
    q->size = 0;
    q->tail = NULL;

    g.visited[start] = 1;
    distances[start] = 0;  // Distance to start node is 0
    enqueue(q, start);

    while (!isEmptyQueue(*q)) {
        int curr = getFront(*q)->item;
        dequeue(q);

        // If the target node is reached, break out of the loop
        if (curr == end) {
            break;
        }

        for (int i = 0; i < g.V; i++) {
            if (g.matrix[curr][i] == 1 && g.visited[i] != 1) {
                g.visited[i] = 1;
                distances[i] = distances[curr] + 1;
                enqueue(q, i);
            }
        }
    }

    if (distances[end] != -1) {
        printf("Shortest path length from %d to %d is %d\n", start + 1, end + 1, distances[end]);
    } else {
        printf("No path exists from %d to %d\n", start + 1, end + 1);
    }

    // Free the queue and other resources if necessary
}


int main()
{
    Graph g;
    int i,j;
    

    // printf("Enter the number of vertices:\n");
    // scanf("%d",&g.V);
    g.V = 5;

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
	
    g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) 
        g.visited[i] = 0;
    
    // printf("Give matrix: \n");

    // for (i = 0; i < g.V; i++)
    //     for (j = 0; j < g.V; j++)
    //         scanf("%d",& g.matrix[i][j]);
    g.matrix[0][1] = 1;
    g.matrix[0][2] = 1;
    g.matrix[1][3] = 1;
    g.matrix[2][3] = 1;
    g.matrix[3][4] = 1;
    // g.matrix[1][0] = 1;
    // g.matrix[2][0] = 1;
    // g.matrix[3][1] = 1;
    // g.matrix[3][2] = 1;
    // g.matrix[4][3] = 1;
    // scanf("%*c");
    
    sd(g, 0, 4);
    // bfs(g);
    // printf("\n");
    // dfs(g);
    // dfs_recursive(g)
    // printf("%d", isCyclic(g));

    return 0;
}

void enqueue (Queue *qPtr, int item)
{
    QueueNode *newNode;
    newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail =newNode;
    qPtr->size++;

}
int dequeue(Queue *qPtr)
{
    if(qPtr == NULL || qPtr->head ==NULL)
        return 0;
    else{
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;

        if(qPtr->head == NULL)
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

QueueNode* getFront(Queue q)
{
    return q.head;
}

int isEmptyQueue(Queue q){
   if(q.size==0) return 1;
    else return 0;
}

void push(Stack *sPtr, int item){
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

int peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}


int numMountainPairs(CDblLinkedList CDLL)
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail

    int count = 1;
    CDblListNode* ptr1 = CDLL.head->next;
    CDblListNode* head_ptr = CDLL.head;
    while(ptr1 != head_ptr){
        ptr1 = ptr1->next;
        count++;
    }
    if (count <= 1) return 0;
    if (count == 2) return 1;
    if (count == 3) return 3; 

    count = 0;
    CDblListNode* ptr2 = ptr1->next;

    do{
        while (ptr2 != ptr1){
            if (ptr1 == ptr2->next || ptr1 == ptr2->pre) {
                count++;
            }else{
                int min = (ptr1->item > ptr2->item) ? ptr2->item : ptr1->item;
                CDblListNode* ptrmove = ptr2->next;
                int add = 0;
                while (ptrmove != ptr1) {
                    if (ptrmove->item <= min) {
                        ptrmove = ptrmove->next;
                    }else{
                        break;
                    }
                }
                if (ptrmove == ptr1) add = 1;
                if (add == 0){
                    ptrmove = ptr2->pre;
                    while (ptrmove != ptr1) {
                        if (ptrmove->item <= min) {
                            ptrmove = ptrmove->pre;
                        }else{
                            break;
                        }
                    }
                    if (ptrmove == ptr1) add = 1;
                }
                count += add;
                
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr1->next;
    }while(ptr1 != head_ptr);
        
    return count/2;
// Write your code here
}
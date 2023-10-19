#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}


ListNode *reverseSegment(ListNode* head, int start, int end)
{
// Write your code here

	if (head == NULL) {
        printf("Linked List is Empty\n");
        return NULL;
    }
    int count = 0;
    ListNode* ptr = head;
    while(ptr != NULL){
        ptr = ptr->next;
		count++;
    }

	if (start >= count || end >= count || start >= end || start < 0 || end < 0){
		return head;
	}else if(start == 0 && end == count-1){
		ListNode *prevNode = NULL;
    	ListNode *currentNode = head;

    while (currentNode != NULL) {
        ListNode* nodeNext = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nodeNext;
    }

    return head;
	}

	ListNode* prevNode = NULL;
	ListNode* currentNode = head;
	ListNode* end1;
	for (int i = 0; i < start-1; i++){
		currentNode = currentNode->next;
	}
	end1 = currentNode;
	currentNode = currentNode->next;
	ListNode* start2 = head;
	for (int i = 0; i < end; i++){
		start2 = start2->next;
	}
	if (start2->next != NULL){
		start2 = start2->next;
	}else{
		start2 = NULL;
	}

	for (int i = start; i <= end; i++){
		ListNode* nodeNext = currentNode->next;
		if(prevNode == NULL){
			currentNode->next = start2;
		}else{
			currentNode->next = prevNode;
		}
		prevNode = currentNode;
		currentNode = nodeNext;
	}
	if (start != 0) end1->next = prevNode;

	return head;
}
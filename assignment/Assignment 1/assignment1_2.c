#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}


void append_node(LinkedList* ll, int item){

    ListNode* ptr;
    if (ll->size == 0){
        ll->head = (ListNode*)malloc(sizeof(ListNode));
        ptr = ll->head;
        ptr->next = NULL;
		ptr->item = item;
		ll->size = 1;
		return;
    }else{
        ptr = ll->head;
    }

    while (ptr->next != NULL){
        ptr = ptr->next;
    }

    ListNode* current = (ListNode*)malloc(sizeof(ListNode));
    current->item = item;
    ptr->next = current;
    current->next = NULL;
    ll->size++;
}

LinkedList rearrange (LinkedList ll){
// Write your code here
	if (ll.head == NULL || ll.head->next == NULL || ll.size <= 0) return ll;
	ListNode* ptr = ll.head;

	LinkedList ll1;
	ll1.size = 0;
	ListNode* head1 = (ListNode*)malloc(sizeof(ListNode));
	ll1.head = head1;
	ListNode* ptr1 = head1;

	LinkedList ll2;
	ll2.size = 0;
	ListNode* head2 = (ListNode*)malloc(sizeof(ListNode));
	ll2.head = head2;
	ListNode* ptr2 = head2;

	int count = 0;
	while(ptr != NULL){
		count++;
		ptr = ptr->next;
	}
	ptr = ll.head;
	for (int i = 0; i < count/2; i++){
		if (i == 0){
			head1->item = ptr->item;
			head1->next = NULL;
		}else{
			ListNode* new1 = (ListNode*)malloc(sizeof(ListNode));
			new1->item = ptr->item;
			new1->next = NULL;
			ptr1->next = new1;
			ptr1 = ptr1->next;
		}
		ptr = ptr->next;
		ll1.size++;
	}
	for (int i = count/2; i < count; i++){
		if (i == count/2){
			head2->item = ptr->item;
			head2->next = NULL;
		}else{
			ListNode* new2 = (ListNode*)malloc(sizeof(ListNode));
			new2->item = ptr->item;
			new2->next = NULL;
			ptr2->next = new2;
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
		ll2.size++;
	}

	ptr2 = ll2.head;
	ptr1 = ll1.head;

	LinkedList rll;
	rll.size = 0;


	for (int i = 0; i < count; i++){
		if (i % 2 != 0){
			append_node(&rll, ptr1->item);
			ptr1 = ptr1->next;
		}else{
			append_node(&rll, ptr2->item);
			ptr2 = ptr2->next;
		}
		rll.size++;
	}

	// part 2

	ptr = rll.head;

	LinkedList ll3;
	ll3.size = 0;
	ListNode* head3 = (ListNode*)malloc(sizeof(ListNode));
	ll3.head = head3;
	ListNode* ptr3 = head3;

	LinkedList ll4;
	ll4.size = 0;
	ListNode* head4 = (ListNode*)malloc(sizeof(ListNode));
	ll4.head = head4;
	ListNode* ptr4 = head4;

	for (int i = 0; i < count/2; i++){
		if (i == 0){
			head3->item = ptr->item;
			head3->next = NULL;
		}else{
			ListNode* new3 = (ListNode*)malloc(sizeof(ListNode));
			new3->item = ptr->item;
			new3->next = NULL;
			ptr3->next = new3;
			ptr3 = ptr3->next;
		}
		ptr = ptr->next;
		ll3.size++;
	}
	for (int i = count/2; i < count; i++){
		if (i == count/2){
			head4->item = ptr->item;
			head4->next = NULL;
		}else{
			ListNode* new4 = (ListNode*)malloc(sizeof(ListNode));
			new4->item = ptr->item;
			new4->next = NULL;
			ptr4->next = new4;
			ptr4 = ptr4->next;
		}
		ptr = ptr->next;
		ll4.size++;
	}

	ptr4 = ll4.head;
	ptr3 = ll3.head;

	LinkedList newrll;
	newrll.size = 0;

	for (int i = 0; i < count; i++){
		if (count % 2 != 0 && i == count-1){
			append_node(&newrll, ptr4->item);
			ptr4 = ptr4->next;
		}
		else if (i % 2 == 0){
			append_node(&newrll, ptr3->item);
			ptr3 = ptr3->next;
		}else{
			append_node(&newrll, ptr4->item);
			ptr4 = ptr4->next;
		}
		newrll.size++;
	}

	return ll1;
}

////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _listnode{
	int num;
	struct _listnode *next;
} ListNode;
typedef struct _linkedlist{
	ListNode *head;
	int size;
} LinkedList;
typedef struct _dbllistnode{
	int num;
	struct _dbllistnode *pre;
	struct _dbllistnode *next;
} DblListNode;

////////////////////////////////////////////////////////////////////
////////////
int removeNode(ListNode **ptrHead, int index);
int removeNode2(LinkedList *ll, int index);
int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList);
int duplicateReverse(ListNode *head, ListNode **ptrNewHead);

void printList(ListNode *head);
ListNode * findNode(ListNode *head, int index);
int insertNode(ListNode **ptrHead, int index, int value);


// these are for the practice questions
int moveMaxToFront(ListNode **ptrHead);
int concatenate(ListNode **ptrHead1, ListNode *head2);
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2);
int insertDbl(DblListNode **ptrHead, int index, int value);
void printDblList(DblListNode *head);

////////////////////////////////////////////////////////////////////
////////////

int main()
{
	int i;
	ListNode *head = NULL;
	ListNode *dupRevHead = NULL;
	ListNode *oddHead = NULL;
	ListNode *evenHead = NULL;
	ListNode *list1Head = NULL, *list2Head = NULL;
	ListNode *combAltHead = NULL;
	DblListNode *dblHead = NULL;
	LinkedList llist;
	int size = 0;

	//build a linked list
	if (insertNode(&head, 0, 6) == 0) size++;
	if (insertNode(&head, 0, 4) == 0) size++;
	if (insertNode(&head, 0, 2) == 0) size++;
	printf("After inserting 3 values.");
	printList(head);


	//removeNode(): question 1
	if (removeNode(&head, 3) == 0) size--;//this one can't be removed.
	if (removeNode(&head, 1) == 0) size--;
	if (removeNode(&head, 0) == 0) size--;

	printf("\nafter remove using removeNode(), ");
	printList(head);

	//insert some nodes
	if (insertNode(&head, 2, 3) == 0) size++; // this one can't be inserted.
	if (insertNode(&head, 1, 1) == 0) size++;
	if (insertNode(&head, 0, 0) == 0) size++;

	printf("\nafter insert, ");
	printList(head);

	//removeNode2(): question 2
	llist.head = head;
	llist.size = size;
	removeNode2(&llist, 2);
	removeNode2(&llist, 0);
	removeNode2(&llist, 0);
	head = llist.head;


	printf("\nafter remove using removeNode2(), ");
	printList(llist.head);
	// empty linked list now

	//split(): question 3
	for (i = 1; i <10; i++)//build a new linked list
		insertNode(&head, 0, i);
	printf("\n\ninsert 1-9 to the linked list,");
	printList(head);
	printf("split the current list, results:\n");
	split(head, &evenHead, &oddHead);
	printf("the even list");
	printList(evenHead);
	printf("the odd list");
	printList(oddHead);

	//duplicateReverse(): question 4
	printf("\n");
	printList(head);
	duplicateReverse(head, &dupRevHead);
	printf("After duplicateReverse(),");
	printList(dupRevHead);

	////////////////////////////////////////////////////////////////////////
	//the following are for the PRACTICE QUESTIONS

	printf("\n\nNow for the practice questions");

	//1.moveMaxToFront()
	printf("\n************** moveMaxToFront *******************\n");
	printList(dupRevHead);
	moveMaxToFront(&dupRevHead);
	printf("after moveMaxToFront()");
	printList(dupRevHead);

	//2. concatenate()
	printf("\n************** concatenate() *******************\n");
	printList(head);
	printList(dupRevHead);
	concatenate(&head, dupRevHead);
	printf("concatenate(current list, duplicate reverse list)\n  ");
	printList(head);

	//3.combineAlternating()
	printf("\n************** combineAlternating() *******************\n");
	for (i = 3; i > 0; i--)				//build linked list 1
		insertNode(&list1Head, 0, i);
	for (i = 13; i > 10; i--)			//build linked list 2
		insertNode(&list2Head, 0, i);
	printf("List 1:");
	printList(list1Head);
	printf("List 2: ");
	printList(list2Head);
	combineAlternating(&combAltHead, list1Head, list2Head);
	printf("After combineAlternating(): ");
	printList(combAltHead);

	//4. insertDbl()
	printf("\n************** insertDbl() *******************\n");
	printf("insertDbl()\nDoubly-linked list: ");
	insertDbl(&dblHead, 0, 10);
	insertDbl(&dblHead, 0, 20);
	insertDbl(&dblHead, 1, 30);
	insertDbl(&dblHead, 2, 40);
	printDblList(dblHead);
	return 0;
}

////////////////////////////////////////////////////////////////////
////////////

void printList(ListNode *head){
	ListNode *cur = head;

	if (cur == NULL)
		return;

	printf("the current linked list is:\n");
	while (cur != NULL){
		printf("%d ", cur->num);
		cur = cur->next;
	}
	printf("\n");
}

void printDblList(DblListNode *head){
	if (head == NULL) return;
	while (head != NULL){
		printf("%d ", head->num);
		head = head->next;
	}
	printf("\n");
}

ListNode * findNode(ListNode *head, int index){
	if (head == NULL || index < 0) return NULL;
	while (index > 0){
		head = head->next;
		if (head == NULL)
			return NULL;
		index--;
	}
	return head;
}

ListNode* findNode2(LinkedList ll, int index)
{
   if(ll.head != NULL){
        ListNode *cur = ll.head;
        if (cur==NULL || index<0 || index >ll.size)
           return NULL;

        while(index>0){
            cur=cur->next;
            if (cur==NULL)
                return NULL;
            index--;
        }
        return cur;
   }
   else
     return NULL;
}


int insertNode(ListNode **ptrHead, int index, int value){
	ListNode *pre, *cur;
	// If empty list or inserting first node, need to update head pointer
	if (*ptrHead == NULL || index == 0){
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(ListNode));
		(*ptrHead)->num = value;
		(*ptrHead)->next = cur;
		return 0;
	}
	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ptrHead, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->num = value;
		pre->next->next = cur;
		return 0;
	}
	return -1;
}

////////////////////////////////////////////////////////////////////
////////////

int removeNode(ListNode **ptrHead, int index){

  //Check if head is already null, we can return straight 0
    if(*ptrHead == NULL)
        return 0;

    /* Write your program code here */
    //Set curr to be ptrhead
    ListNode *curr;
    ListNode * pre;
    //Check if the index is 0 first, this means we are attempting to remove the head, so we should update the head accordingly
    if(index == 0)
    {
        curr = *ptrHead;
        *ptrHead = (*ptrHead)->next;
        //Then we free curr
        free(curr);
        return 1;
    }
    //Else we just attempt to find the node at that index
    else if((pre = findNode(*ptrHead, index -1)) != NULL)
    {
        //If we found the node to remove, we then find the node at the previous index as it is not a doubly linked list
        //Check if pre exists,
        if(pre->next != NULL)
        {
            curr = pre->next;
            //Set pre-> next to be nodeToRemove's next
            pre->next = pre->next->next;
            //Then we free the nodeToRemove
            free(curr);
            //Return 1 for successful remove
            return 1;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////

int removeNode2(LinkedList *ll, int index) {

	   //Same implemention of the previous
    //First we check if the head of ll is null, we can return straight as the linked list *head has not been initialized yet
    //Or if given index is more than ll's size, then we also return as we cant remove a node there
    if(ll->head == NULL || index > ll->size - 1)
        return 0;

    ListNode * pre, *curr;
    //Else check if index is 0 which means we are removing the first node
    if(index == 0)
    {
        //Set curr to be head
        curr = ll->head;
        ll->head = ll->head->next;
        //Call free on head
        free(curr);
        //Set head to be head's next
        //Decrement ll size
        ll->size--;
        return 1;
    }
    else if((pre = findNode2(*ll, index -1)) != NULL)
    {
        if(pre->next != NULL)
        {
            curr = pre->next;
            //We have to set pre to be next's next
            pre->next = pre->next->next;
            //Free pre->next
            free(curr);
            //Decrement ll size
            ll->size--;
            return 1;
        }    
    }
    return 0;
}



int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList)
{
//Variable declaration
    ListNode * curr;
    int indice = 0, evenSize = 0, oddSize = 0;
    //Sanity check
    if(head == NULL)
        return 0;
    //Variable initialization
    curr = head;
    while(curr != NULL)
    {
        if(indice % 2 == 0)
        {
            //Even
            insertNode(ptrEvenList,evenSize++,curr->num);
        }
        else
        {
            //Odd
            insertNode(ptrOddList,oddSize++,curr->num);
        }
        indice++;
        curr = curr->next;
    }
    return 1;

}

int duplicateReverse(ListNode *head, ListNode **ptrNewHead){

    //Variable declaration
    ListNode * curr;
    //Sanity check
    if(head == NULL)
        return -1;
    //Variable initialization
    curr = head;

    while(curr != NULL)
    {
        insertNode(ptrNewHead,0,curr->num);
        curr = curr->next;
    } 
	return 0;
}

////////////////////////////////////////////////////////////////////
////////////

////////////////////////////////////////////////////////////////////////

/// @brief Moves the max node of the linked list to the front
/// @param ptrHead pointer to pointer head
/// @return 0 if unsuccessful, 1 if successful.
int moveMaxToFront(ListNode **ptrHead)
{
    //Variable declaration
    ListNode * curr, *pre, *maxNode;
    int min;
    //Sanity check
    if(*ptrHead == NULL)
        return 0;
    //Variable initialization
    curr = *ptrHead;
	pre = NULL;
	maxNode = *ptrHead;

    //Do looping
    while(curr != NULL)
    {
		//If the next node is not nyll and the next number is larger, then its our new max
		if(curr->next != NULL && curr->num < curr->next->num)
		{
			//Store the reference of the "maxNode"
			maxNode = curr->next;
			//Update pre 
			pre = curr;
		}
        curr = curr->next;
    }    

	//If max node is equals to the head, nothing was changed
	if(maxNode == *ptrHead)
		return 0;
	
	//Handle the links between both
	pre->next = pre->next->next;
	maxNode->next = *ptrHead;
	*ptrHead = maxNode;

	return 1;
}

/// @brief Concatenates two linked lists
/// @param ptrHead1 head 1
/// @param head2 head2
/// @return 0 if it completes successfully and -1 otherwise
int concatenate(ListNode **ptrHead1, ListNode *head2){

	//Variable declaration
	ListNode * curr;
	//Sanity check
	if(ptrHead1== NULL || head2 == NULL)
		return -1;
	
	curr = *ptrHead1;
	//Go to the last node
	while(curr != NULL && curr->next != NULL)
	{
		curr = curr->next;
	}
	//Now curr holds the last node, so set curr next to be head2
	curr->next = head2;
	return 0;
}

/// @brief combines two linked lists into a new one
/// @param ptrHead head of combined list
/// @param head1 head of source linkedlist1
/// @param head2 head of source linkedlist 2
/// @return 0 if it completes successfully and -1 otherwise
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2){

	//Variable declaration
	ListNode * curr, *curr2;
	int index = 0, even = 1;
	//Sanity check
	if(ptrHead == NULL || head1 == NULL || head2 == NULL)
		return -1;
	//Variable initialization
	curr = head1;
	curr2 = head2;
	//Until one terminates
	while(curr != NULL && curr2 != NULL)
	{
		if(even == 1)
		{
			insertNode(ptrHead, index++, curr->num);
			curr = curr->next;
		}
		else
		{
			insertNode(ptrHead, index++, curr2->num);
			curr2 = curr2->next;
		}
		even = -even;
	}
	//Then do while and insert all, one of them has already reached end or both reached end
	while(curr != NULL)
	{
		insertNode(ptrHead, index++, curr->num);
		curr = curr->next;
	}
	while(curr2 != NULL)
	{
		insertNode(ptrHead, index++, curr2->num);
		curr2 = curr2->next;
	}
	return 0;
}


int insertDbl(DblListNode **ptrHead, int index, int value){

	// write your code here
	return 0;
}


////////////////////////////////////////////////////////////////////
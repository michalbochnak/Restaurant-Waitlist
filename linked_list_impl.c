// linked_list_impl.c
//
//	Michal Bochnak, mbochn2
//	

#include "wait_list.h"


// Add the new group to the list, return the pointer to the new head
List *AddToList(List *waitList, char *name, int size, boolean inRestaurant) {
	
	// fill in the struct info
	Group *temp = (Group*)malloc(sizeof(Group));
	inRestaurant ? (temp->Status = YES) : (temp->Status = NO);
	strcpy(temp->name, name);
	temp->size = size;

	// set up the pointers for pNext and pPrev  
	temp->pNext = NULL;
	temp->pPrev = waitList->pTail;

	// update pTail->pNext if needed
	if (waitList->pTail != NULL)
		waitList->pTail->pNext = temp;

	// update pHead if needed
	if (waitList->count == 0)
		waitList->pHead = temp;

	// update pTail
	waitList->pTail = temp;

	// increment number of elements on the list
	waitList->count++;

	return waitList;
}


// Checks if name is already on the list, returns TRUE if exist,
// FALSE is returned otherwise
boolean DoesNameExist(List *waitList, char *name) {

	Group *cur = waitList->pHead;		// set cur to pHead

	if (debugMode) {
		printf("\nDebugging information (function DoesNameExist):\n");
		if (listEmpty(waitList)) {
			printf("Wait list is empty.\n\n");
			return FALSE;
		}
	}

	// Search for the element
	while (cur != NULL) {
		if (debugMode) {
			printf("%31s, %4d, %5s\n", cur->name, cur->size,
				(cur->Status) ? "In Restaurant" : "Call ahead group");
		}
		if (strcmp(cur->name, name) == 0) 
			return TRUE;		// exists
		cur = cur->pNext;		// forward pointer
	}

	return FALSE;				// does not exist
}


// Update status of the Group
boolean UpdateStatus(List *waitList, char *name) {

	Group *cur = waitList->pHead;		// set cur to pHead

	if (debugMode) {
		printf("\nDebugging information (function UpdateStatus):\n");
		if (listEmpty(waitList)) {
			printf("Wait list is empty.\n\n");
			return FALSE;
		}
	}

	// Search for the element
	while (cur != NULL) {
		if (debugMode) {
			printf("%31s, %4d, %5s\n", cur->name, cur->size,
				(cur->Status) ? "In Restaurant" : "Call ahead group");
		}
		if (strcmp(cur->name, name) == 0) {
			if (cur->Status) 
				return FALSE;		// already marked as In Restaurant, return FALSE
			else {
				cur->Status = YES;	// update,
				return TRUE;		// updated, return TRUE
			}
		}
		cur = cur->pNext;			// forward the pointer
	}
}


// Find the group which can fit the given table size, removes the group if exist,
// returns the name of the group if found, NULL otherwise is returned
char *RetrieveAndRemove(List *waitList, int size) {

	Group *cur = waitList->pHead;		// set cur to pHead
	Group *toDelete = NULL;				// node to delete
	char *name;							// name to be returned if any

	if (debugMode) {
		printf("\nDebugging information (function RetrieveAndRemove):\n");
		if (listEmpty(waitList)) {
			printf("Wait list is empty.\n\n");
			return FALSE;
		}
	}

	// traverse the wait list
	while (cur != NULL) {
		if (debugMode) {
			printf("%31s, %4d, %5s\n", cur->name, cur->size,
				(cur->Status) ? "In Restaurant" : "Call ahead group");
		}

		if (cur->size <= size) {
			if (cur->Status) {			// check if group is in the restaurant
				// malloc the space for name
				name = (char*)malloc(sizeof(char) * strlen(cur->name) + 1);
				strcpy(name, cur->name);		// copy the name
				// remove the group from list
				waitList = RemoveGroup(cur, waitList);
				return name;		// return the name of group removed
			}
		}
		cur = cur->pNext;			// forward the pointer
	}

	return NULL;					// nothing to remove
}


// Removes the node from linked list, returns the pointer to the new head
List *RemoveGroup(Group *cur, List *waitList) {

	Group *toDelete = cur;		// group to delete

	// one node in the waitlist
	if (waitList->count == 1) {
		waitList->pHead = NULL;
		waitList->pTail = NULL;
		waitList->count--;		// decrement list counter
	}	// two nodes on the waitlist
	else if (waitList->count == 2) {
		// head to be removed
		if (toDelete == waitList->pHead) {
			waitList->pHead = waitList->pTail;
			waitList->pTail->pPrev = NULL;
			waitList->count--;	// decrement list counter
		}	
		// tail to be removed
		else {
			waitList->pTail = waitList->pHead;
			waitList->pHead->pNext = NULL;
			waitList->count--;	// decrement list counter
		}
	}
	// 3 or more nodes
	else {	
			// head to be removed
		if (toDelete == waitList->pHead) {
			waitList->pHead = toDelete->pNext;
			waitList->pHead->pPrev = NULL;
			waitList->count--;	// decrement list counter
			return;
		}
		// tail to be removed
		else if (toDelete == waitList->pTail) {
			waitList->pTail = toDelete->pPrev;
			waitList->pTail->pNext = NULL;
			waitList->count--;	// decrement list counter
		}
		// node to remove in the middle of the waitlist
		else {
			toDelete->pPrev->pNext = toDelete->pNext;
			toDelete->pNext->pPrev = toDelete->pPrev;
			waitList->count--;	// decrement list counter
		}
	}

	free(toDelete);

	return waitList;		// return head
}


// Count groups ahead, return number of groups ahead of given group,
// returns -1 if not found
int CountGroupsAhead(List *waitList, char *name) {

	Group *cur = waitList->pHead;		// set cur to pHead
	int count = 0;						// number of groups

	if (debugMode) {
		printf("\nDebugging information (function CountGroupsAhead):\n");
		if (listEmpty(waitList)) {
			printf("Wait list is empty.\n\n");
			return count;
		}
	}

	// traverse the list
	while (cur != NULL) {
		if (debugMode) {
			printf("%31s, %4d, %5s\n", cur->name, cur->size,
				(cur->Status) ? "In Restaurant" : "Call ahead group");
		}

		// found
		if (strcmp(cur->name, name) == 0) {
			printf("C: \n", count);
			return count;
		}
		cur = cur->pNext;		// forward pointer
		count++;				// increment pointer
	}
	
	return -1;
}


// Displays groups sizes ahead of given group
void DisplayGroupSizeAhead(List *waitList, int numOfGroupsAhead) {
	
	Group *cur = waitList->pHead;		// set cur to pHead

	if (debugMode) {
		printf("\nDebugging information (function DisplayGroupSizeAhead):\n");
		if (listEmpty(waitList)) {
			printf("Wait list is empty.\n\n");
		}
	}

	// displays the given number of groups
	while (numOfGroupsAhead--) {

		if (debugMode) {
			printf("%31s, %4d, %5s\n", cur->name, cur->size,
				(cur->Status) ? "In Restaurant" : "Call ahead group");
		}

		// display size of group
		printf("%2d\n", cur->size);
		cur = cur->pNext;
	}
}


// Display the whole waitlist
void DisplayListInformation(List *waitList) {

	Group *cur = waitList->pHead;		// set cut to pHead
	int num = 1;			// to number the groups ahile displaying

	if (cur == NULL) {
		printf("Wait list is empty\n\n");
		return;
	}

	// display table header
	printf("%4s %31s %15s %20s\n", "#:", "Group name:", "Group size:", "Status:");

	// raverse and display all groups info
	while (cur != NULL) {
		printf("%3d. %31s %15d %20s\n", num++, cur->name, cur->size,
			cur->Status ? "In Restaurant" : "Call ahead group");
		cur = cur->pNext;		// forward the pointer
	}
}


// Initialize list handle, returns pointer to the head of the list 
List *InitializeList(List *waitList) {
	waitList->pHead = NULL;
	waitList->pTail = NULL;
	waitList->count = 0;

	return waitList;
}


// Checks if the list is empty
// returns TRUE if list is empty, returns FALSE otherwise 
int listEmpty(List *waitList) {
	if (waitList->count == 0)
		return TRUE;		// empty
	else
		return FALSE;		// not empty
}

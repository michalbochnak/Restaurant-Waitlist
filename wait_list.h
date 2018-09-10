// wait_list.h
//
//	Michal Bochnak, mbochn2
//	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum { FALSE = 0, TRUE, NO = 0, YES } boolean;
int debugMode;			// global for debugMode control

// struct for storing info about each group
typedef struct Group {
	struct Group *pNext;
	struct Group *pPrev;
	char name[30];
	boolean Status;
	int size;
} Group;

// handle to the queue
typedef struct List {
	Group *pHead;
	Group *pTail;
	int count;
} List;


// ----------------------------------------------------------------------------
// Function prototypes
// ----------------------------------------------------------------------------

// user_interface.c
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printCommands();
void PrintAuthorInformation();

// licked_list.c
void doAdd(List **waitList);
void doCallAhead(List **waitList);
void doWaiting(List **waitList);
void doRetrieve(List **waitList);
void doList(List **waitList);
void doDisplay(List **waitList);

// linked_list_impl.c
List *AddToList(List *waitList, char *name, int size, boolean inRestaurant);
boolean DoesNameExist(List *waitList, char *name);
boolean UpdateStatus(List *waitList, char *name);
List *RemoveGroup(Group *cur, List *waitList);
char *RetrieveAndRemove(List *waitList, int size);
int CountGroupsAhead(List *waitList, char *name);
void DisplayGroupSizeAhead(List *waitList, int numOfGroupsAhead);
void DisplayListInformation(List *waitList);
List *InitializeList(List *waitList);
int listEmpty(List *waitList);
// linked_list.c
//
//	Michal Bochnak, mbochn2
//	


#include "wait_list.h"


void doAdd(List **waitList) {
	/* get group size from input */
	int size = getPosInt();
	if (size < 1) 	{
		printf("Error: Add command requires an integer value of at least 1\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name) 	{
		printf("Error: Add command requires a name to be given\n");
		printf("Add command is of form: a <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	// check if group does not exist
	if (!DoesNameExist(*waitList, name)) {
		printf("Adding group \"%s\" of size %d\n", name, size);
		// add group to the list
		*waitList = AddToList(*waitList, name, size, YES);
	}
	else	// group already on the list 
		printf("Name already on the list.\n");
}


void doCallAhead(List **waitList)
{
	/* get group size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Call-ahead command requires an integer value of at least 1\n");
		printf("Call-ahead command is of form: c <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	/* get group name from input */
	char *name = getName();
	if (NULL == name)
	{
		printf("Error: Call-ahead command requires a name to be given\n");
		printf("Call-ahead command is of form: c <size> <name>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		printf("         <name> is the name of the group making the reservation\n");
		return;
	}

	printf("Call-ahead group \"%s\" of size %d\n", name, size);

	// check if group does not exist
	if (!DoesNameExist(*waitList, name)) {
		printf("Adding group \"%s\" of size %d\n", name, size);
		// add group to the list
		*waitList = AddToList(*waitList, name, size, NO);
	}
	else	// group already on the list 
		printf("Name already on the list.\n");
}


void doWaiting(List **waitList) {
	/* get group name from input */
	char *name = getName();
	if (NULL == name) 	{
		printf("Error: Waiting command requires a name to be given\n");
		printf("Waiting command is of form: w <name>\n");
		printf("  where: <name> is the name of the group that is now waiting\n");
		return;
	}

	// check if group exist
	if (DoesNameExist(*waitList, name)) {
		boolean updated = UpdateStatus(*waitList, name);
		if (updated)	// group was updated succesfully
			printf("Waiting group \"%s\" is now in the restaurant\n", name);
		else	// marked as in restaurant already
			printf("Waiting group \"%s\" is marked as \"In restaurant\" already\n", name);
	}
	else		// group does not exist
		printf("There is no group named \"%s\" on the list.\n", name);
}


void doRetrieve(List **waitList)
{
	/* get table size from input */
	int size = getPosInt();
	if (size < 1)
	{
		printf("Error: Retrieve command requires an integer value of at least 1\n");
		printf("Retrieve command is of form: r <size>\n");
		printf("  where: <size> is the size of the group making the reservation\n");
		return;
	}
	clearToEoln();
	printf("Retrieve (and remove) the first group that can fit at a table of size %d\n", size);

	// pointer to retrieved group
	char *retrievedGroup = RetrieveAndRemove(*waitList, size);

	if (retrievedGroup == NULL)	// group does not found
		printf("There is no group which can fit table size of %d.\n", size);
	else {						// found, remove group from list
		printf("Group %s was retrieved and is now removed from the list.\n", retrievedGroup);
	}
}


void doList(List **waitList) {
	/* get group name from input */
	char *name = getName();
	int numOfGroupsAhead;

	if (NULL == name) {
		printf("Error: List command requires a name to be given\n");
		printf("List command is of form: l <name>\n");
		printf("  where: <name> is the name of the group to inquire about\n");
		return;
	}

	// check if group exist
	if (!DoesNameExist(*waitList, name))
		printf("There is no group named %s.\n", name);
	else {		// group exists
		// count number of groups ahead of the given group
		numOfGroupsAhead = CountGroupsAhead(*waitList, name);
		printf("There is %d groups ahead on group named %s.\n", numOfGroupsAhead, name);
		if (numOfGroupsAhead > 0) {		// at least one group ahead, display information
			printf("Group \"%s\" is behind the following groups sizes:\n", name);
			DisplayGroupSizeAhead(*waitList, numOfGroupsAhead);
		}
	}
}


void doDisplay(List **waitList) {

	List *temp = *waitList;

	clearToEoln();
	printf("Display information about all groups.\n");

	printf("Wait list contains total number of %d groups:\n\n", temp->count);
	DisplayListInformation(*waitList);
}
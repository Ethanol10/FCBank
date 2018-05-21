#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linked_list_implementation.h"


/*******************************************************************************
 * This function appends an Account at the end of a linked list of Account_t 
 * types.
 * inputs:
 * - Account (account_t accountS)
 * - Pointer to head of Account Linked List (nodeAcc_t* head)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void appendSingleAccNode(account_t accountS, nodeAcc_t* head)
{
	/*
		1)Check the first node, if there is nothing in the first node,
			place the element in there
		2)Else, go to the next nodes until nextNode field is null.
	*/
	if((*head).nextNode == NULL && (*head).account.id == 0){
		(*head).account = accountS;
	}
	else{
		nodeAcc_t* newNode = malloc(sizeof(nodeAcc_t) * 1);
		nodeAcc_t* currNode = head;
	
		while((*currNode).nextNode != NULL){
			currNode = (*currNode).nextNode;
		}
		(*currNode).nextNode = newNode;
		(*newNode).account = accountS;
		(*newNode).nextNode = NULL;
	}
	
}
/*******************************************************************************
 * This function appends a Joint Account to the end of a linked list of 
 * JointAccount_t
 * inputs:
 * - Joint Account (jointAccount_t account J)
 * - Pointer to head of Linked list of Joint Accounts (nodeJAcc_t* head)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
/* Add a joint account at the end of the linked list*/
void appendJointAccNode(jointAccount_t accountJ, nodeJAcc_t* head)
{
	if((*head).nextNode == NULL && (*head).account.userID1 == 0){
		(*head).account = accountJ;
	}
	else{
		nodeJAcc_t* newNode = malloc(sizeof(nodeJAcc_t) * 1);
		nodeJAcc_t* currNode = head;
	
		while((*currNode).nextNode != NULL){
			currNode = (*currNode).nextNode;
		}
		(*currNode).nextNode = newNode;
		(*newNode).account = accountJ;
		(*newNode).nextNode = NULL;
	}
}

/*******************************************************************************
 * This function removes an Account from a Linked List of Accounts.
 * inputs:
 * - Account (account_t accountS)
 * - Pointer to head of Account Linked List (nodeAcc_t* head)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void removeSingleAccNode(account_t accountS, nodeAcc_t* head)
{
	/* Variable Declaration*/
	nodeAcc_t* nodeLeft;
	nodeAcc_t currNode = *head;
	nodeAcc_t* nodeRight = NULL	;
	int found = 0; 
	int location = -1;
	int i;
	
	/* Find the node to delete, set the nodeShift to the 
		node next to the account being deleted.*/
	while( (currNode.nextNode != NULL) && (found != 1) ){
		if(currNode.account.id == accountS.id){
			found = 1;
			nodeRight = currNode.nextNode;
		}
		else{
			currNode = *currNode.nextNode;
			location++;
			if(currNode.account.id == accountS.id){
				found = 1;
				nodeRight = currNode.nextNode;
			}
		}
	}
	
	/* If the account is found, delete it by freeing the
		currNode.nextNode and shifting the neighbour node
		up to make the current node have the address of the
		shifted node.*/
	if(found){
		if(!(location < 0)){
			nodeLeft = head;
			for(i = 0; i < location - 1; i++){
				nodeLeft = (*nodeLeft).nextNode;
			}
			free((*nodeLeft).nextNode);
			(*nodeLeft).nextNode = nodeRight;
		}
		else{
			free(head);
			head = nodeRight;
		}
	}
}

/*******************************************************************************
 * This function removes a Joint Account from a Linked List of Joint Accounts.
 * inputs:
 * - Joint Account (jointAccount_t account J)
 * - Pointer to head of Linked list of Joint Accounts (nodeJAcc_t* head)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void removeJointAccNode(jointAccount_t accountJ, nodeJAcc_t* head)
{
	/* Variable Declaration*/
	/* nodeRight is the node that is further in the list next to the
		node needing to be removed.*/
	nodeJAcc_t* nodeLeft;
	nodeJAcc_t currNode = *head;
	nodeJAcc_t* nodeRight = NULL;
	int found = 0; 
	int location = -1;
	int i;
	
	/* Find the node to delete, set the nodeShift to the 
		node next to the account being deleted.*/
	while( (currNode.nextNode != NULL) && (found != 1) ){
		if(currNode.account.userID1 == accountJ.userID1){
			found = 1;
			nodeRight = currNode.nextNode;
		}
		else{
			currNode = *currNode.nextNode;
			location++;
			if(currNode.account.userID1 == accountJ.userID1){
				found = 1;
				nodeRight = currNode.nextNode;
			}
		}
	}
	
	/* If the account is found, delete it by freeing the
		currNode.nextNode and shifting the neighbour node
		up to make the current node have the address of the
		shifted node.*/
	if(found){
		if(!(location < 0)){
			nodeLeft = head;
			for(i = 0; i < location - 1; i++){
				nodeLeft = (*nodeLeft).nextNode;
			}
			free((*nodeLeft).nextNode);
			(*nodeLeft).nextNode = nodeRight;
		}
		else{
			free(head);
			head = nodeRight;
		}
	}
}

/*******************************************************************************
 * Finds an Account from a Linked List of Accounts and returns the account at 
 * the discovered node. Returns an account with an ID of 0 if the account could
 * not be found.
 * inputs:
 * - user ID (int userID)
 * - Pointer to head of Linked List (nodeAcc_t* head)
 * outputs:
 * - Pointer to Account (account_t)
 Author: Ethan Goh
*******************************************************************************/
nodeAcc_t* findSingleNode(int userID, nodeAcc_t* head)
{
	/*start at the head
	check the fields and see if they match.
	if the ID matches, return the account
	if no id matches, return an account with NULL;
	*/
	nodeAcc_t* currNode = head;
	nodeAcc_t* failedNode = NULL;
	
	if((*currNode).account.id == userID){
		return currNode;
	}
	
	while((*currNode).nextNode != NULL){
		if((*currNode).account.id == userID){
			return currNode;
		}
		else{
			currNode = (*currNode).nextNode;
		}
	} 
	
	if((*currNode).account.id == userID){
		return currNode;
	}
	
	return failedNode;
}

/*******************************************************************************
 * Finds an Account from a Linked List of Joint Accounts and returns the account
 * at the discovered node. Returns an account with an userID1 and userID2 of 0 
 * if the account could not be found.
 * inputs:
 * - User ID (int userID)
 * - Pointer to head of Linked List (nodeJAcc_t* head)
 * outputs:
 * - Pointer to Joint Account (jointAccount_t *)
 Author: Ethan Goh
*******************************************************************************/
nodeJAcc_t* findJointNode(int userID, nodeJAcc_t* head)
{
	/*start at the head
	check the fields and see if they match.
	if one of the two ID matches the input account, return the account
	if no id matches, return an account with NULL;
	*/
	
	nodeJAcc_t* currNode = head;
	nodeJAcc_t* failedNode = NULL; /*Account contains nothing if no match*/
	
	if((*currNode).account.userID1 == userID 
		|| (*currNode).account.userID2 == userID){
		return currNode;
	}
	
	while((*currNode).nextNode != NULL){
		if((*currNode).account.userID1 == userID 
			|| (*currNode).account.userID2 == userID){
			return currNode;
		}
		else{
			currNode = (*currNode).nextNode;
		}
	} 
	
	if((*currNode).account.userID1 == userID 
		|| (*currNode).account.userID2 == userID){
		return currNode;
	}

	return failedNode;
}

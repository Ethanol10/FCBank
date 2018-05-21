/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Group:26
 * Authors : 
 * Mohamad Win - 98034628
 * Ethan Goh - 12903151
 * Emmanuel Tshuma - 12311697
 * Varun Sriram - 12568731
 * Ngoc Thao Han Ho - 12868636
   
 * Date of submission: 10/05/2018
*******************************************************************************/

/*******************************************************************************
 * List of Header files. As the project is being developed, more header files 
 may be added.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Header files defined by group 26*/
#include "linked_list_implementation.h"

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define TRUE 1
#define FALSE 0
#define MAX_NAME_LEN 11

/*******************************************************************************
 * List structs
*******************************************************************************/
	/* User defined structs that are shared between the linked list and 
		this file are in the "linked_list_implementation.h" file. */

/*******************************************************************************
 * Function prototypes. As the project is being developed, more function 
 declarations may be added.
*******************************************************************************/
void addAccount(nodeAcc_t* headS, nodeJAcc_t* headJ); 
void editAccount(); 
void removeAccount();
void withdraw(int userID, nodeAcc_t* headS, nodeJAcc_t* headJ);
void deposit(int userID, nodeAcc_t* headS, nodeJAcc_t* headJ);
void transfer();
void encrypt();
void decrypt();
void compress();
void decompress();
void printMenu(int menuNo);
int isCorrectLogin(int userID, int userPin, nodeAcc_t* headS, 
					nodeJAcc_t* headJ);
void loginUser(nodeAcc_t* headS, nodeJAcc_t* headJ);
void singleAccountCreation(nodeAcc_t* headS);
void jointAccountCreation(nodeJAcc_t* headJ);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{	
	int userInput = 0;
	nodeAcc_t* headAcc = malloc(sizeof(nodeAcc_t) * 1);
	nodeJAcc_t* headJointAcc = malloc(sizeof(nodeJAcc_t) * 1);
	
	/*TEST INPUTS*/
	/*Initialise the first head.*/
	(*headAcc).account.id = 0;
	(*headJointAcc).account.userID1 = 0;
	(*headJointAcc).account.userID2 = 0;
	
	/*Accounts for Single.*/
	account_t account1;
	account1.id = 11100;
	account1.balance = 999;
	account1.pin = 3541;
	
	account_t account2;
	account2.id = 9999;
	account2.balance = 1;
	account2.pin = 3014;
	
	appendSingleAccNode(account1, headAcc);
	appendSingleAccNode(account2, headAcc);
	
	/*Accounts for Joint*/
	jointAccount_t account3;
	account3.userID1 = 11111;
	account3.userID2 = 22222;
	account3.balance = 20202;
	account3.userPin2 = 2222;
	account3.userPin1 = 1111;
	
	jointAccount_t account4;
	account4.userID1 = 12121;
	account4.userID2 = 23232;
	account4.balance = 10;
	account4.userPin2 = 9090;
	account4.userPin1 = 9987;	
	
	appendJointAccNode(account3, headJointAcc);
	appendJointAccNode(account4, headJointAcc);	
	/* TEST INPUTS */

	while(userInput != 3){
		/* Initial start up menu*/
		printMenu(1);
		userInput = 0;
		scanf(" %d", &userInput);
		while(getchar() != '\n'){} /*Clear input buffer*/
		
		switch (userInput){
			case 1: /* User Log in*/
				loginUser(headAcc, headJointAcc);
				break;
			case 2: /* Creating a new account*/
				addAccount(headAcc, headJointAcc);
				break;
			case 3: /*Exit the program*/
				break;
			default: /* Invalid Input*/
				printf("Invalid input, please try again\n");
				break;
		}
	}
	
    return 0;     
}

/*******************************************************************************
 * This function prints the initial menu with a list of functions the user may
 choose to use
 * - Integer to determine a menu to be printed (int menuNo)
 * outputs:
 * - none
 Author: Mohamad Win
*******************************************************************************/
void printMenu(int menuNo)
{
	switch (menuNo){
		case 1:
			printf("*\t*\t*\t*\t*\t*\t*");
			printf("\t*\t*\t*\t*\t*\t*\n");
			printf("\t\t\t\tWELCOME TO FCBANK\n");
			printf("Please select an option below by pressing the ");
			printf("corresponding number key on your keyboard\n");
			printf("1. Log in to an existing account\n");
			printf("2. Create a new account\n");
			printf("3. Exit program\n");
			break;
		case 2:
			printf("Please enter your ID associated with your account\n");
			break;
		case 3: 
			printf("Welcome! What would you like to do today?\n");
			printf("1. Deposit cash\n");
			printf("2. Withdraw cash\n");
			printf("3. Edit account\n");
			printf("4. Delete your account\n");
			printf("5. Transfer funds to another account\n");
			printf("6. Log out\n");
			break;
		case 4:
			printf("Creating Account:\n");
			printf("What account type are you making today?\n");
			printf("1. Single Account\n");
			printf("2. Joint Account\n");
			printf("3. Exit\n");
			break;
		case 5: 
			break;
		default:
			printf("*	*	*	*	*	*	*	*	* 	*	*	*	*\n");
			printf("				WELCOME TO FCBANK						\n");
			printf("Options:\n");	
			printf("Select an option by pressing ");
			printf("the corresponding number key on your keyboard\n");
			printf("1. Add an account\n");  
			printf("2. Edit an existing account\n"); 
			printf("3. Remove an account\n"); 
			printf("4. Add a joint account\n");
			printf("5. Withdraw from an existing account\n");
			printf("6. Deposit into an existing account\n");
			printf("7. Transfer between two existing accounts\n");
			printf("8. Exit program\n");
			break;
	}
}

/*******************************************************************************
 * This function creates a new account and places it in the linked list.
 * inputs:
 * - Head of linked list of single accounts (nodeAcc_t* headS)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void addAccount(nodeAcc_t* headS, nodeJAcc_t* headJ)
{
	int userInput = 0;
	
	printMenu(4);
	while(userInput != 3){
		scanf(" %d", &userInput);
		while(getchar() != '\n'){} /*Clear input buffer*/
		
		switch(userInput){			
			case 1: /*Single Account*/
				singleAccountCreation(headS);
				userInput = 3;
				break;
			case 2: /*Joint Account*/
				jointAccountCreation(headJ);
				userInput = 3;
				break;
			case 3:	/*Exit Menu*/
				break;
		}
	}
}

/*******************************************************************************
 * This function allows the user to edit an account to the system based on user 
 input.
 * inputs:
 * - account details 
 * outputs:
 * - edited account
 Author: Emmanuel Tshuma
*******************************************************************************/
void editAccount()
{

}

/*******************************************************************************
 * This function allows the user to remove an account if they can provide 
 required credentials.
 * inputs:
 * - account ID
 * outputs:
 * none
 Author: Ngoc Thao Han Ho
*******************************************************************************/
void removeAccount()
{

}

/*******************************************************************************
 * This function allows the user to withdraw money from their account 
 input.
 * inputs:
 * - Integer holding Bank ID (int userID)
 * - Head of linked list of single accounts (nodeAcc_t* headS)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ)
 * outputs:
 * - none
 Author: Emmanuel Tshuma
*******************************************************************************/
void withdraw(int userID, nodeAcc_t* headS, nodeJAcc_t* headJ)
{
/*	account_t* account1 = findSingleNode(userID, headS);
	jointAccount_t* account2 = findJointNode(userID, headJ);
	
	if((*account1).id){
		
	}
	else if((*account2).userID1){
		
	}*/
}

/*******************************************************************************
 * This function allows the user to deposit money into their account.
 * inputs:
 * - Integer holding Bank ID (int userID)
 * - Head of linked list of single accounts (nodeAcc_t* headS)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ)
 * outputs:
 * - none
 Author: Ngoc Thao Han Ho
*******************************************************************************/
void deposit(int userID, nodeAcc_t* headS, nodeJAcc_t* headJ)
{
	
}

/*******************************************************************************
 * This function allows the user to transfer money from their account to 
 another account. 
 input.
 * inputs:
 * - account ID, account ID
 * outputs:
 * - none
 Author: Mohamad Win
*******************************************************************************/
void transfer()
{
	
}

/*******************************************************************************
 * This function encrypts the user's data 
 input.
 * inputs:
 * - none
 * outputs:
 * - none
 Author: Mohamad Win
*******************************************************************************/
void encrypt()
{

}

/*******************************************************************************
 * This function decrypts the user's data if they are able to provide correct 
 credentials
 input.
 * inputs:
 * - none
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void decrypt()
{

}

/*******************************************************************************
 * This function compresses the user's data 
 input.
 * inputs:
 * - none
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void compress()
{

}

/*******************************************************************************
 * This function decompresses the user's data 
 input.
 * inputs:
 * - none
 * outputs:
 * - none
 Author: Varun Sriram
*******************************************************************************/
void decompress()
{

}

/*******************************************************************************
 * This function checked if the user data inputted matches an account in the 
 * linked list.
 * inputs:
 * - Bank ID (int userID)
 * - Bank PIN (int userPin)
 * - Head of linked list of single accounts (nodeAcc_t* headS)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ)
 * outputs:
 * - Integer acting as boolean variable to determine true or false.
 Author: Ethan Goh
*******************************************************************************/
int isCorrectLogin(int userID,
					int userPin, 
					nodeAcc_t* headS, 
					nodeJAcc_t* headJ){
	nodeAcc_t* testAcc;
	nodeJAcc_t* testJoint;
	
	testAcc = findSingleNode(userID, headS);
	testJoint = findJointNode(userID, headJ);
	
	if(testAcc != NULL){
		if((*testAcc).account.pin == userPin){
			return TRUE;
		}
	}
	else if(testJoint != NULL){
		if((*testJoint).account.userPin1 == userPin || (*testJoint).account.userPin2 == userPin){
			return TRUE;
		}
	}
	else{
		return FALSE;
	}
	
	return FALSE;
}

/*******************************************************************************
 * This function controls the user login menu and allows the user to input a 
 * number to access different menu items.
 * inputs:
 * - Head of linked list of single accounts (nodeAcc_t* headS)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void loginUser(nodeAcc_t* headS, nodeJAcc_t* headJ){
	int* currentUserID = malloc(sizeof(int) * 1);
	int* currentUserPin = malloc(sizeof(int) * 1);
	int found = FALSE;
	int userInput;
	
	printMenu(2);
	printf("Bank ID: \n");
	if(scanf(" %d", currentUserID) == 1){
		printf("PIN no: \n");
		scanf(" %d", currentUserPin);
		while(getchar() != '\n'){} /*Clear input buffer*/
		found = isCorrectLogin(*currentUserID,
							*currentUserPin, headS, headJ);
		if(found){
			userInput = 0;
			while(userInput != 6){
				printMenu(3);
				scanf(" %d", &userInput);
				switch(userInput){
					case 1: /*Deposit*/
						deposit(*currentUserID, headS, headJ);
						break;
					case 2: /*Withdraw*/
						withdraw(*currentUserID, headS, headJ);
						break;
					case 3: /*Edit Account Details*/
						editAccount();
						break;
					case 4: /*Delete Account*/
						removeAccount();
						break;
					case 5: /*Transfer funds to another account*/
						transfer();
						break;
					case 6: /*Logout*/
						found = FALSE;
						*currentUserID = 0;
						*currentUserPin = 0;
						printf("Log out successful!\n\n");
						break;
					default:			
						break;
				}
			}
		}
		else{
			printf("Invalid Bank ID/PIN combination. ");
			printf("Please try again.\n");
		}
	}
	else{
		printf("Invalid Bank ID. Please try again.\n");
	}
}

/*******************************************************************************
 * This function explicitly steps through a process to create a single account.
 * inputs:
 * - Head of linked list of single accounts (nodeAcc_t* headS)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/

void singleAccountCreation(nodeAcc_t* headS){
	int i;
	account_t newAcc;
	int allowed = FALSE;
	int numberFound, letterFound;
	int rndNo;
	int pinInt;
	char* pin = calloc(5, sizeof(char));
	char* fname = calloc(MAX_NAME_LEN, sizeof(char));
	char* lname = calloc(MAX_NAME_LEN, sizeof(char));
	printf("Creating Single Account: \n");
	/*First Name*/
	while(!allowed){
		printf("What is your first name? "); 
		printf("(10 characters maximum)\n");
		scanf(" %10s", fname);
		numberFound = FALSE;
		while(getchar() != '\n'){} /*Clear input buffer*/
		for(i = 0; i < MAX_NAME_LEN; i++){
			if(fname[i] >= '0' && fname[i] <= '9'){
				numberFound = TRUE;
				i = MAX_NAME_LEN;
			}
		}
		if(numberFound){
			printf("Names cannot contain numbers.\n");
		}
		else{
			allowed = TRUE; /*First name is valid*/
		}
	}
				
	allowed = FALSE;

	/*Last Name*/
	while(!allowed){
		printf("What is your last name? "); 
		printf("(10 characters maximum)\n");
		scanf(" %10s", lname);
		numberFound = FALSE;
		while(getchar() != '\n'){} /*Clear input buffer*/
		for(i = 0; i < MAX_NAME_LEN; i++){
			if(lname[i] >= '0' && lname[i] <= '9'){
				numberFound = TRUE;
				i = MAX_NAME_LEN;
			}
		}
		if(numberFound){
			printf("Names cannot contain numbers.\n");
		}
		else{
			allowed = TRUE; /*Last name is valid*/
		}
	}
		
	allowed = FALSE;
		
	/*Assign a random ID. Reroll if already taken.*/
	while(!allowed){
		rndNo = rand() % (1000000 - 100000)	+ 100000;
		allowed = findSingleNode(rndNo, headS) == NULL ? TRUE : FALSE;
	}
	printf("Your unique Bank ID is: %d\n", rndNo);
	
	allowed = FALSE;
		
	/*Let the user choose a pin*/				
	while(!allowed){
		printf("Please choose a 4 digit PIN.\n");
		scanf(" %4s", pin);
		while(getchar() != '\n'){} /*Clear input buffer*/
		letterFound = FALSE;
		for(i = 0; i < 5; i++){
			if(pin[i] <= '0' && pin[i] >= '9'){
				letterFound = TRUE;
				i = 5;
			}
		}
		if(letterFound){
			printf("PIN cannot have letters.\n");
		}
		else{
			pinInt = atoi(pin);	
			allowed = TRUE;
		}
	}
			
	printf("Thank you for joining FCBank. We hope you have a great day!\n");
	printf("Please log in to use your account.\n");
	newAcc.id = rndNo;
	newAcc.pin = pinInt;
	strcpy(newAcc.fname, fname);
	strcpy(newAcc.lname, lname);
	newAcc.balance = 0;
	appendSingleAccNode(newAcc, headS);
	
	free(fname);
	free(lname);
	free(pin);
}

/*******************************************************************************
 * This function explicitly steps through a process to create a joint account.
 * inputs:
 * - Head of linked list of joint accounts (nodeAcc_t* headJ)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/

void jointAccountCreation(nodeJAcc_t* headJ){
	int i;
	jointAccount_t newAcc;
	int allowed = FALSE;
	int numberFound, letterFound;
	int rndNo1;
	int rndNo2;
	int pinInt1;
	int pinInt2;
	char* pin1 = calloc(5, sizeof(char));
	char* pin2 = calloc(5, sizeof(char));
	char* fname1 = calloc(MAX_NAME_LEN, sizeof(char));
	char* lname1 = calloc(MAX_NAME_LEN, sizeof(char));
	char* fname2 = calloc(MAX_NAME_LEN, sizeof(char));
	char* lname2 = calloc(MAX_NAME_LEN, sizeof(char));
	
	printf("Creating Joint Account:\n");
	/*1st User First Name*/
	while(!allowed){
		printf("What is the first name for the first user? "); 
		printf("(10 characters maximum)\n");
		scanf(" %10s", fname1);
		numberFound = FALSE;
		while(getchar() != '\n'){} /*Clear input buffer*/
		for(i = 0; i < MAX_NAME_LEN; i++){
			if(fname1[i] >= '0' && fname1[i] <= '9'){
				numberFound = TRUE;
				i = MAX_NAME_LEN;
			}
		}
		if(numberFound){
			printf("Names cannot contain numbers.\n");
		}
		else{
			allowed = TRUE; /*First name is valid*/
		}
	}
				
	allowed = FALSE;

	/*1st User Last Name*/
	while(!allowed){
		printf("What is the last name for the first user? "); 
		printf("(10 characters maximum)\n");
		scanf(" %10s", lname1);
		numberFound = FALSE;
		while(getchar() != '\n'){} /*Clear input buffer*/
		for(i = 0; i < MAX_NAME_LEN; i++){
			if(lname1[i] >= '0' && lname1[i] <= '9'){
				numberFound = TRUE;
				i = MAX_NAME_LEN;
			}
		}
		if(numberFound){
			printf("Names cannot contain numbers.\n");
		}
		else{
			allowed = TRUE; /*Last name is valid*/
		}
	}
		
	allowed = FALSE;
	
	/*2nd User First Name*/
	while(!allowed){
		printf("What is the first name for the second  user? "); 
		printf("(10 characters maximum)\n");
		scanf(" %10s", fname2);
		numberFound = FALSE;
		while(getchar() != '\n'){} /*Clear input buffer*/
		for(i = 0; i < MAX_NAME_LEN; i++){
			if(fname2[i] >= '0' && fname2[i] <= '9'){
				numberFound = TRUE;
				i = MAX_NAME_LEN;
			}
		}
		if(numberFound){
			printf("Names cannot contain numbers.\n");
		}
		else{
			allowed = TRUE; /*First name is valid*/
		}
	}
				
	allowed = FALSE;

	/*2nd User Last Name*/
	while(!allowed){
		printf("What is the last name for the second user? "); 
		printf("(10 characters maximum)\n");
		scanf(" %10s", lname2);
		numberFound = FALSE;
		while(getchar() != '\n'){} /*Clear input buffer*/
		for(i = 0; i < MAX_NAME_LEN; i++){
			if(lname2[i] >= '0' && lname2[i] <= '9'){
				numberFound = TRUE;
				i = MAX_NAME_LEN;
			}
		}
		if(numberFound){
			printf("Names cannot contain numbers.\n");
		}
		else{
			allowed = TRUE; /*Last name is valid*/
		}
	}
		
	allowed = FALSE;
		
	/*Assign a random ID for 1st user. Reroll if already taken.*/
	while(!allowed){
		rndNo1 = rand() % (1000000 - 100000) + 100000;
		allowed = findJointNode(rndNo1, headJ) == NULL ? TRUE : FALSE;
		allowed = (rndNo1 == 0) ? FALSE : TRUE;
	}
	printf("For %s, Your unique Bank ID is: %d\n", fname1, rndNo1);
	
	allowed = FALSE;
		
	/*Let the 1st user choose a pin*/				
	while(!allowed){
		printf("%s, Please choose a 4 digit PIN.\n", fname1);
		scanf(" %4s", pin1);
		while(getchar() != '\n'){} /*Clear input buffer*/
		letterFound = FALSE;
		for(i = 0; i < 5; i++){
			if(pin1[i] <= '0' && pin1[i] >= '9'){
				letterFound = TRUE;
				i = 5;
			}
		}
		if(letterFound){
			printf("PIN cannot have letters.\n");
		}
		else{
			pinInt1 = atoi(pin1);	
			allowed = TRUE;
		}
	}
	
	allowed = FALSE;
	/*Assign a random ID for the 2nd user. Reroll if already taken.*/
	while(!allowed){
		rndNo2 = rand() % (1000000 - 100000) + 100000;
		allowed = findJointNode(rndNo2, headJ) == NULL? TRUE : FALSE;
		allowed = (rndNo2 == 0) ? FALSE : TRUE;
	}
	printf("For %s, Your unique Bank ID is: %d\n", fname2, rndNo2);
	
	allowed = FALSE;
		
	/*Let the 2nd user choose a pin*/				
	while(!allowed){
		printf("%s, Please choose a 4 digit PIN.\n", fname2);
		scanf(" %4s", pin2);
		while(getchar() != '\n'){} /*Clear input buffer*/
		letterFound = FALSE;
		for(i = 0; i < 5; i++){
			if(pin2[i] <= '0' && pin2[i] >= '9'){
				letterFound = TRUE;
				i = 5;
			}
		}
		if(letterFound){
			printf("PIN cannot have letters.\n");
		}
		else{
			pinInt2 = atoi(pin2);	
			allowed = TRUE;
		}
	}
			
	printf("Thank you for joining FCBank. We hope you have a great day!\n");
	printf("Please log in to use your account.\n");
	newAcc.userID1 = rndNo1;
	newAcc.userID2 = rndNo2;
	newAcc.userPin1 = pinInt1;
	newAcc.userPin2 = pinInt2;
	strcpy(newAcc.fname1, fname1);
	strcpy(newAcc.fname2, fname2);
	strcpy(newAcc.lname1, lname1);
	strcpy(newAcc.lname2, lname2);
	newAcc.balance = 0;
	appendJointAccNode(newAcc, headJ);
	
	free(fname1);
	free(lname1);
	free(fname2);
	free(lname2);
	free(pin1);
	free(pin2);
}
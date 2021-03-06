/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Group:26
 * Authors : 
 * Mohamad Win - 98034628
 * Ethan Goh - 12903151
 * Emmanuel Tshuma - 13211697
 * Varun Sriram - 12568731
 * Ngoc Thao Han Ho - 12868636
   
 * Date of submission: 02/06/2018
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
#define MAX_PASS_CHAR 20
#define DEBUG

/*******************************************************************************
 * List structs
*******************************************************************************/
	/* User defined structs that are shared between the linked list and 
		this file are in the "linked_list_implementation.h" file. */

/*******************************************************************************
 * Function prototypes. As the project is being developed, more function 
 declarations may be added.
*******************************************************************************/
void addAccount(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p); 
void editAccount(int* userID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p); 
void removeAccount(int* userID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p);
void withdraw(int* userID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p);
void deposit(int* userID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p);
void transfer(int* userID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p);
void encryptDecrypt(FILE *initial, FILE *changed, char* pass);
void printMenu(int menuNo);
int isCorrectLogin(int userID, int userPin, nodeAcc_t* headS_p, 
					nodeJAcc_t* headJ_p);
void loginUser(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p);
void singleAccountCreation(nodeAcc_t* headS_p);
void jointAccountCreation(nodeJAcc_t* headJ_p);
int saveAccountsToFile(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p, char* pass);
int loadAccountsFromFile(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p, char* pass);
account_t singleAccountStringSplit(char* accountStr);
jointAccount_t jointAccountStringSplit(char* jAccountStr);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(int argc, char* argv[])
{	
	FILE* passPtr;
	FILE* decryptPass;
	char pass[MAX_PASS_CHAR];
	char passInp[MAX_PASS_CHAR];
	char masterUser[MAX_PASS_CHAR];
	int userInput = 0;
	nodeAcc_t* headAcc_p = malloc(sizeof(nodeAcc_t) * 1);
	nodeJAcc_t* headJointAcc_p = malloc(sizeof(nodeJAcc_t) * 1);
	FILE* passwordRewritePtr;
	FILE* reXORPtr;
	FILE* plainTxtPtr;
	int successUser = FALSE;

#ifdef DEBUG
	printf("DEBUG IS DEFINED. IF THIS IS NOT INTENDED,");
	printf("PLEASE DISABLE DEBUG MODE IN THE SOURCE BEFORE COMPILING\n");
#endif
	/*
		1) Get the Username from the user. decrypt the password.
		2) if the password does not match, deny the user.
	*/
	/*PASSWORD LOADING*/
	
	printf("Please enter the username ->\n");
	scanf(" %20s", masterUser);
	while (getchar() != '\n') {} /*Clear input buffer*/
	
	passPtr = fopen("mp.txt", "rb");
	decryptPass = fopen("mps.bin", "wb");
	encryptDecrypt(passPtr, decryptPass, masterUser);
	
#ifdef DEBUG
	printf("here's your username = %s\n", masterUser);
#endif

	fclose(passPtr);
	fclose(decryptPass);
	
	if( (passPtr = fopen("mps.bin", "rb")) != NULL){
		if(fgets(pass, MAX_PASS_CHAR, passPtr) != NULL){
			successUser = TRUE;
			#ifdef DEBUG
				printf("Master password acquisition success: ");
				printf("%s\n", pass);
			#endif
		}
	}
	fclose(passPtr);
	
	if(!successUser){
		printf("Credentials incorrect, please try again,");
		printf(" or contact the software developer.\n");
		return 0;
	}
	if(argc <= 1 && successUser){
		/*TEST INPUTS*/
		/*Initialise the first head.*/
/*		(*headAcc_p).account.id = 0;
		(*headJointAcc_p).account.userID1 = 0;s
		(*headJointAcc_p).account.userID2 = 0;
	*/	
		printf("Please enter the master password -> \n");
		scanf(" %20s", passInp);
		while (getchar() != '\n') {} /*Clear input buffer*/
		if(strcmp(passInp, pass) == 0){
			if(loadAccountsFromFile(headAcc_p, headJointAcc_p, pass)){
				#ifdef DEBUG
				printf("Accounts loaded successfully.\n");
				#endif
			}
			else{
				#ifdef DEBUG
				printf("Accounts failed to load, ");
				printf("or there were no Accounts to load.\n");
				#endif
			}

			while (userInput != 3) {
				/* Initial start up menu*/
				printMenu(1);
				userInput = 0;
				scanf(" %d", &userInput);
				while (getchar() != '\n') {} /*Clear input buffer*/

				switch (userInput) {
				case 1: /* User Log in*/
					loginUser(headAcc_p, headJointAcc_p);
					break;
				case 2: /* Creating a new account*/
					addAccount(headAcc_p, headJointAcc_p);
					break;
				case 3: /*Exit the program*/
					break;
				default: /* Invalid Input*/
					printf("Invalid input, please try again\n");
					break;
				}
			}

			/*TEST FILE CREATION*/
			if (saveAccountsToFile(headAcc_p, headJointAcc_p, pass)) {
				#ifdef DEBUG
				printf("Success!\n");
				#endif
			}
			else {
				#ifdef DEBUG
				printf("Accounts not saved\n");
				#endif
			}
			
			/*Open passPtr to read password, 
				open decryptPass*/
			passPtr = fopen("mps.bin", "rb");
			decryptPass = fopen("mp.txt", "wb");
			encryptDecrypt(passPtr, decryptPass, masterUser);
			fclose(decryptPass);
			fclose(passPtr);
			remove("mps.bin");
		}
		else{
			printf("Password Incorrect.\n");
		}
		return 0;
	}
	else if(strcmp(argv[1], "-pass?") == 0){
		printf("Please enter the master password ->\n");
		scanf("%s", passInp);
		char* newPass = malloc(sizeof(char)* MAX_PASS_CHAR);
		char* confirmPass = malloc(sizeof(char) * MAX_PASS_CHAR);

		if(strcmp(pass, passInp) == 0){
			int userInput;
			while(userInput != 3){
				printMenu(7);
				scanf(" %d", &userInput);
				
				switch(userInput){
					case 1: /*Change master username*/
						printf("Please enter the new username\n");
						printf("Old username = %s\n", masterUser);
						int i;
						for(i = 0; i < MAX_PASS_CHAR; i++){
							masterUser[i] = '\0';
						}
						scanf(" %20s", masterUser);
						while (getchar() != '\n') {} /*Clear input buffer*/
						
						printf("Username successfully changed.\n");
						break;
					case 2:/*Change master password*/
						printf("Please input the new password:>\n");
						scanf(" %s", newPass);
						while (getchar() != '\n') {} /*Clear input buffer*/
						printf("Please confirm the new password:\n");
						scanf(" %s", confirmPass);
						while (getchar() != '\n') {} /*Clear input buffer*/
						
						if (strcmp(newPass, confirmPass) == 0) {
							passwordRewritePtr = fopen("mps.bin", "wb");
							fputs(newPass, passwordRewritePtr);
							fclose(passwordRewritePtr);
						}
						else {
							printf("Passwords do not match.\n");
						}
						
						/*Decrypting old database with the old master password*/
						reXORPtr = fopen("database.bin", "rb");
						plainTxtPtr = fopen("plainTxt.bin", "wb");
#ifdef DEBUG
						printf("Decrypting old database ");
						printf("with the old master password\n");
#endif
						encryptDecrypt(reXORPtr, plainTxtPtr, pass);
						fclose(reXORPtr);
						fclose(plainTxtPtr);
						
						/*Encrypting the plain text with a new master password*/
						reXORPtr = fopen("database.bin", "wb");
						plainTxtPtr = fopen("plainTxt.bin", "rb");
#ifdef DEBUG
						printf("Encrypting plain text ");
						printf("with a new master password.\n");
#endif
						encryptDecrypt(plainTxtPtr, reXORPtr, newPass);
						fclose(reXORPtr);
						fclose(plainTxtPtr);

						break;
					case 3:/*Exit superuser*/
						break;
				}
			}
					
			passPtr = fopen("mps.bin", "rb");
			decryptPass = fopen("mp.txt", "wb");
			encryptDecrypt(passPtr, decryptPass, masterUser);
			fclose(decryptPass);
			fclose(passPtr);
#ifndef DEBUG
				remove("mps.bin");
#endif
		}		
		else{
			printf("Password incorrect.\n");
		}
		return 0;
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
			printf("1. First Name\n");
			printf("2. Second Name\n");
			printf("3. PIN\n");
			printf("4. Exit\n");
			break;
		case 6: 
			printf("1. First User's First Name\n");
			printf("2. First User's Last Name\n");
			printf("3. First User's PIN\n");
			printf("4. Second User's First Name\n");
			printf("5. Second User's Last Name\n");
			printf("6. Second User's PIN\n");
			printf("7. Exit\n");
			break;	
		case 7:
			printf("Superuser Control\n");
			printf("1. Change master username\n");
			printf("2. Change master password\n");
			printf("3. Exit superuser\n");
			break;
		default:
			#ifdef DEBUG
			printf("Invalid Menu Code\n");
			#endif
			break;
	}
}

/*******************************************************************************
 * This function creates a new account and places it in the linked list.
 * inputs:
 * - Head of linked list of single accounts (nodeAcc_t* headS_p)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ_p)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void addAccount(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p)
{
	int userInput = 0;
	
	printMenu(4);
	while(userInput != 3){
		scanf(" %d", &userInput);
		while(getchar() != '\n'){} /*Clear input buffer*/
		
		switch(userInput){			
			case 1: /*Single Account*/
				singleAccountCreation(headS_p);
				userInput = 3;
				break;
			case 2: /*Joint Account*/
				jointAccountCreation(headJ_p);
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
 Author: Mohamad Win
*******************************************************************************/
void editAccount(int* currentUserID_p, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p)
{
	int choice, newPin;
	char newFName[MAX_NAME_LEN];
	char newLName[MAX_NAME_LEN];
	int loop = 0;
	nodeAcc_t* temp_account_p;
    nodeJAcc_t* temp_joint_p;
	
	temp_joint_p = findJointNode (*currentUserID_p, headJ_p);
    temp_account_p = findSingleNode (*currentUserID_p, headS_p);
	
	if(temp_account_p != NULL && temp_joint_p == NULL)
	{
		printf("What do you wish to change?\n");
		printMenu(5);
		scanf(" %d", &choice);
		while(getchar() != '\n'){} /*Clear input buffer*/
		while(loop==0)
		{
			switch(choice)
			{
				case 1: /*First Name*/
				printf("Please enter your new first name\n");
				scanf("%s", newFName);
				while(getchar() != '\n'){} /*Clear input buffer*/
				strcpy((*temp_account_p).account.fname, newFName);
				printf("Your first name has been changed.\n");
				loop=1;
					break;
				case 2: /*Last Name*/
				printf("Please enter your new last name\n");
				scanf("%s", newLName);
				while(getchar() != '\n'){} /*Clear input buffer*/
				strcpy((*temp_account_p).account.lname, newLName);
				printf("Your last name has been changed.\n");
				loop=1;
					break;
				case 3: /*Pin*/
				printf("Please enter your new desired PIN\n");
				scanf("%d", &newPin);
				while(getchar() != '\n'){} /*Clear input buffer*/
				(*temp_account_p).account.pin = newPin;
				printf("Your PIN number has been changed.\n");
				loop =1;
					break;
				case 4: /*Exit*/
				loop =1;	
					break;
			}
		}
	}
	
	else if (temp_joint_p!= NULL && temp_account_p == NULL)
	{	
		loop =0;
		printf("What do you wish to change?\n");
		printMenu(6);
		scanf(" %d", &choice);
		while(getchar() != '\n'){} /*Clear input buffer*/
		while(loop==0)
		{
			switch(choice)
			{
				case 1: /*First User's First Name*/
					printf("Please enter your new first name\n");
					scanf("%s", newFName);
					while(getchar() != '\n'){} /*Clear input buffer*/
					strcpy((*temp_joint_p).account.fname1, newFName);
					printf("Your first name has been changed.\n");
					loop =1;
					break;
				case 2: /*First User's Last Name*/
					printf("Please enter your new last name\n");
					scanf("%s", newLName);
					while(getchar() != '\n'){} /*Clear input buffer*/
					strcpy((*temp_joint_p).account.lname1, newLName);
					printf("Your last name has been changed.\n");
					loop =1;
					break;
				case 3: /*First User's Pin*/
					printf("Please enter your new desired PIN\n");
					scanf("%d", &newPin);
					while(getchar() != '\n'){} /*Clear input buffer*/
					(*temp_joint_p).account.userPin1 = newPin;
					printf("Your PIN number has been changed.\n");
					loop =1;
					break;
				case 4: /*Second User's First Name*/
					printf("Please enter your new first name\n");
					scanf("%s", newFName);
					while(getchar() != '\n'){} /*Clear input buffer*/
					strcpy((*temp_joint_p).account.fname2, newFName);
					printf("Your first name has been changed.\n");
					loop =1;
					break;
				case 5: /*Second User's Last Name*/
					printf("Please enter your new last name\n");
					scanf("%s", newLName);
					strcpy((*temp_joint_p).account.lname2, newLName);
					printf("Your last name has been changed.\n");
					loop=1;
					break;
				case 6: /*Second User's Pin*/
					printf("Please enter your new desired PIN\n");
					scanf("%d", &newPin);
					while(getchar() != '\n'){} /*Clear input buffer*/
					(*temp_joint_p).account.userPin2 = newPin;
					printf("Your PIN number has been changed.\n");
					loop =1;
					break;	
				case 7: /*Exit*/
					loop =1;
					break;
			}
		}
	}
	
	
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
void removeAccount(int* currentUserID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p)
{
    char sure_or_not[2];
    char balance_check[2];
    nodeAcc_t* temp_account_p;
    nodeJAcc_t* temp_joint_p;

    printf("Are you sure to delete your account? (Y/N) ");
    scanf(" %s", sure_or_not);
    while(getchar() != '\n'){} /*Clear input buffer*/
    printf("\n");
    /*check the first confirmation*/
    if (sure_or_not[1]!='\0') /*when input more than 2 characters*/
    {
      printf("Invalid input, please try again.\n");
	  removeAccount(currentUserID, headS_p, headJ_p);
	}
	else/*when input has 1 character only'*/
	{
    switch (sure_or_not[0])
    {
       case 'Y': /*Yes to delete*/
                temp_account_p = findSingleNode (*currentUserID, headS_p);
                temp_joint_p = findJointNode (*currentUserID, headJ_p);
		
			    if(temp_account_p != NULL && temp_joint_p == NULL) 
			    {  
	    	       printf("You still have $%.2lf as balance in your account.\n", 
	    	                                 (*temp_account_p).account.balance);
			    }
			    else if (temp_joint_p != NULL && temp_account_p == NULL)
                {
                   printf("You still have $%.2lf as balance in your account.\n", 
                                             (*temp_joint_p).account.balance); 
                }
                          
			    printf("Your balance will be lost after");
			    printf(" you delete your account.\n");
			    printf("Do you wish to continue? (Y/N) ");
			    scanf (" %s", balance_check);
			    while(getchar() != '\n'){} /*Clear input buffer*/
                printf("\n");
      /*second confirmation before deleting after knowing the current balance*/
      
      /*when the input has more than 2 characters*/
			    if (balance_check[1]!='\0')
                {
                printf("Invalid input, please try again.\n");
	            removeAccount(currentUserID, headS_p, headJ_p);
	            }
	  /*when the input has just 1 character*/
	            else
	            {
	            /*when input is 'Y' for second confirmation*/
			    if (balance_check[0]=='Y')
	            {
	              /*remove the single account*/
		          if (temp_account_p != NULL && temp_joint_p == NULL)
  	              {
		              removeSingleAccNode((*temp_account_p).account, headS_p);
    		      }
    		      /*remove the joint account*/
		          else if (temp_joint_p != NULL && temp_account_p == NULL)
    	          {
				      removeJointAccNode((*temp_joint_p).account, headJ_p);
			      }
	            printf("Your account was successfully deleted.\n");
	            break;
			    } 
			    /*when input is 'N' for second confirmation*/  
			    else if (balance_check[0] == 'N')
			    {
		            break;
    	        }
    	        /*when the character is not 'Y' or 'N'*/ 
			    else
			    {
			       printf("Invalid input, please try again.\n");
                   removeAccount(currentUserID, headS_p, headJ_p);
			    }
			    }
				break;
				
	   case 'N': /*No to delete*/
				printf("\n");
				break;
				
	   default: /*the first confirmation is different than 'Y' or 'N'*/
	            printf("\nInvalid input, please try again.\n");
	            removeAccount(currentUserID, headS_p, headJ_p);
	            
    }
    }
    
}

/*******************************************************************************
 * This function allows the user to withdraw money from their account 
 input.
 * inputs:
 * - Integer holding Bank ID (int userID)
 * - Head of linked list of single accounts (nodeAcc_t* headS_p)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ_p)
 * outputs:
 * - none
 Author: Mohamad Win
*******************************************************************************/
void withdraw(int* currentUserID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p)
{
	int loop = 0;
	char confirmation[2];
	char secondConfirm;
	double amount;
	nodeAcc_t* temp_account_p;
	nodeJAcc_t* temp_joint_p;
	
	temp_joint_p = findJointNode (*currentUserID, headJ_p);
    temp_account_p = findSingleNode (*currentUserID, headS_p);	
	
	/*check how much is in the balance*/
	while(loop == 0)
	{
		#ifdef DEBUG
		printf("entering withdraw loop\n");
		#endif
		if(temp_account_p != NULL && (*temp_account_p).account.balance>0 ) 
		{  
			printf("Your current balance is $%.2lf.\n", 
			(*temp_account_p).account.balance);
			loop =1;
		}
		/*If balance is too low, user cannot withdraw*/
		else if(temp_account_p != NULL && (*temp_account_p).account.balance<=0)
		{
			printf("Your current balance is $%.2lf.\n", 
			(*temp_account_p).account.balance);
			printf("Your balance is too low to withdraw.\n");
			printf("Returning to main menu.\n");
			return;
		}
	
		else if (temp_joint_p != NULL && (*temp_joint_p).account.balance>0)
		{
			printf("Your current balance is $%.2lf.\n", 
			(*temp_joint_p).account.balance);
			loop =1;
		}
		/*If balance is too low, user cannot withdraw*/
		else if(temp_joint_p != NULL && (*temp_joint_p).account.balance<=0)
		{
			printf("Your current balance is $%.2lf.\n", 
			(*temp_joint_p).account.balance);
			printf("Your balance is too low to withdraw.\n");
			printf("Returning to main menu.\n");
			return;
		}
	}
		
	printf("Do you wish to continue withdrawing? Y or N\n");
	scanf(" %s", confirmation);
	while(strlen(confirmation)>1)
		{
			printf("Invalid input. Please try again.\n");
			printf("Do you wish to continue withdrawing? Y or N\n");
			scanf(" %s", confirmation);
		}
		
	secondConfirm = confirmation[0];
	while(getchar() != '\n'){} /*Clear input buffer*/
	loop = 0;	

		switch(secondConfirm)
		{
			case 'Y': /*Yes to withdraw*/
                    
                printf("How much do you wish to withdraw? ");
				scanf (" %lf", &amount);
				while(getchar() != '\n'){} /*Clear input buffer*/
				printf("\n");
				/*Withdraw from a single account*/
				if (temp_account_p != NULL && 
				    (*temp_account_p).account.balance>=amount)
				{
				    (*temp_account_p).account.balance = 
					(*temp_account_p).account.balance - amount;
				    printf("Your withdraw is successful.\n");
					printf("Your new balance is $%.2lf.\n", 
					(*temp_account_p).account.balance);	
                    printf("\n");
				}
				
				else if(temp_account_p != NULL &&
				     (*temp_account_p).account.balance<amount)
				{
				    printf("Sorry, you have insufficient funds.\n");
				}
				/*Withdraw from the joint account*/   
				else if (temp_joint_p !=NULL && 
				    (*temp_joint_p).account.balance>=amount)
			    {
					(*temp_joint_p).account.balance = 
					    (*temp_joint_p).account.balance - amount;
					printf("Your withdraw is successful.\n");
			        printf("Your new balance is $%.2lf.\n", 
			            (*temp_joint_p).account.balance);
			        printf("\n");			  
				}
				
				else if(temp_joint_p != NULL && 
				    (*temp_joint_p).account.balance<amount)
				{
				    printf("Sorry, you have insufficient funds.\n");
				}
				
			    break;
				
			case 'N': /*No to deposit*/
				break;
				
			default: /*Wrong input for first confirmation*/
				printf("Invalid input, please try again.\n");
				withdraw(currentUserID, headS_p, headJ_p);
				break;
		}
	
}

/*******************************************************************************
 * This function allows the user to deposit money into their account.
 * inputs:
 * - Integer holding Bank ID (int userID)
 * - Head of linked list of single accounts (nodeAcc_t* headS_p)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ_p)
 * outputs:
 * - none
 Author: Ngoc Thao Han Ho
*******************************************************************************/
void deposit(int* currentUserID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p)
{
	char want_or_not[2];
	char add_money[100];
    nodeAcc_t* temp_account_p;
    nodeJAcc_t* temp_joint_p;
    int i;
    int letterFound;
    double amount;
    
    temp_joint_p = findJointNode (*currentUserID, headJ_p);
    temp_account_p = findSingleNode (*currentUserID, headS_p);	
    
    /*Check the current balance*/
	if(temp_account_p != NULL) /*When the user account is a single account*/
	{  
		printf("Your current balance is $%.2lf.\n", 
		                            (*temp_account_p).account.balance);
    }
	else if (temp_joint_p != NULL)/*When the user account is a joint account*/
    {
        printf("Your current balance is $%.2lf.\n", 
                                    (*temp_joint_p).account.balance);
    }
    
    /*Second confirmation*/
    printf("Are you want to continue to deposit? (Y/N) "); 
    scanf(" %s", want_or_not);           
    while(getchar() != '\n'){} /*Clear input buffer*/
    /*Check that the users just enter only 'Y' or 'N'*/
	if (want_or_not[1]!='\0') 
    {
      printf("\nInvalid input, please try again.\n");
	  deposit(currentUserID, headS_p, headJ_p);
	}
	else
    {
    switch (want_or_not[0])
    {
       case 'Y': /*Yes to deposit*/
                    printf("How much do you want to deposit? $");
               
				    scanf (" %s", add_money);
				    
				    while(getchar() != '\n'){} /*Clear input buffer*/
				    printf("\n");
				    letterFound = FALSE;
/*Check that the input add_money is a string of numbers, can be with decimal*/
				    for(i = 0; i < strlen(add_money); i++){
			        if((add_money[i] < '0' || add_money[i] > '9') 
			                                       && add_money[i] != '.'){
			        letterFound = TRUE;
		            i = strlen(add_money);
		            }
		            }
                   /*Check if there is character other than number in add_money, 
                    then print invalid input and return deposit function*/	    
		            if (letterFound) 
		            {
		                printf("\nInvalid input, please try again.\n");
				        deposit(currentUserID, headS_p, headJ_p);
		            }
                    /*Else convert string add_money to amount in double type */
		            else
		            {
		            sscanf(add_money, " %lf", &amount);
				/*Deposit in single account with entered amount greater than 0*/
				    if (temp_account_p != NULL) 
				    {
				        (*temp_account_p).account.balance += amount;
				        printf("Your deposit is successful.\n");
				        printf("Your new balance is $%.2lf.\n", 
				                             (*temp_account_p).account.balance);
				        printf("\n");
				        deposit(currentUserID, headS_p, headJ_p);   
				    }
				    
				 /*Deposit in joint account with entered amount greater than 0*/
				    else if (temp_joint_p !=NULL) 
				    {
				        (*temp_joint_p).account.balance += amount;
				        printf("Your deposit is successful.\n");
				        printf("Your new balance is $%.2lf.\n", 
				                              (*temp_joint_p).account.balance);
				        printf("\n");
				        deposit(currentUserID, headS_p, headJ_p);
				    }
				 
				    } 
				    break;
				
	   case 'N': /*No to deposit*/
				printf("\n");
				break;
				
	   default: /*Wrong input for first confirmation*/
	            printf("\nInvalid input, please try again.\n");
	            deposit(currentUserID, headS_p, headJ_p);	            
    }
    }
}
/*******************************************************************************
 * This function allows the user to transfer money from their account to 
 another account. 
 input.
 * inputs:
 * - account ID, account ID
 * outputs:
 * - none
 Author: Ngoc Thao Han Ho/ Mohamad Win
*******************************************************************************/
void transfer(int* currentUserID, nodeAcc_t* headS_p, nodeJAcc_t* headJ_p)
{
	int loop = 0,check;
	char confirmation[2];
	char transfer_money[100];
	int i;
    int letterFound;
    double amount;

	nodeAcc_t* temp_account_p;
	nodeJAcc_t* temp_joint_p;
	nodeAcc_t* temp_account2_p;
	nodeJAcc_t* temp_joint2_p;
	
	temp_joint_p = findJointNode (*currentUserID, headJ_p);
    temp_account_p = findSingleNode (*currentUserID, headS_p);
	
	while(loop == 0)
	{
		#ifdef DEBUG
		printf("entering transfer loop\n");
		#endif
		if(temp_account_p != NULL && (*temp_account_p).account.balance>0 ) 
		{  
			printf("Your current balance is $%.2lf.\n", 
			(*temp_account_p).account.balance);
			loop =1;
		}
		/*If balance is too low, user cannot withdraw*/
		else if(temp_account_p != NULL && (*temp_account_p).account.balance<=0)
		{
			printf("Your current balance is $%.2lf.\n", 
			(*temp_account_p).account.balance);
			printf("Your balance is too low to transfer.\n");
			printf("Returning to main menu.\n");
			return;
		}
	
		else if (temp_joint_p != NULL && (*temp_joint_p).account.balance>0)
		{
			printf("Your current balance is $%.2lf.\n", 
			(*temp_joint_p).account.balance);
			loop =1;
		}
		/*If balance is too low, user cannot withdraw*/
		else if(temp_joint_p != NULL && (*temp_joint_p).account.balance<=0)
		{
			printf("Your current balance is $%.2lf.\n", 
			(*temp_joint_p).account.balance);
			printf("Your balance is too low to transfer.\n");
			printf("Returning to main menu.\n");
			return;
		}
	}
	
	printf("Do you wish to continue transferring? (Y/N) ");
	
	scanf(" %s", confirmation);           
    while(getchar() != '\n'){} /*Clear input buffer*/
    loop = 0;
    /*Check that user input for confirmation is just only 'Y' or 'N'*/
    if (confirmation[1]!='\0')
    {
      printf("\nInvalid input, please try again.\n");
	  transfer(currentUserID, headS_p, headJ_p);
	}
	else
    {
	switch(confirmation[0])
	{
	    case 'Y':
	        printf("Please enter the ID of the account you wish");
	        printf(" to transfer to\n");
	        scanf(" %d", &check);
	        while(getchar() != '\n'){} /*Clear input buffer*/
	        
	        int* accID;
        	accID = &check;
        	temp_joint2_p = findJointNode (*accID, headJ_p);
            temp_account2_p = findSingleNode (*accID, headS_p);
        	printf("Please enter the amount you would like to transfer: $");
        	scanf(" %s", transfer_money);
        	while(getchar() != '\n'){} /*Clear input buffer*/
        	printf("\n");
		    letterFound = FALSE;
            /*Check that the input transfer_money is a string of numbers,
            can be with decimal*/
		    for(i = 0; i < strlen(transfer_money); i++){
	            if((transfer_money[i] < '0' || transfer_money[i] > '9')
	                                            && transfer_money[i] != '.'){
			        letterFound = TRUE;
			        i = strlen(transfer_money);
		            }
            }
            /*Check if there is a letter in transfer_money, 
            then print invalid input and return deposit function*/
        	if (letterFound)
		    {
                printf("\nInvalid input, please try again.\n");
		        transfer(currentUserID, headS_p, headJ_p);
            }
            /*Else convert string add_money to amount in double type*/
            else
            {
                sscanf(transfer_money, " %lf", &amount);
            /*Transfer from a single account to a single account*/
        	if (temp_account2_p != NULL && temp_account_p != NULL && 
        	temp_joint_p == NULL && temp_joint2_p == NULL)
        	{       
        	    (*temp_account_p).account.balance = 
        	    (*temp_account_p).account.balance - amount;
        	    (*temp_account2_p).account.balance += amount;
        	    printf("You successfully transfered $%.2lf to %d.\n", 
        	                                                amount, *accID); 
        	    transfer(currentUserID, headS_p, headJ_p);     
        	}
            /*Transfer from a single account to a joint account*/
        	else if (temp_account2_p == NULL && temp_account_p != NULL && 
        	temp_joint_p == NULL && temp_joint2_p != NULL)
        	{
        	    (*temp_account_p).account.balance = 
        	    (*temp_account_p).account.balance - amount;
        	    (*temp_joint2_p).account.balance += amount;
        	    printf("You successfully transfered $%.2lf to %d.\n", 
        	                                                amount, *accID);      
        	    transfer(currentUserID, headS_p, headJ_p);
        	}
            /*Transfer from a joint account to a single account*/
        	else if (temp_account2_p != NULL && temp_account_p == NULL && 
        	temp_joint_p != NULL && temp_joint2_p == NULL)
        	{
        	    (*temp_joint_p).account.balance = 
        	    (*temp_joint_p).account.balance - amount;
        	    (*temp_account2_p).account.balance += amount;
        	    printf("You successfully transfered $%.2lf to %d.\n", 
        	                                                amount, *accID);       
        	    transfer(currentUserID, headS_p, headJ_p);
        	}
            /*Transfer from a joint account to a joint account*/
        	else if (temp_account2_p == NULL && temp_account_p == NULL && 
        	temp_joint_p != NULL && temp_joint2_p != NULL)
        	{
        	    (*temp_joint_p).account.balance = 
        	    (*temp_joint_p).account.balance - amount;
        	    (*temp_joint2_p).account.balance += amount;
        	    printf("You successfully transfered $%.2lf to %d.\n", 
        	                                                amount, *accID); 
        	    transfer(currentUserID, headS_p, headJ_p);
        	}
            /*Print invalid input when the the entered ID that
					user wanted to transfer to is wrong */
        	else
        	{
        	     printf("Invalid input, please try again.\n");
        	     transfer(currentUserID, headS_p, headJ_p);
        	}
        	}
	        break;
	        
        case 'N': /*No to transfer*/
            printf("\n");
            break;
            
        default: /*Wrong input for first confirmation*/
            printf("\nInvalid input, please try again.\n");
            transfer(currentUserID, headS_p, headJ_p);    	        
	}
	}
}

/*******************************************************************************
 * This function encrypts/decrypts the file holding a databse.
 * inputs:
 * - Pointer to FILE (FILE* initial)
 * - Pointer to FILE (FILE* changed)
 * - Master password (char* pass)
 * outputs:
 * - none
 Author: Ethan Goh/Mohamad Win
*******************************************************************************/
void encryptDecrypt(FILE *initial, FILE *changed, char* pass) {
	int i = 0;
	char c1;
	char c2;

	while ((c1 = fgetc(initial)) != EOF) {
		/*
			Get char 1, XOR it with pass[x],
			where x = (position of current char) modulo (passsize/charsize)
		*/
		c2 = c1 ^ pass[i % (sizeof(pass) / sizeof(char))];
		i++;
		if (fputc(c2, changed) == EOF) {
			#ifdef DEBUG
				printf("EOF reached");
			#endif
		}
	}
}

/*******************************************************************************
 * This function checked if the user data inputted matches an account in the 
 * linked list.
 * inputs:
 * - Bank ID (int userID)
 * - Bank PIN (int userPin)
 * - Head of linked list of single accounts (nodeAcc_t* headS_p)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ_p)
 * outputs:
 * - Integer acting as boolean variable to determine true or false.
 Author: Ethan Goh
*******************************************************************************/
int isCorrectLogin(int userID,
					int userPin, 
					nodeAcc_t* headS_p, 
					nodeJAcc_t* headJ_p){
	nodeAcc_t* testAcc;
	nodeJAcc_t* testJoint;
	
	testAcc = findSingleNode(userID, headS_p);
	testJoint = findJointNode(userID, headJ_p);
	
	if(testAcc != NULL){
		if((*testAcc).account.pin == userPin){
			return TRUE;
		}
	}
	else if(testJoint != NULL){
		if((*testJoint).account.userPin1 == userPin || 
		        (*testJoint).account.userPin2 == userPin){
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
 * - Head of linked list of single accounts (nodeAcc_t* headS_p)
 * - Head of linked list of joint accounts (nodeJAcc_t* headJ_p)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/
void loginUser(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p){
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
							*currentUserPin, headS_p, headJ_p);
		if(found){
			userInput = 0;
			while(userInput != 6){
				printMenu(3);
				scanf(" %d", &userInput);
				switch(userInput){
					case 1: /*Deposit*/
						deposit(currentUserID, headS_p, headJ_p);
						break;
					case 2: /*Withdraw*/
						withdraw(currentUserID, headS_p, headJ_p);
						break;
					case 3: /*Edit Account Details*/
						editAccount(currentUserID, headS_p, headJ_p);
						break;
					case 4: /*Delete Account*/
						removeAccount(currentUserID, headS_p, headJ_p);
						userInput = 6;
						break;
					case 5: /*Transfer funds to another account*/
						transfer(currentUserID, headS_p, headJ_p);
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
 * - Head of linked list of single accounts (nodeAcc_t* headS_p)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/

void singleAccountCreation(nodeAcc_t* headS_p){
	int i;
	account_t newAcc;
	int allowed = FALSE;
	int numberFound, letterFound;
	int rndNo;
	int pinInt;
	char* pin = calloc(5, sizeof(char));
	char* fname = calloc(MAX_NAME_LEN, sizeof(char));
	char* lname = calloc(MAX_NAME_LEN, sizeof(char));
	int rndSeed = 0;
	
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
	/*
	  Assign a random ID. Reroll if already taken.
	  Using fname converted to an int + rand mod strlen(lname)	
	  as a seed.
	*/
	for(i = 0; i < strlen(fname); i++){
		rndSeed += fname[i] + rand() % strlen(lname);
	}
	while(!allowed){
		srand(rndSeed);
		rndNo = rand() % (1000000 - 100000)	+ 100000;
		allowed = findSingleNode(rndNo, headS_p) == NULL ? TRUE : FALSE;
	}
	printf("Your unique Bank ID is: %d\n", rndNo);
	
	allowed = FALSE;
		
	/*Let the user choose a pin*/				
	while(!allowed){
		printf("Please choose a 4 digit PIN.\n");
		scanf(" %4s", pin);
		while(getchar() != '\n'){} /*Clear input buffer*/
		letterFound = FALSE;
		for(i = 0; i < 4; i++){
			if(pin[i] <= '0' || pin[i] >= '9'){
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
	appendSingleAccNode(newAcc, headS_p);
	
	free(fname);
	free(lname);
	free(pin);
}

/*******************************************************************************
 * This function explicitly steps through a process to create a joint account.
 * inputs:
 * - Head of linked list of joint accounts (nodeAcc_t* headJ_p)
 * outputs:
 * - none
 Author: Ethan Goh
*******************************************************************************/

void jointAccountCreation(nodeJAcc_t* headJ_p){
	int i;
	jointAccount_t newAcc;
	int allowed = FALSE;
	int numberFound, letterFound;
	int rndNo1;
	int rndNo2;
	int pinInt1;
	int pinInt2;
    int rndSeed;
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
		printf("What is the first name for the second user? "); 
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
		
	/*Assign a random ID for 1st user. Reroll if already taken.
	  Using fname converted to an int + rand mod strlen(lname)	
	  as a seed.
	*/
	rndSeed = 0;
	for(i = 0; i < strlen(fname1); i++){
		rndSeed += fname1[i] + rand() % strlen(lname1);
	}
	while(!allowed){
		rndNo1 = rand() % (1000000 - 100000) + 100000;
		allowed = findJointNode(rndNo1, headJ_p) == NULL ? TRUE : FALSE;
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
	
	/*Assign a random ID for the 2nd user. Reroll if already taken.
	  Using fname converted to an int + rand mod strlen(lname)	
	  as a seed.
	*/
	rndSeed = 0;
	for(i = 0; i < strlen(fname2); i++){
		rndSeed += fname2[i] + rand() % strlen(lname2);
	}
	while(!allowed){
		rndNo2 = rand() % (1000000 - 100000) + 100000;
		allowed = findJointNode(rndNo2, headJ_p) == NULL? TRUE : FALSE;
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
	appendJointAccNode(newAcc, headJ_p);
	
	free(fname1);
	free(lname1);
	free(fname2);
	free(lname2);
	free(pin1);
	free(pin2);
}

/*******************************************************************************
* This function saves all accounts of both types into a file.
* inputs:
* - Head of linked list of single accounts (nodeAcc_t* headJ_p)
* - Head of linked list of joint accounts (nodeJAcc_t* headJ_p)
* - Encryption key (char* pass)
* outputs:
* - Integer indicating success in saving (0 = Failure)(int)
Author: Ethan Goh
*******************************************************************************/
int saveAccountsToFile(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p, char* pass) {
	/*
	WRITING FORMAT:
	FOR SINGLE ACCOUNTS:
	1) ID, PIN, BALANCE, FNAME, LNAME

	FOR JOINT ACCOUNTS:
	1) ID1, ID2, PIN1, PIN2, BALANCE, FNAME1, LNAME1, FNAME2, LNAME2

	SINGLE ACCOUNTS ARE PRINTED FIRST, THEN ALL JOINT ACCOUNTS AFTERWARDS.
	*/
#ifdef DEBUG
	printf("Saving accounts to file\n");
#endif
	FILE* writePtr;
	FILE* encryptData;
	nodeAcc_t* currNode = headS_p;
	nodeJAcc_t* currNodeJ = headJ_p;
	int success = FALSE;

	writePtr = fopen("plainTxt.bin", "wb");

	if (writePtr != NULL) {
		while (currNode != NULL) {
			fprintf(writePtr, "%d ", (*currNode).account.id);
			fprintf(writePtr, "%d ", (*currNode).account.pin);
			fprintf(writePtr, "%lf ", (*currNode).account.balance);
			fprintf(writePtr, "%s ", (*currNode).account.fname);
			fprintf(writePtr, "%s\n", (*currNode).account.lname);
			currNode = (*currNode).nextNode;
		}

		fprintf(writePtr, "JOINTACCOUNT\n");

		while (currNodeJ != NULL) {
			fprintf(writePtr, "%d ", (*currNodeJ).account.userID1);
			fprintf(writePtr, "%d ", (*currNodeJ).account.userID2);
			fprintf(writePtr, "%d ", (*currNodeJ).account.userPin1);
			fprintf(writePtr, "%d ", (*currNodeJ).account.userPin2);
			fprintf(writePtr, "%lf ", (*currNodeJ).account.balance);
			fprintf(writePtr, "%s ", (*currNodeJ).account.fname1);
			fprintf(writePtr, "%s ", (*currNodeJ).account.lname1);
			fprintf(writePtr, "%s ", (*currNodeJ).account.fname2);
			fprintf(writePtr, "%s\n", (*currNodeJ).account.lname2);
			currNodeJ = (*currNodeJ).nextNode;
		}
		success = TRUE;
	}
	fclose(writePtr);

	/*Encrypt before closing program*/
	writePtr = fopen("plainTxt.bin", "rb");
	encryptData = fopen("database.bin", "wb");
	encryptDecrypt(writePtr, encryptData, pass);

#ifndef DEBUG
	/* If debug is enabled, the account file is saved as both an encrypted
	file and a non-encrypted file.*/
	success = !(remove("plainTxt.bin"));
#endif

	fclose(encryptData);
	fclose(writePtr);
	return success;
}

/*******************************************************************************
* This function loads accounts from a database.bin file.
* inputs:
* - Head of linked list of single accounts (nodeAcc_t* headS_p)
* - Head of linked list of joint accounts (nodeJAcc_t* headJ_p)
* - Pointer to an array of chars (char* pass)
* outputs:
* - Integer indicating success in loading. (int)
Author: Ethan Goh
*******************************************************************************/
int loadAccountsFromFile(nodeAcc_t* headS_p, nodeJAcc_t* headJ_p, char* pass){
	/*
	WRITING FORMAT:
	FOR SINGLE ACCOUNTS:
	1) ID, PIN, BALANCE, FNAME, LNAME
	
	FOR JOINT ACCOUNTS:
	1) ID1, ID2, PIN1, PIN2, BALANCE, FNAME1, LNAME1, FNAME2, LNAME2
	
	SINGLE ACCOUNTS ARE PRINTED FIRST, THEN ALL JOINT ACCOUNTS AFTERWARDS. 
	*/
	int success = FALSE;
	FILE* readPtr;
	FILE* decryptData;
	char* accountStr = malloc(sizeof(char) * 150);
	account_t readAccount;
	jointAccount_t readJoint;
	int jointFlag = FALSE;

	decryptData = fopen("database.bin", "rb");
	readPtr = fopen("plainTxt.bin", "wb");
	if (decryptData != NULL) {
		encryptDecrypt(decryptData, readPtr, pass);
	}
	else {
		success = FALSE;
		return success;
	}

	fclose(readPtr);
	fclose(decryptData);

#ifdef DEBUG
	printf("Reading accounts from file\n");
#endif

	readPtr = fopen("plainTxt.bin", "rb");
	if (readPtr != NULL) {
		while ((fgets(accountStr, 150, readPtr) != NULL)) {
			if (!jointFlag) {
				if (!strcmp("JOINTACCOUNT\n", accountStr)) {
					jointFlag = TRUE;
				}
				else {
					readAccount = singleAccountStringSplit(accountStr);
					appendSingleAccNode(readAccount, headS_p);
				}
			}
			else {
				readJoint = jointAccountStringSplit(accountStr);
				appendJointAccNode(readJoint, headJ_p);
			}
		}
		success = TRUE;
	}

	if (readPtr != NULL) {
		fclose(readPtr);
	}
	free(accountStr);

#ifndef DEBUG
	success = !(remove("plainTxt.bin"));
#endif
	return success;
}

/*******************************************************************************
* This function splits the string that holds account data into account fields.
* inputs:
* - Pointer to an Array of chars (char* accountStr)
* outputs:
* - Account with filled in data (account_t)
Author: Ethan Goh
*******************************************************************************/
account_t singleAccountStringSplit(char* accountStr){
	/*
	WRITING FORMAT:
	FOR SINGLE ACCOUNTS:
	1) ID, PIN, BALANCE, FNAME, LNAME
	*/
	int i = 0, j = 0;
	char * buffer = malloc(sizeof(char) * 50);
	account_t account;
	
	/*Account ID*/
	while(*(accountStr + i) != ' '){
		buffer[j] = accountStr[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	sscanf(buffer, " %d", &account.id);
	j = 0;
	i++;
	
	/*Account Pin*/
	while(*(accountStr + i) != ' '){
		buffer[j] = accountStr[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	sscanf(buffer, " %d", &account.pin);
	j = 0;
	i++;

	/*Account Balance*/
	while(*(accountStr + i) != ' '){
		buffer[j] = accountStr[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	sscanf(buffer, " %lf", &account.balance);
	j = 0;
	i++;
	
	/*Account First Name*/
	while(*(accountStr + i) != ' '){
		buffer[j] = accountStr[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	sscanf(buffer, " %s", account.fname);
	j = 0;
	i++;
	
	/*Account Last Name*/
	while(*(accountStr + i) != '\n'){
		buffer[j] = accountStr[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
	sscanf(buffer, " %s", account.lname);
	
	free(buffer);
	return account;
}

/*******************************************************************************
* This function splits the string that holds account data into account fields.
* inputs:
* - Pointer to an Array of chars (char* jAccountStr)
* outputs:
* - Joint Account with filled in data (account_t)
Author: Ethan Goh
*******************************************************************************/
jointAccount_t jointAccountStringSplit(char* jAccountStr){
	/*
	WRITING FORMAT:
	FOR JOINT ACCOUNTS:
	1) ID1, ID2, PIN1, PIN2, BALANCE, FNAME1, LNAME1, FNAME2, LNAME2
	*/
	char bufferJ[75];
	jointAccount_t joint;
	int i = 0, j = 0;
	
	/*Account ID user 1*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %d", &joint.userID1);
	j = 0;
	i++;

	/*Account ID user 2*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %d", &joint.userID2);
	j = 0;
	i++;
	
	/*Account PIN user 1*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %d", &joint.userPin1);
	j = 0;
	i++;

	/*Account PIN user 2*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %d", &joint.userPin2);
	j = 0;
	i++;

	/*Account Balance*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %lf", &joint.balance);
	j = 0;
	i++;
	
	/*Account First Name User 1*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %s", joint.fname1);
	j = 0;
	i++;
	
	/*Account Last Name User 1*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %s", joint.lname1);
	j = 0;
	i++;
	
	/*Account First Name User 2*/
	while(*(jAccountStr + i) != ' '){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %s", joint.fname2);
	j = 0;
	i++;
	
	/*Account Last Name User 2*/
	while(*(jAccountStr + i) != '\n'){
		bufferJ[j] = jAccountStr[i];
		i++;
		j++;
	}
	bufferJ[j] = '\0';
	sscanf(bufferJ, " %s", joint.lname2);
	return joint;
}

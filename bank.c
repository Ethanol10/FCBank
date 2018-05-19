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

/*******************************************************************************
 * List structs
*******************************************************************************/
	/* User defined structs that are shared between the linked list and 
		this file are in the "linked_list_implementation.h" file. */

/*******************************************************************************
 * Function prototypes. As the project is being developed, more function 
 declarations may be added.
*******************************************************************************/
void addAccount(); 
void editAccount(); 
void removeAccount(); 
void addJointAccount();
void withdraw();
void deposit();
void transfer();
void encrypt();
void decrypt();
void compress();
void decompress();
void printMenu(int menuNo);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{	
	printMenu(1);
	printMenu(2);
	printMenu(3);
	printMenu(4);
	printMenu(100);
	
	
    return 0;     
}

/*******************************************************************************
 * This function prints the initial menu with a list of functions the user may
 choose to use
 * - none
 * outputs:
 * - a new account
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
			printf("1. Log in to existing account\n");
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
			printf("Creating Account: Type '!exit' at any time to quit\n");
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
 * This function adds an account to the system based on user input.
 * inputs:
 * - user details
 * outputs:
 * - a new account
 Author: Varun Sriram
*******************************************************************************/
void addAccount()
{
	
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
 * This function allows the user to make a new Joint account.
 * inputs:
 * user details
 * outputs:
 * - a new account(joint)
 Author: Ethan Goh
*******************************************************************************/
void JointAccount()
{

}

/*******************************************************************************
 * This function allows the user to withdraw money from their account 
 input.
 * inputs:
 * - amount the user wishes to withdraw
 * outputs:
 * - none
 Author: Emmanuel Tshuma
*******************************************************************************/
void withdraw()
{
	

}

/*******************************************************************************
 * This function allows the user to deposit money into their account.
 * inputs:
 * - amount the user wishes to deposit
 * outputs:
 * - none
 Author: Ngoc Thao Han Ho
*******************************************************************************/
void deposit()
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


#ifndef L_L_IMP   /* Guard */
#define L_L_IMP

#define MAX_NAME_LEN 11
/*******************************************************************************
 * List structs
*******************************************************************************/
struct account
{
	int id;
	int pin;
	double balance;	
	char fname[MAX_NAME_LEN] ;
	char lname[MAX_NAME_LEN] ;
};
typedef struct account account_t;

struct jointAccount
{
	int userID1;
	int userPin1;
	int userID2;
	int userPin2;
	double balance;
	char fname1[MAX_NAME_LEN] ;
	char lname1[MAX_NAME_LEN] ;
	char fname2[MAX_NAME_LEN] ;
	char lname2[MAX_NAME_LEN] ;
};
typedef struct jointAccount jointAccount_t;

struct nodeAcc
{
	account_t account;
	struct nodeAcc* nextNode;
};
typedef struct nodeAcc nodeAcc_t;

struct nodeJAcc
{
	jointAccount_t account;
	struct nodeJAcc* nextNode;
};
typedef struct nodeJAcc nodeJAcc_t;

/*******************************************************************************
 * Function prototypes. As the project is being developed, more function 
 declarations may be added.
*******************************************************************************/
void appendSingleAccNode(account_t accountS, nodeAcc_t* head);
void appendJointAccNode(jointAccount_t, nodeJAcc_t* head);
void removeSingleAccNode(account_t accountS, nodeAcc_t* head);
void removeJointAccNode(jointAccount_t accountJ, nodeJAcc_t* head);
nodeAcc_t* findSingleNode(int userID, nodeAcc_t* head); 
nodeJAcc_t* findJointNode(int userID, nodeJAcc_t* head);

#endif
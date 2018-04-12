#include<stdio.h>
#include<stdlib.h>

/*------------------------------------------------------------------------------------*/
// structure for transaction record.

struct transaction
{
 unsigned long amount;                           //amount to be debited from account
 unsigned char transaction_fee;                  //char can be used a integer with range 0-255. Transaction fee will not be greater than that.

 /* data types for 'public key' of reciever,
    'digital signature' of sender and 
    'time-stamp' yet to be declared.         */
 }; 

/*------------------------------------------------------------------------------------*/
//structure for hash node;

struct merkle
{
 unsigned short index;
 char hash[65];                                  //hash is 64 characters long. 1 byte for NULL charactere.
 struct transaction *data;
 struct merkle *left;
 struct merkle *right;
 } *root;


/*------------------------------------------------------------------------------------*/
unsigned short height;         //stores the height of the binary tree
unsigned short count;          //counts the total number of transactions. The ceil() of log of count, with base 2, will give the height of binary tree.
unsigned short c;

struct merkle* create_merkle();                       //function to dynamically allocate memory for data type merkle.
struct transaction* create_transaction();             //function to dynamically allocate memory for data type transaction.

/*function_by_shikhar: a function to be made by shikhar to list the names of files in current directory and count them*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/


int main()
{
 unsigned short i;
 
// height = log;

// for(i=0; i<n;)

c=0;
merkle_make(root,height,0); 



 return 0;
 }











/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
struct merkle* create_merkle()
{
 short i;
 struct merkle *ptr;
 ptr = NULL;
 ptr = (struct merkle*)malloc(sizeof(struct merkle));

 if(ptr == NULL)
  return ptr;

 for(i=0; i<66; i++, ptr->hash[i]='\0');

 ptr->data = NULL;
 ptr->left = NULL;
 ptr->right = NULL;

 return ptr;
 }
/*------------------------------------------------------------------------------------*/

struct transaction* create_transaction()
{
 struct transaction *ptr;
 ptr = NULL;
 ptr = (struct transaction*)malloc(sizeof(struct transaction));

 if(ptr == NULL)
  return ptr;

 ptr->amount = 0;
 ptr-> transaction_fee = 0;

 return ptr;
 }
/*------------------------------------------------------------------------------------*/

void merkle_make(struct merkle *head, unsigned short height, unsigned short h)
{
 if(c > count)  //'c' > 'count' means all transactions are listed in binary tree.
  return;

 if(h>height)   //if height is getting larger tha the height decided, then it will stop making new nodes and return.
  return;

 head = create_merkle();

 if(head == NULL)
 {
  printf("\n\n\tERROR: WHILE CREATING MERKLE TREE, AT HEIGHT %d",height);
  exit(1);
  }

 if(h == height)
 {
  head->data = create_transaction();
   if(head->data == NULL)
   {
    printf("\n\n\tERROR: WHILE CREATING TRANSACTION DATA, AT HEIGHT %d",height);
    exit(1);
    }
  }



 }



/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/

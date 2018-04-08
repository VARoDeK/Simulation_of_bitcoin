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
 unsigned short index.
 char hash[65];                                  //hash is 64 characters long. 1 byte for NULL charactere.
 struct transaction *data;
 struct merkle *next;
 };


/*------------------------------------------------------------------------------------*/

struct merkle* create_merkle(unsigned short index)
{
 short i;
 struct merkle *ptr;
 ptr = NULL;
 ptr = (struct merkle*)malloc(sizeof(struct merkle));

 if(ptr == NULL)
  return ptr;

 ptr->index = index;

 for(i=0; i<66; i++, ptr->hash[i]='\0');

 ptr->data = NULL;
 ptr->next = NULL;

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

void merkle_hash()
{
 system("ls *.btransaction > merkle_hash_temp.bcoin");

 char name[8][]
 }
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/

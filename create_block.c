#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>

#define FILE_SIZE 201                                                  //maximum length of filename
#define FOLDER_SIZE 51

char static_path[FOLDER_SIZE];           //to save path to betacoin folder

/*----------------------------------------------------------------------------------------------------------*/
struct block
{
 unsigned int magic_number;                    //to define that the file is a block of blockchain
 unsigned int block_size;                      //block size
 unsigned char previous_block_hash[65]; 
 unsigned char current_block_hash[65];       
 unsigned char merkle_hash[65];                
 unsigned long timestamp;                      
 unsigned long difficulty_target; //no_of_zeros
 unsigned long nonce;
 unsigned int no_of_transaction;
 }block_global;

/*----------------------------------------------------------------------------------------------------------*/
struct transaction
{
 unsigned char t_id[FILE_SIZE];                     //It is the name of transaction file (*.transaction) which is string concat of wallet_id+timestamp;                  
 long double amount;                                //amount to be debited from account
 unsigned char transaction_fee;                     //char can be used a integer with range 0-255. Transaction fee will not be greater than that.
 unsigned long timestamp;
 /* data types for 'public key' of reciever,
    'digital signature' of sender and         */
 }trans_global;

/*----------------------------------------------------------------------------------------------------------*/
char folder[FOLDER_SIZE];
char filename[FILE_SIZE];                                                   //will save the name of transaction file, which is read from "a.txt", which is to be opened.

char miner[] = "/miner/";
char sha[] = "/sha/";
void full_path(char[],char[]); 


FILE *fpg, *fp;                                                                 //"fpg" to open list.txt, "fp" to open transaction files.



/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

void prerun_setup()
{
 strcpy(folder , getenv("HOME")); //sets folder to "/home/<user-name>" in linux and "/Users/<user-name>" for OSX.
 strcat(folder , "/betacoin");    //sets folder to "/home/<user-name>/betacoin" in linux and "/Users/<user-name>/betacoin" for OSX. 



 FILE *fp;



 block_global.magic_number = 0x54fc7f8e;
 
 }
/*----------------------------------------------------------------------------------------------------------*/
void full_path(char subd[],char a[])
{
 unsigned short i;
 char temp[FILE_SIZE];

 for(i=0; ;i++)
 {
  if(a[i]=='\0')
  {
   if(a[i-1] == '\n')
    a[i-1] = '\0';
   break;
   }
  }

 strcpy(temp , folder);
 strcat(temp , subd);
 strcat(temp , a);
 strcpy(a , temp);
 }
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

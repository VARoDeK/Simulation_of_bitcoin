/*
This program is to recalaculate the balance of user.
This will read the blocks of blockchain.
if you have paid the amount, figure will get deducted from your wallet.
if you have recieved the amount, figure will get added in your wallet.
if you have mined the block, 1 betacoin will be added in your account.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"betacoin.h"

 
/*--------------------------------------------------------------------*/
struct user user_global;
struct block block_global;
struct transaction trans_global;
FILE *fp, *fpg;
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

int main()
{
 unsigned long num,i;
 unsigned short j;
 long double user_balance = (long double)1000; //1000 is the minimum amount required to open account.
 long double trans_fee = (long double)1;   //or mining reward
/*
hence inititally all users have 1000 betacoin, then we can read from genesis block and can calculate balance.
*/

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");

 strcpy(filename , "sha.256");
 full_path(binary , filename);

printf("\n Reading user details..");
 fp = fopen(filename , "rb");
  if(fp == NULL)
  {
   printf("\n\tERROR: Couldn't read user details to recalaculate balance.");
   exit(1);
   } 
 fread(&user_global , sizeof(struct user) , 1 , fp);
 fclose(fp);

/*--no of blocks-------------*/
 printf("\n Reading number of blocks present in blockchain..");
 strcpy(filename , "no_of_blocks.txt");
 full_path(blockchain , filename);
 fp = fopen(filename , "rb");
    if(fp == NULL)
    {
     printf("\n ERROR: Could not open %s to read number of blocks." , filename);
     exit(1);
     }
  fscanf(fp , "%lu" , &num);
  fclose(fp);

/*--calculate balance--------*/
printf("\n Current Balance: %Lf" , user_balance);
 strcpy(filename , "block_list.txt");
 full_path(blockchain , filename);

  fpg = fopen(filename , "r");
    if(fpg == NULL)
    {
     printf("\n ERROR: Could not open %s to read list of blocks." , filename);
     exit(1);
     }

  for(i = 0 ; i < num ; i++)
  {
   fscanf(fpg , "%s" , filename);
   full_path(blockchain , filename);

  printf("\n Opening block: %s" , filename);
   fp = fopen(filename , "rb");
       if(fp == NULL)
       {
        printf("\n ERROR: Could not open %s to read block." , filename);
        exit(1);
        }

   fread(&block_global , sizeof(struct block) , 1 , fp);

   if(strcmp(block_global.miner_id , user_global.wallet_id) == 0)
   {
    user_balance += trans_fee;
   line();
    printf("\n You have mined the block: %s: +1.0" , filename);
    printf("\n Balance: %Lf" , user_balance);
   line();
    }

   for(j = 0 ; j< block_global.no_of_transaction ; j++)
   {
    fread(&trans_global , sizeof(struct transaction) , 1, fp);
    if(strcmp(trans_global.sender_id , user_global.wallet_id) == 0)
    {
     line(); 
     user_balance -= trans_global.amount;
     user_balance -= trans_fee;
      printf("\n You paid %Lf to %s" , trans_global.amount , trans_global.reciever_id);
      printf("\n Transaction fee: %Lf" , (long double)1);
      printf("\n Balance: %Lf" , user_balance);
     line();
     } 

    if(strcmp(trans_global.reciever_id , user_global.wallet_id) == 0)
    {
     user_balance -= trans_global.amount;
     line();
      printf("\n You recieved %Lf from %s" , trans_global.amount , trans_global.sender_id);
      printf("\n Balance: %Lf" , user_balance);
     line();
     }
    }

   fclose(fp);
   }
  fclose(fpg);


printf("\n Your current balance is: %Lf" , user_balance);

 user_global.account_balance = user_balance;
 strcpy(filename , "sha.256");
 full_path(binary , filename);
 fp = fopen(filename , "wb");
    if(fp == NULL)
    {
     printf("\n ERROR: Could not open %s to write recalculated balance." , filename);
     exit(1);
     }
  fwrite(&user_global , sizeof(struct user) , 1 , fp);
  fclose(fp);
 }
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

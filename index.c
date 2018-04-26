#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"betacoin.h"


char ch;                         //variable to store user options
char account;                    //flag to check if account is created or not
FILE *fp, *fpg;

char option();
void prerun_setup();              //defines some specific values to variables before running program
void display_options();           //displays all options to the user
void read_user_details();         //reads user details from the system



/*-------options--------------------------*/
void call_create_account();       //to run the program for creating account
void mine();                      //to mine
void recalculate_balance();       //it will recalculate balance of user.
/*----------------------------------------------------------------------------------*/
struct user user_global;
struct block block_global;
struct transaction trans_global;
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
int main()
{
 char t;
 prerun_setup();

 if(account == 0)
  call_create_account();
 
 read_user_details();



re1:
  display_options();
  re2:
   printf("\n\t\tEnter your option: ");
   fflush(stdin);  
   ch = getchar();
    
   t = 0;
    while(t != '\n')
     t = getchar();
  
  if (ch == 'B' || ch == 'b')
  {
   line();
   printf("\n\tName: %s" , user_global.name);
   printf("\n\tLocation: %s" , user_global.location);
   printf("\n\tUsername@Hostname: %s" , user_global.user_and_hostname);
   printf("\n\tEmail: %s" , user_global.email);
   printf("\n\tTime of creation: %ld seconds since 1970-01-01 00:00:00 UTC" , user_global.timestamp);
   line();
   goto re1;
   }  

  else if(ch == 'D' || ch == 'd')
  {
   mine();
     if(user_global.miner_flag == 0)
      goto re1;
   system("~/betacoin/binary/create_block");
   system("~/betacoin/binary/send_newblock.c");
   goto re1;
   }

 else if(ch == 'E' || ch == 'e')
 {
  user_global.miner_flag = 1;
  strcpy(filename , "sha.256");
  full_path(binary , filename);

  fp = fopen(filename , "wb");
      if(fp == NULL)
      {
       printf("\n Error: Could not open %s to become miner." , filename);
       exit(1);
       }
  fwrite(&user_global , sizeof(struct user) , 1 , fp);
  fclose(fp);
  } 

 else if(ch == 'F' || ch == 'f')
 {
  line();
  printf("\tAre your sure, you want to delete your account?");
  printf("\n\tEnter 'C' to confirm.");
  printf("\n\tEnter 'N' to go back to main menu.");

  repl:
   fflush(stdin);
   ch = getchar();
       t = 0;
    while(t != '\n')
     t = getchar();

    if(ch == 'C' || 'c')
    {
       strcpy(filename , "sha.256");
       full_path(binary , filename);
       remove(filename);
       exit(1);
     }

    else if(ch == 'N' || ch == 'n')
     goto re1;

   else
    goto repl;
  } 


 else if(ch == 'G' || ch == 'g')
 {
  line();
  printf("\n\tADD A NEW MINER");
  line();
  if (system("~/betacoin/binary/add_a_new_miner") != 0)
   exit(1);
  }

 

 else if(ch == 'Q' || ch == 'q')
  exit(0);

  else
   goto re2;

 }

/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

char option()
{
 char a;
 fflush(stdout);
 fflush(stdin);
 scanf("%c" , &a);
 return a;
 }
/*----------------------------------------------------------------------------------*/

void prerun_setup()
{
 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin/binary/");

 account = 0;

 strcpy(filename , folder);
 strcat(filename , "sha.256");
 fp = fopen(filename , "rb");
  if(fp == NULL)
   account = 0;
  else
  { 
   account = 1;
   fclose(fp);
   }


 }
/*----------------------------------------------------------------------------------*/
void read_user_details()
{
 FILE *fp;

 strcpy(filename , folder);
 strcat(filename , "sha.256");
 fp = fopen(filename , "rb");
  if(fp == NULL)
  {
   printf("\n\tERROR: COULD NOT READ USER DETAILS");
   return;
   }
 
 fread(&user_global , sizeof(struct user) , 1 , fp);
 fclose(fp);
 }
/*----------------------------------------------------------------------------------*/
void display_options()
{
line();
printf("\nWALLET ID: %s" , user_global.wallet_id);
line();

printf("\n\n\tEnter 'A' to check your balance.");
printf("\n\n\tEnter 'B' to check your user details.");
printf("\n\n\tEnter 'C' to make a transaction.");
printf("\n\n\tEnter 'D' to mine.");
printf("\n\n\tEnter 'E' to become a new miner.");
printf("\n\n\tEnter 'F' to delte your account.");
printf("\n\n\tEnter 'G' to add a new miner");
printf("\n\n\tEnter 'H' to add a benificiary");
printf("\n\n\tEnter 'I' to check order of benificiary");
printf("\n\n\tEnter 'J' to re-run first_run setup");
printf("\n\n\tEnter 'K' to recalculate balance from transaction history.");
printf("\n\n\tEnter 'L' to synchronize");
printf("\n\n\tEnter 'M' to verify a miner's block");
printf("\n\n\tEnter 'Q' to leave this portal and exit.");
 }

/*----------------------------------------------------------------------------------*/
void call_create_account()
{
 char t;
   line();
  printf("\n\tPLEASE CREATE AN BETACOIN ACCOUNT.");
  printf("\n\t\tEnter 'A' to create.");
  printf("\n\t\tEnter 'E' to exit.\n");

  re:
   printf("\n\t\t\tEnter your choice: ");
   fflush(stdin);
   ch = getchar();
     t = 0;
    while(t != '\n')
     t = getchar();

    if(ch == 'A' || ch == 'a')
    {
     if(system("~/betacoin/binary/create_account") != 0)
       exit(1);
     else
     {
      account = 1;
      read_user_details();
      }
     }

    else if(ch == 'E' || ch == 'e')
     exit(1);

    else
     goto re;

 }
/*------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
void mine()
{
 if(user_global.miner_flag == 0)
 {
  line();
  printf("\n\n\tYOU ARE NOT A MINER.");
  printf("\n\n\t\tPLEASE APPLY TO BECOME A MINER.");
  line();
  return;
  }
 

 }
/*----------------------------------------------------------------------------------*/

void recalculate_balance()
{
 strcpy(filename , "sha.256");
 full_path(binary , filename);

 unsigned long num,i;
 unsigned short j;
 long double user_balance = user_global.account_balance;

 printf("\n Reading user Details..");
 fp = fopen(filename , "rb");
    if(fp == NULL)
    {
     printf("\n ERROR: Could not open %s to read user details" , filename);
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
user_balance = (long double)0;

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
   fscanf(fpg , "%[^\n]s" , filename);
   full_path(blockchain , filename);

   fp = fopen(filename , "rb");
       if(fp == NULL)
       {
        printf("\n ERROR: Could not open %s to read block." , filename);
        exit(1);
        }

   fread(&block_global , sizeof(struct block) , 1 , fp);

   if(strcmp(block_global.miner_id , user_global.wallet_id) == 0)
    user_balance += (long double)1;

   for(j = 0 ; j< block_global.no_of_transaction ; j++)
   {
    fread(&trans_global , sizeof(struct user) , 1, fp);
    if(strcmp(trans_global.sender_id , user_global.wallet_id) == 0)
     user_balance -= trans_global.amount;

    if(strcmp(trans_global.reciever_id , user_global.wallet_id) == 0)
     user_balance -= trans_global.amount;
    }

   fclose(fp);

   }
  fclose(fpg);

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

/*----------------------------------------------------------------------------------*/


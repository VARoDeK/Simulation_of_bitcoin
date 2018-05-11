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

  if(ch == 'A' || ch == 'a')
  {
   if(system("~/betacoin/binary/synchronize") != 0)
    exit(1); 
   /*
     - first call the function to recalculate balance
     - then read the modified user_details from the file
     - and store in user_global
    */ 
   if(system("~/betacoin/binary/recalculate_balance") != 0)
    exit(1);

   read_user_details();
   goto re1;
   }
  
  else if (ch == 'B' || ch == 'b')
  {
   read_user_details();
   line();
   printf("\n\tName: %s" , user_global.name);
   printf("\n\tLocation: %s" , user_global.location);
   printf("\n\tUsername@Hostname: %s" , user_global.user_and_hostname);
   printf("\n\tEmail: %s" , user_global.email);
   printf("\n\tTime of creation: %ld seconds since 1970-01-01 00:00:00 UTC" , user_global.timestamp);
   line();
   goto re1;
   }  


  else if(ch == 'C' || ch == 'c')
  {
   if(system("~/betacoin/binary/make_transaction") != 0)
     exit(1);
   goto re1;
   }


  else if(ch == 'D' || ch == 'd')
  {
   mine();
     if(user_global.miner_flag == 0)
      goto re1;
   if(system("~/betacoin/binary/create_block") != 0)
     exit(1);
   
   if(system("~/betacoin/binary/send_newblock") != 0)
     exit(1);
   goto re1;
   }

 else if(ch == 'E' || ch == 'e')
 {
  read_user_details();
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
 goto re1;
  } 

 else if(ch == 'F' || ch == 'f')
 {
  line();
  printf("\n\tAre your sure, you want to delete your account? YOU WILL LOOSE ALL YOUR BETACOINS FOREVER.");
  printf("\n\tEnter 'C' to confirm.");
  printf("\n\tEnter 'N' to go back to main menu.");
  
  repl:
   fflush(stdin);
    printf("\n\t\tEnter your choice: ");

   ch = getchar();
       t = 0;
    while(t != '\n')
     t = getchar();

    if(ch == 'C' || ch == 'c')
    {
       strcpy(filename , "sha.256");
       full_path(binary , filename);
       remove(filename);
       system("rm ~/betacoin/miner/*");
       line();
       printf("\n\tACCOUNT SUCCESSFULLY DELETED");
       line(); 
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
  if (system("~/betacoin/binary/miner_menu") != 0)
   exit(1);
  goto re1;
  }


else if(ch == 'I' || ch == 'i')
{
 if(system("~/betacoin/binary/synchronize") !=0)
  exit(1);
 goto re1;
 }


else if(ch == 'J' || ch == 'j')
{ 
 if(system("~/betacoin/binary/verify_block") != 0)
  exit(1);

 else
  system("rm ~/betacoin/verify/*");

 goto re1;
 }


 else if(ch == 'K' || ch == 'k')
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
 strcat(folder , "/betacoin");

 account = 0;

 strcpy(filename , "sha.256");
 full_path(binary , filename);
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

 strcpy(filename , "sha.256");
 full_path(binary , filename);
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
printf("\n\n\tEnter 'G' to add/ delete/ display miners.");
printf("\n\n\tEnter 'I' to synchronize");
printf("\n\n\tEnter 'J' to verify a miner's block");
printf("\n\n\tEnter 'K' to leave this portal and exit.");
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

/*----------------------------------------------------------------------------------*/


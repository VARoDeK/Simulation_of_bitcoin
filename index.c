#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void line()
{ 
 printf("\n------------------------------------------------------------------");
 }

char ch;                         //variable to store user options
char account;                    //flag to check if account is created or not
FILE *fp;

char option();
void prerun_setup();              //defines some specific values to variables before running program
void display_options();           //displays all options to the user
void read_user_details();         //reads user details from the system



/*-------options--------------------------*/
void call_create_account();       //to run the program for creating account
void mine();                      //to mine

/*----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
int main()
{
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

  if(ch == 'A' || ch == 'a')
  {}
  else if (ch == 'B' || ch == 'b')
  {
   line();
   printf("\n\tName: %s" , user_global.name);
   printf("\n\tLocation: %s" , user_global.location);
   printf("\n\tUsername@Hostname: %s" , user_global.user_and_hostname);
   printf("\n\tEmail: %s" , user_global.email);
   printf("\n\tTime of creation: %ld seconds since 1970-01-01 00:00:00 UTC" , user_global.timestamp);
   line();
   getchar();
   goto re1;
   }  

  else if(ch == 'D' || ch == 'd')
  {
   mine();
   getchar();
   goto re1;
   }


  else
  {
   getchar();
   goto re2;
   }

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
printf("\n\n\tEnter 'Q' to leave this portal and exit.");

 }

/*----------------------------------------------------------------------------------*/
void call_create_account()
{
   line();
  printf("\n\tPLEASE CREATE AN BETACOIN ACCOUNT.");
  printf("\n\t\tEnter 'A' to create.");
  printf("\n\t\tEnter 'E' to exit.\n");

  re:
   printf("\n\t\t\tEnter your choice: ");
   fflush(stdin);
   ch = getchar();

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
    {
     getchar();
     goto re;
     }

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

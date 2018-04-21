#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FOLDER_SIZE 51
#define FILE_SIZE 201

void line()
{ 
 printf("\n------------------------------------------------------------------");
 }

char ch;                         //variable to store user options
char account;                    //flag to check if account is created or not
char password;                   //flag to check if passord is set or not
char pass[FILE_SIZE];            //to in put password
char folder[FOLDER_SIZE];
char filename[FILE_SIZE];
FILE *fp;
char miner[] = "/miner/";
char sha[] = "/sha/";

char option();
void prerun_setup();              //defines some specific values to variables before running program
void display_options();           //displays all options to the user
void read_user_details();         //reads user details from the system
void full_path(char[],char[]);    //gives full path to the file
void call_create_account();       //to run the program for creating account
short security_check();
/*----------------------------------------------------------------------------------*/
struct user
{
 char wallet_id[71];              //strcat(timestamp + md5(name,timestamp,location,user_and_hostname,email))
 char name[51];
 unsigned long timestamp;
 char location[51];
 char user_and_hostname[51];      //for my system: varodek@varodek.local
 char email[51];      
 }user_global;


/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
int main()
{
 prerun_setup();

 if(password == 0)
 {
  if(system("~/betacoin/binary/create_account") != 0)
   exit(1);
  prerun_setup();
  }


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

 strcpy(filename , folder);
 strcat(filename , "md.5");
 fp = fopen(filename , "r");
  if(fp == NULL)
   password = 0;
  else
  {
   password = 1;
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
printf("\n\n\tEnter 'C' to mkae a transaction.");
printf("\n\n\tEnter 'D' to mine.");
printf("\n\n\tEnter 'E' to delte your account.");
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

/*----------------------------------------------------------------------------------*/
short security_check()
{

 }
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

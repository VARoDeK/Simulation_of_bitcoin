#include<stdio.h>
#include<stdlib.h>

#define FOLDER_SIZE 51
#define FILE_SIZE 201

void line()
 printf("\n------------------------------------------------------------------");


char ch;
char account;
char folder[FOLDER_SIZE];
char filename[FILE_SIZE];

char option();
void prerun_setup();
void display_options();
/*----------------------------------------------------------------------------------*/
struct user
{
 char wallet_id[71];
 char name[51];
 unsigned long timestamp;
 char location[51];
 char user_and_hostname[51];
 char email[51];
 }user_global;


/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
int main()
{
 prerun_setup();

 if(account == 0)
 {
  line();
  printf("\n\tPlease create an Betacoin account");
  printf("\n\t\tEnter A to ")
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
 FILE fp;

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin/binary/");

 account = 0;

 strcpy(filename , folder);
 strcat(filename , "sha.256");
 fp = fopen(filename , "rb");
  if(fp == NULL)
  {
   account = 0;
   return;
   }


 }
/*----------------------------------------------------------------------------------*/
void display_option()
{


 }
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>
#include"betacoin.h"

struct user user_global;


/*------------------------------------------------------------------------------*/
char ch;
char account;           //to know if account exists or not.
char tempstring[71];
void input();
void display_details();
void correction(char []); 
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

int main()
{
 FILE *fp;
 struct timeval tv;
 char temp[FOLDER_SIZE];
 char t;

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");
/*-------Account--------------------------------------*/
 account = 0;
 strcpy(filename , folder);
 strcat(filename , "/binary/sha.256");

 fp = fopen(filename , "rb");
  if(fp != NULL)
  {
   line();
   printf("\n\n\t\tERROR: USER ACCOUNT ALREADY EXISTS.\n");
   line();
   fclose(fp);
   return 1;
   }
 
re1:
 line();
   input();
 line();
  printf("\n\t\tCONFIRM");
 line();
  display_details();
 line();
  printf("\n\n\tEnter 'C' to confirm.");
  printf("\n\n\tEnter 'R' to re-enter.");
  printf("\n\n\tEnter 'E' to discard and exit.\n");
 re2:
  printf("\n\t\tEnter your choice: ");
  fflush(stdin);
  ch = getchar();
    t = 0;
   while(t != '\n')
     t = getchar();
   if(ch == 'C' || ch == 'c')
    goto write;

   else if(ch == 'R' || ch == 'r')
    goto re1;

   else if(ch == 'E' || ch == 'e')
    exit(1);

   else 
    goto re2;

 write:
  gettimeofday(&tv , NULL);
  user_global.timestamp = (unsigned long)tv.tv_sec;
  user_global.account_balance = (long double)1000;
/*-writing input.txt--------------------------------*/
  strcpy(filename , folder);
  strcat(filename , "/sha/input.txt");
  fp = fopen(filename , "w");
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s..\n" , filename);
           line();
           exit(1);
            }

  fprintf(fp,"%lu\n%s%s%s%s" , user_global.timestamp , user_global.location , user_global.name , user_global.email , user_global.user_and_hostname);
  fclose(fp);

  system("python3 ~/betacoin/binary/MD5_function_DUP.py");

/*-reading input.txt-------------------------------*/
  fp = fopen(filename , "r");
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s..\t" , filename);
           line();
           exit(1);
            }

  fscanf(fp , "%s" , tempstring);
  fclose(fp);


/*-reading output.txt-------------------------------*/
  strcpy(filename , folder);
  strcat(filename , "/sha/output.txt");

  fp = fopen(filename , "r");
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s..\n" , filename);
           line();
           exit(1);
            }

  fscanf(fp , "%s" , user_global.wallet_id);
  fclose(fp);

 strcat(user_global.wallet_id , tempstring);


 user_global.miner_flag = 0;
/*-writing user details------------------------------*/
  strcpy(filename , folder);
  strcat(filename , "/binary/sha.256");
  fp = fopen(filename , "wb");
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s..\n" , filename);
           line();
           exit(1);
            }
  fwrite(&user_global , sizeof(struct user) , 1 , fp);
  fclose(fp);

 account = 1;

line();
line();
printf("\n\tACCOUNT SUCCESSFULLY CREATED.");
line();
line();

display_details();
line();

return 0;



 }
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

void input()
{
 short temp;
 char c,t;

 line();
 printf("\n\t\tACCOUNT CREATION: ENTER DETAILS");
 line();
 printf("\n\tEnter your name: ");
 fflush(stdin);
 scanf("%[^\n]" , user_global.name);
     t = 0;
   while(t != '\n')
     t = getchar();


// getchar();
 printf("\n\tEnter location: ");
 fflush(stdin);
 scanf("%[^\n]" , user_global.location);

     t = 0;
   while(t != '\n')
     t = getchar();
 
// getchar();
 printf("\n\tEnter email-id: ");
 fflush(stdin);
 scanf("%[^\n]", user_global.email);

    t = 0;
   while(t != '\n')
     t = getchar();

 getlogin_r(user_global.user_and_hostname, NAME_SIZE);
 strcat(user_global.user_and_hostname , "@");
 gethostname(tempstring , NAME_SIZE);
 strcat(user_global.user_and_hostname , tempstring);

#ifdef __linux__
 strcat(user_global.user_and_hostname , ".local");
#endif
 }

/*------------------------------------------------------------------------------*/
void display_details()
{
 if(account != 0)
  printf("\nWallet id: %s" , user_global.wallet_id);
 printf("\nName: %s" , user_global.name);
 if(account != 0)
  printf("\ntimestamp: %lu" , user_global.timestamp);
 printf("\nlocation: %s" , user_global.location);
 printf("\nuser and hostname: %s" , user_global.user_and_hostname);
 printf("\nemail: %s" , user_global.email);
 if(account != 0)
  printf("\naccount balance: %LF" , user_global.account_balance);
 }

/*------------------------------------------------------------------------------*/
void correction(char a[])
{
 short i;
 for(i= 0 ; a[i] != '\0' ; i++)
  if(a[i] == '\n')
   a[i] = '\0';
 }
/*------------------------------------------------------------------------------*/

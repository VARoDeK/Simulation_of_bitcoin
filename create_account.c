#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>

#define FOLDER_SIZE 51
#define FILE_SIZE 201

void line()
{ 
 printf("\n------------------------------------------------------------------\n"); 
 }


struct user
{
 char wallet_id[71];
 char name[51];
 unsigned long timestamp;
 char location[51];
 char user_and_hostname[51];
 char email[51];
 }user_global;


/*------------------------------------------------------------------------------*/
char folder[FOLDER_SIZE];
char filename[FILE_SIZE];
char ch;
char account;           //to know if account exists or not.
char tempstring[51];
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

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");
/*-------Account--------------------------------------*/
 account = 0;
 strcpy(filename , folder);
 strcat(filename , "/binary/sha.256");

 fp = fopen(filename , "rb");
  if(fp != NULL)
  {
   printf("\n\n\t\tERROR: USER ACCOUNT ALREADY EXISTS.");
   fclose(fp);
   return 1;
   }
 
re1:
 line();
   input();
 line();
  printf("\t\tCONFIRM");
 line();
  display_details();
 line();
  printf("\n\n\tEnter 'C' to confirm.");
  printf("\n\n\tEnter 'R' to re-enter.");
  printf("\n\n\tEnter 'E' to discard and exit.\n");
 re2:
  printf("\n\t\tEnter your choice: ");
  fflush(stdin);
  ch = fgetc(stdin);
   if(ch == 'C' || ch == 'c')
    goto write;

   else if(ch == 'R' || ch == 'r')
   {
    getchar();
    goto re1;
    }

   else if(ch == 'E' || ch == 'e')
    exit(1);

   else 
   {
    getchar();
    goto re2;
    }

 write:
  gettimeofday(&tv , NULL);
  user_global.timestamp = (unsigned long)tv.tv_sec;

/*-writing input.txt--------------------------------*/
  strcpy(filename , folder);
  strcat(filename , "/sha/input.txt");
  fp = fopen(filename , "w");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s.." , filename);
           exit(1);
            }

  fprintf(fp,"%lu\n%s%s%s%s" , user_global.timestamp , user_global.location , user_global.name , user_global.email , user_global.user_and_hostname);
  fclose(fp);

  system("python3 ~/betacoin/binary/MD5_function_DUP.py");

/*-reading input.txt-------------------------------*/
  fp = fopen(filename , "r");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s.." , filename);
           exit(1);
            }

  fscanf(fp , "%s" , user_global.wallet_id);
  fclose(fp);


/*-reading output.txt-------------------------------*/
  strcpy(filename , folder);
  strcat(filename , "/sha/output.txt");

  fp = fopen(filename , "r");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s.." , filename);
           exit(1);
            }

  fscanf(fp , "%s" , tempstring);
  fclose(fp);

 strcat(user_global.wallet_id , tempstring);

/*-writing user details------------------------------*/
  strcpy(filename , folder);
  strcat(filename , "/binary/sha.256");
  fp = fopen(filename , "wb");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s.." , filename);
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
 char c;

 line();
 printf("\t\tACCOUNT CREATION: ENTER DETAILS");
 line();
 printf("\n\tEnter your name: ");
 fflush(stdin);
 fgets(user_global.name , 51 ,stdin);
 correction(user_global.name);

// getchar();
 printf("\n\tEnter location: ");
 fflush(stdin);
 fgets(user_global.location , 51 ,stdin);
 correction(user_global.location);
 
// getchar();
 printf("\n\tEnter email-id: ");
 fflush(stdin);
 fgets(user_global.email , 51 ,stdin);
 correction(user_global.email);

 getlogin_r(user_global.user_and_hostname, 51);
 strcat(user_global.user_and_hostname , "@");
 gethostname(tempstring , 51);
 strcat(user_global.user_and_hostname , tempstring);
 strcat(user_global.user_and_hostname , ".local");
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

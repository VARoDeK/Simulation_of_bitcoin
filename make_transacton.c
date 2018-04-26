#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include"betacoin.h"


/*------------------------------------------------------------------------*/
long double user_balance;

struct block block_global;
struct transaction trans_global;
struct user user_global;
char tempstring[FILE_SIZE];
FILE *fp;
/*------------------------------------------------------------------------*/
void prerun_setup();
void display_user_details();
void display_transaction_details();

/*
We made functions to display user details and transaction details, each of them having seperate lines of code to read details from file,
so as we can confirm that data was properly written on file.

*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
int main()
{
 char t, ch;
 struct timeval tv;

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");


display_user_details();
start:
 line();
 printf("\n\t\t\t\tPAY");
 line();
  printf("\n\n\tEnter the reciever's wallet id: ");
  scanf("%[^\n]s" , trans_global.reciever_id);
   t = 0;
   while(t != '\n')
    t = getchar();

re:
  printf("\n\tEnter the amount to be paid: ");
  scanf("%LF" , &trans_global.amount);
   if(trans_global.amount > (user_global.account_balance -1))
    {
     printf("\n\n\t\tYOU DON'T HAVE ENOUGH BALANCE.\n");
     goto re;
     }
     t = 0;
   while(t != '\n')
     t = getchar();




 strcpy(trans_global.sender_id , user_global.wallet_id);
  
 gettimeofday(&tv , NULL);
 trans_global.timestamp = (unsigned long)tv.tv_sec;

 trans_global.transaction_fee = 1;
 trans_global.amount += (long double)1;

 printf("\n\n\tReciever's Wallet id: %s" , trans_global.reciever_id);
 printf("\n\tAmount to be paid: %Lf" , trans_global.amount);
 printf("\n\tTransaction fee: %Lf" , (long double)trans_global.transaction_fee);

 line();
  printf("\n\t\t\t\tCONFIRM");
 line();
  printf("\n\tEnter 'C' to confirm");
  printf("\n\tEnter 'R' to re-enter");
  printf("\n\tEnter 'E' to discard and exit");
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
    goto start;

   else if(ch == 'E' || ch == 'e')
    exit(1);

   else
    goto re2;

 write:
  strcpy(filename , "input.txt");
  full_path(sha , filename);
printf("\n Opening %s for writing.." , filename);
  fp = fopen(filename , "w");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s.." , filename);
           exit(1);
            }

  fprintf(fp,"%lu" , trans_global.timestamp);
  fclose(fp);

printf("\n Opening %s for reading.." , filename);
  fp = fopen(filename , "r");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s.." , filename);
           exit(1);
            }

  fscanf(fp , "%s" , tempstring);
  fclose(fp);

 strcat(tempstring , user_global.wallet_id);
 strcpy(trans_global.t_id , tempstring);
 strcat(tempstring , ".transaction");
 full_path(miner , tempstring);
//since tempstring is gobally defined, the adddress stored in it can be used by read_transaction_details() function also.



printf("\n%s" , trans_global.t_id);
 fp = fopen(tempstring , "wb");
    if(fp == NULL)
    {
     printf("\n ERROR: Could not open %s to write." , filename);
     exit(1);
     }
 fwrite(&trans_global , sizeof(struct transaction) , 1 , fp);
 fclose(fp);      

user_global.account_balance -= trans_global.amount;

strcpy(filename , "sha.256");
full_path(binary , filename);
 fp = fopen(filename , "wb");
    if(fp == NULL)
    {
     printf("\n ERROR: Could not open %s to write." , filename);
     exit(1);
     }
 fwrite(&user_global , sizeof(struct user) , 1 , fp);
 fclose(fp);

display_user_details();
display_transaction_details();

 }

/*------------------------------------------------------------------------*/
void display_user_details()
{
 strcpy(filename , "sha.256");
 full_path(binary , filename);

 printf("\n Reading user Details..");
 fp = fopen(filename , "rb");
    if(fp == NULL)
    {
     printf("\n ERROR: Could not open %s to read user details" , filename);
     exit(1);
     }
  fread(&user_global , sizeof(struct user) , 1 , fp);
  fclose(fp);
line();
 printf("\n\t\tModified User Details");
line();
  printf("\n Wallet id: %s" , user_global.wallet_id);
 printf("\n Name: %s" , user_global.name);
  printf("\n timestamp: %lu" , user_global.timestamp);
 printf("\n location: %s" , user_global.location);
 printf("\n user and hostname: %s" , user_global.user_and_hostname);
 printf("\n email: %s" , user_global.email);
  printf("\n account balance: %LF" , user_global.account_balance);
line();
 }

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/

void display_transaction_details()
{
 printf("\n Reading transction Details..");
 fp = fopen(tempstring , "rb");
    if(fp == NULL)
    {
     printf("\n ERROR: Could not open %s to read user details" , filename);
     exit(1);
     }
  fread(&trans_global , sizeof(struct transaction) , 1 , fp);
  fclose(fp);
line();
 printf("\n\t\tTransaction Details");
line();
  printf("\n Transaction id: %s" , trans_global.t_id);
 printf("\n Sender's ID: %s" , trans_global.sender_id);
  printf("\n timestamp: %lu" , trans_global.timestamp);
 printf("\n Reciever ID: %s" , trans_global.reciever_id);
 printf("\n Amount: %LF" , trans_global.amount);
 printf("\n Transaction fee: %LF" , (long double)trans_global.transaction_fee);
line();

 }
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*
-This program will allow user to make transaction.
-This program will be called by index.c but before calling this, index.c should call recalculate_balnce() function to know correct current balance of user.
-The transaction fee for each transaction is 1 betacoin.
-The t_id (transaction id) of transaction will be strcat(timestamp + wallet_id of user).
-The name of transaction file will be t_id.transaction. (t_id means strcat(timestamp + wallet_id of user)).
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include"betacoin.h"


/*------------------------------------------------------------------------*/
struct block block_global;
struct transaction trans_global;
struct user user_global;
struct beneficiary ben, ben2;
struct timeval tv;
/*------------------------------------------------------------------------*/

char tempstring[FILE_SIZE];     //use to store temporary filename.
char filename[FILE_SIZE], tempfile1[FILE_SIZE], tempfile2[FILE_SIZE];
char ch, t;
FILE *fp;
unsigned short i;
unsigned long num;
/*------------------------------------------------------------------------*/

void display_user_details();
void display_transaction_details();
void add_beneficiary();
void display_beneficiary();
void delete_beneficiary();
void transaction();
/*
We made functions to display user details and transaction details, each of them having seperate lines of code to read details from file,
so as we can confirm that data was properly written on file.

*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*
- first call display_user_details(), this will not only show details of user but also save it in object, trans_global.
- then ask for reciever_id of reciever, this is the wallet id of reciever.
- then ask for amount that has to be paid. if your balance is less than (amount+transaction_fee), it wont allow transaction.
- then asks for confirmation.
- once confirmed, deducts the amount from user's balance. else exit the program.
- calculates timestamp which is in form "unsigned long" and writes it to ~/betacoin/sha/input.txt.
- then reads than timestamp and stores it in the form of string, so as to calculate t_id. (t_id = strcat(timestamp+wallet_id)).
- then writes the transaction record in t_id.transaction file.
- then again calls display_user_details(); and display_transaction_details(). These two program open specific files, read them and print.
- reading records from file, ensures that file was properly written, or else it would have not read it properly.
*/

int main()
{
 char t, ch;

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");

 system("~/betacoin/binary/recalculate_balance");
 display_user_details();                                         //display_user_details

 strcpy(filename , "no_of_beneficiary.txt");
 full_path(binary , filename);

 fp = fopen(filename , "rb");
 if(fp == NULL)
  num = 0;
 else
 {
  fscanf(fp , "%lu" , &num);
  fclose(fp);
  }


 start:
  line();
  printf("\n\t\tMINER MENU");
  line();

  printf("\n\tEnter 'T' to make a transaction.");
  printf("\n\tEnter 'V' to view Beneficiary ID and their details.");
  printf("\n\tEnter 'A' to add a Beneficiary.");
  printf("\n\tEnter 'D' to delete a Beneficiary.");
  printf("\n\tEnter 'E' to exit.");

   re:
    printf("\n\t\tEnter your choice: ");
    fflush(stdin);
    ch = getchar();
      t = 0;
     while(t != '\n')
      t = getchar();

     if(ch == 'T' || ch == 't')
     {
      transaction();
      goto start;
      }

     else if(ch == 'V' || ch == 'v')
     {
      display_beneficiary();
      goto start;
      }

     else if(ch == 'A' || ch == 'a')
     {
      add_beneficiary();
      goto start;
      }

     else if(ch == 'D' || ch == 'd')
     {
      delete_beneficiary();
      goto start;
      }

    else if(ch == 'E' || ch == 'e')
    {
     return 0;
     }

    else
    goto re;



}
/*--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------*/
void transaction()
{
 unsigned short j,i;
 start:
 line();
 printf("\n\t\t\t\tPAY");
 line();
  printf("\n\n\tEnter the Beneficiary's ID: ");              //asking for reciever's wallet id
  scanf("%hu" , &j);
   t = 0;
   while(t != '\n')
    t = getchar();

     if(j >= num)
     {
      printf("\n\tINVALID BENEFICIARY ID.");
      printf("\n\tYou are requested to opt to \"Display List of beneficiary\" and see BENEFICIARY ID from there.");
      return;
      }

re:
  printf("\n\tEnter the amount to be paid: ");                   //amount to be paid
  scanf("%LF" , &trans_global.amount);
   if(trans_global.amount > (user_global.account_balance -1))
    {
     printf("\n\n\t\tYOU DON'T HAVE ENOUGH BALANCE.\n");
     goto re;
     }
     t = 0;
   while(t != '\n')
     t = getchar();


 strcpy(filename , "list_of_beneficiary.txt");
 full_path(binary , filename);
 fp = fopen(filename , "rb");
 if(fp == NULL)
 {
  line();
  printf("\n\n\tERROR: Could not open %s to read.\n" , filename);
  line();
  exit(1);
  }

 for(i = 0 ; i<=j ; i++)
  fread(&ben , sizeof(struct beneficiary) , 1 , fp);

 strcpy(trans_global.reciever_id , ben.account_no);
 strcpy(trans_global.sender_id , user_global.wallet_id);          //sender's id is same as wallet id of user
  
 gettimeofday(&tv , NULL);
 trans_global.timestamp = (unsigned long)tv.tv_sec;               //calculated timestamp

 trans_global.transaction_fee = 1;                                //included transaction fee

 printf("\n\n\tReciever's Wallet id: %s" , trans_global.reciever_id);
 printf("\n\tAmount to be paid: %Lf" , trans_global.amount);
 printf("\n\tTransaction fee: %Lf" , (long double)trans_global.transaction_fee);
 printf("\n\tTotal amount to be deducted: %LF" , trans_global.amount+(long double)1);
 line();
  printf("\n\t\t\t\tCONFIRM");
 line();
  printf("\n\tEnter 'C' to confirm");
  printf("\n\tEnter 'R' to re-enter");
  printf("\n\tEnter 'E' to discard and return");
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
    return;

   else
    goto re2;

 write:
/*-----------------------------------------------------------------*/
  strcpy(filename , "input.txt");                                   //writing timestamp to ~/betacoin/sha/input.txt in unsigned long format
  full_path(sha , filename);
 printf("\n Opening %s for writing.." , filename);
  fp = fopen(filename , "w");
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s..\n" , filename);
           line();
           exit(1);
            }

  fprintf(fp,"%lu" , trans_global.timestamp);
  fclose(fp);
/*-----------------------------------------------------------------*/
printf("\n Opening %s for reading.." , filename);
  fp = fopen(filename , "r");                                       //reading timestamp from ~/betacoin/sha/input.txt in string format
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s..\n" , filename);
           line();
           exit(1);
            }

  fscanf(fp , "%s" , tempstring);
  fclose(fp);

/*-----------------------------------------------------------------*/
 strcat(tempstring , user_global.wallet_id);
 strcpy(trans_global.t_id , tempstring);
 strcat(tempstring , ".transaction");
 full_path(miner , tempstring);
//since tempstring is gobally defined, the adddress stored in it can be used by read_transaction_details() function also.



printf("\n%s" , trans_global.t_id);
 fp = fopen(tempstring , "wb");
    if(fp == NULL)
    {
     line();
     printf("\n\n\tERROR: Could not open %s to write.\n" , filename);
     line();
     exit(1);
     }
 fwrite(&trans_global , sizeof(struct transaction) , 1 , fp);
 fclose(fp);      

user_global.account_balance -= trans_global.amount;                //amount deducted
user_global.account_balance -= (long double)1;                     //transaction fee deducted

strcpy(filename , "sha.256");
full_path(binary , filename);
 fp = fopen(filename , "wb");
    if(fp == NULL)
    {
     line();
     printf("\n\n\tERROR: Could not open %s to write.\n" , filename);
     line();
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
     line();
     printf("\n\n\t ERROR: Could not open %s to read user details\n" , filename);
     line();
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
     line();
     printf("\n\n\tERROR: Could not open %s to read user details.\n" , tempstring);
     line();
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

void display_beneficiary()
{
 if(num == 0)
 {
  printf("\n\tNO Beneficiary IN YOUR LIST.");
  return;
  }


 strcpy(filename , "list_of_beneficiary.txt");
 full_path(binary , filename);

 fp = fopen(filename , "r");
  if(fp == NULL)
  {
   line();
   printf("\n\n\t\tERROR: Could not open %s to read.\n" , filename);
   line();
   exit(1);
   }

for(i = 0; i < num ; i++)
{
 fread(&ben , sizeof(struct beneficiary) , 1 , fp);
 line();
  printf("\n Beneficiary ID: %hu" , i);
  printf("\n Beneficiary name: %s", ben.name);
  printf("\n Comments: %s" , ben.comment);
 }

fclose(fp);
 }




/*------------------------------------------------------------------------*/

void delete_beneficiary()
{
FILE *fp1;
 unsigned short j;

  start:
 line();
  printf("\n\tEnter Beneficiary ID to delete: ");
   scanf("%hu", &j);

      t = 0;
     while(t != '\n')
      t = getchar();


     if(j >= num)
     {
      printf("\n\tINVALID BNEFICIARY ID.");
      printf("\n\tYou are requested to opt to \"Display List of Beneficiaries\" and see BENEFICIARY ID from there.");
      return;
      }

  line();
  printf("\n\t\tCONFIRM");
  line();
//After that it will open file to check list that which miner, user wants to delete.
 strcpy(filename , "list_of_beneficiary.txt");
 full_path(binary , filename);

 fp = fopen(filename , "r");
  if(fp == NULL)
  {
   line();
   printf("\n\n\t\tERROR: Could not open %s to read.\n" , filename);
   line();
   exit(1);
   }

for(i = 0; i < num ; i++)
{
 fread(&ben , sizeof(struct beneficiary) , 1 , fp);
  if(i == j)
    break;
 }

printf("\n BENEFICIARY record will be deleted");
printf("\n Beneficiary name: %s" , ben.name);
printf("\n Beneficiary account number: %s" , ben.account_no);

  printf("\n\tEnter 'C' to confirm and save.");
  printf("\n\tEnter 'R' to re-enter.");
  printf("\n\tEnter 'E' to discard and return.");

   re:
    printf("\n\t\tEnter your choice: ");
    fflush(stdin);
    ch = getchar();
      t = 0;
     while(t != '\n')
      t = getchar();
     if(ch == 'C' || ch == 'c')
      goto del;

     else if(ch == 'R' || ch == 'r')
     {
      line();
      goto start;
      }

     else if(ch == 'E' || ch == 'e')
     {
      fclose(fp);
      return;
      }

    else
     goto re;

del:
fseek(fp , 0 , SEEK_SET);

 strcpy(tempfile1 , "temp.txt");
 full_path(binary , tempfile1);

 fp1 = fopen(tempfile1 , "w");
  if(fp == NULL)
  {
   line();
   printf("\n\n\t\tERROR: Could not open %s to write.\n" , tempfile1);
   line();
   exit(1);
   }

for(i = 0 ; i<num ; i++)
{
 fread(&ben , sizeof(struct beneficiary) , 1 , fp);
 if(i != j)
 fwrite(&ben , sizeof(struct beneficiary) , 1 , fp1);
 }
fclose(fp);
fclose(fp1);


num--;
 strcpy(tempfile2 , "no_of_beneficiary.txt");
 full_path(binary , tempfile2);

 fp = fopen(tempfile2 , "w");
 if(fp == NULL)
 {
   line();
   printf("\n\n\t\tERROR: Could not open %s to write.\n" , tempfile2);
   line();
   exit(1);
  }

fprintf(fp , "%lu" , num);
fclose(fp);


remove(filename);
rename(tempfile1 , filename);


printf("\n\tSUCCESSFULLY DELETED");

}

/*------------------------------------------------------------------------*/

void add_beneficiary()
{
 start:
line();
  printf("\n\tEnter the name of beneficiary: ");
   scanf("%[^\n]s", ben.name);
       t = 0;
     while(t != '\n')
      t = getchar();

  printf("\n\tEnter the account number/ wallet Id of beneficiary: ");
   scanf("%[^\n]s", ben.account_no);
       t = 0;
     while(t != '\n')
      t = getchar();

  printf("\n\tEnter any comments (max 500 characters): ");
   scanf("%[^\n]s", ben.comment);
       t = 0;
     while(t != '\n')
      t = getchar();



  line();
  printf("\n\t\tCONFIRM");
  line();

  printf("\n\tEnter 'C' to confirm and save.");
  printf("\n\tEnter 'R' to re-enter.");
  printf("\n\tEnter 'E' to discard and exit.");

   re:
    printf("\n\t\tEnter your choice: ");
    fflush(stdin);
    ch = getchar();
      t = 0;
     while(t != '\n')
      t = getchar();
     if(ch == 'C' || ch == 'c')
      goto sav;

     else if(ch == 'R' || ch == 'r')
     {
      line();
      goto start;
      }

     else if(ch == 'E' || ch == 'e')
     {
      exit(1);
      }

    else
     goto re;

sav:
 strcpy(filename , "list_of_beneficiary.txt");
 full_path(binary , filename);

fp = fopen(filename , "a");
fclose(fp);
/*
The above command was writtten for a purpose.
as next lines check if hostname already exist in record, the file should be present, or else fp will be NULL and we won't be able to know why.
so opening in append mode will create file if it does not exist, or if it exists, it will no truncate the data.
*/

 fp = fopen(filename , "rb");
  if(fp == NULL)
  {
   line();
   printf("\n\n\t\tERROR: Could not open %s to read.\n" , filename);
   line();
   exit(1);
   }

for(i = 0; i < num ; i++)
{
 fread(&ben2 , sizeof(struct beneficiary) , 1 , fp);
 if(strcmp(ben2.account_no , ben.account_no) == 0)
 {
  fclose(fp);
  printf("\n\tBENEFICIARY ACCOUNT NUMBER IS ALREADY IN THE RECORD.\n");
  line();
  goto start;
  }
 }
fclose(fp);



 fp = fopen(filename , "ab");
  if(fp == NULL)
  {
   line();
   printf("\n\n\t\tERROR: Could not open %s to append.\n" , filename);
   line();
   fclose(fp);
   exit(1);
   }
 fwrite(&ben , sizeof(struct beneficiary) , 1 , fp);
 num++;
fclose(fp);

 strcpy(filename , "no_of_beneficiary.txt");
 full_path(binary , filename);
 fp = fopen(filename , "w");
  if(fp == NULL)
  {
   line();
   printf("\n\n\t\tERROR: Could not open %s.\n" , filename);
   line();
   fclose(fp);
   exit(1);
   }
 fprintf(fp , "%lu" , num);
fclose(fp);


printf("\n\n");
line();
printf("\n\t\tBENEFICIARY SUCCESSFULLY ADDED TO YOUR LIST");
line();
printf("\n Beneficiary name: %s" , ben.name);
printf("\n Beneficiary account no: %s" , ben.account_no);
printf("\n Comments: %s" , ben.comment);
printf("\n Beneficiary ID on your system: %lu" , num-1);
line();
 }


/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

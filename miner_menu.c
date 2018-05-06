#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"betacoin.h"


/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
 char ch,t;
 FILE *fp;
 unsigned short num = 0, i;
 char host[NAME_SIZE], temp[NAME_SIZE], tempfile1[FILE_SIZE], tempfile2[FILE_SIZE];



void add_a_new_miner();
void display_miner();
void delete_miner();

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
int main()
{
 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");
 
 strcpy(filename , "no_of_miners.txt");
 full_path(miner , filename);

 fp = fopen(filename , "r");
 if(fp == NULL)
  num = 0;
 else
 {
  fscanf(fp , "%hu" , &num);
  fclose(fp);
  }

 start:
  line();
  printf("\n\t\tMINER MENU");
  line();

  printf("\n\tEnter 'V' to view miner ID and their hostname.");
  printf("\n\tEnter 'A' to add a miner.");
  printf("\n\tEnter 'D' to delete a miner.");
  printf("\n\tEnter 'E' to exit.");

   re:
    printf("\n\t\tEnter your choice: ");
    fflush(stdin);
    ch = getchar();
      t = 0;
     while(t != '\n')
      t = getchar();
     if(ch == 'V' || ch == 'v')
     {
      display_miner();
      goto start;
      }

     else if(ch == 'A' || ch == 'a')
     {
      add_a_new_miner();
      goto start;
      }

     else if(ch == 'D' || ch == 'd')
     {
      delete_miner();
      goto start;
      }

    else if(ch == 'E' || ch == 'e')
    {
     return 0;
     }

    else
     goto re;

}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/


void add_a_new_miner()
{
 start:
line();
  printf("\n\tEnter <user_name>@hostname of miner: ");
   scanf("%[^\n]s", host);
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
 strcpy(filename , "list_of_miners.txt");
 full_path(miner , filename);

fp = fopen(filename , "a");
fclose(fp);
/*
The above command was writtten for a purpose.
as next lines check if hostname already exist in record, the file should be present, or else fp will be NULL and we won't be able to know why.
so opening in append mode will create file if it does not exist, or if it exists, it will no truncate the data.
*/

 fp = fopen(filename , "r");
  if(fp == NULL)
  {
   printf("\n\n\t\tERROR: Could not open %s to read." , filename);
   exit(1);
   }

for(i = 0; i < num ; i++)
{
 fscanf(fp , "%s" , temp);
 if(strcmp(host , temp) == 0)
 {
  fclose(fp);
  printf("\n\tMINER IS ALREADY IN THE RECORD.\n");
  line();
  goto start;
  }
 }
fclose(fp);



 fp = fopen(filename , "a");
  if(fp == NULL)
  {
   printf("\n\n\t\tERROR: Could not open %s to append." , filename);
   fclose(fp);
   exit(1);
   }
 fprintf(fp , "%s\n" , host);
 num++;
fclose(fp);
 
 strcpy(filename , "no_of_miners.txt");
 full_path(miner , filename);
 fp = fopen(filename , "w");
  if(fp == NULL)
  {
   printf("\n\n\t\tERROR: Could not open %s." , filename);
   fclose(fp);
   exit(1);
   }
 fprintf(fp , "%hu" , num);
fclose(fp);


printf("\n\n");
line();
printf("\n\t\tMINER SUCCESSFULLY ADDED TO YOUR LIST");
line();
printf("\n Miner: %s" , host);
printf("\n Miner ID on your system: %hu" , num-1);
line();



 }

/*------------------------------------------------------------------*/
void display_miner()
{
 if(num == 0)
 {
  printf("\n\tNO MINER IN YOUR LIST.");
  return;
  }

 
 strcpy(filename , "list_of_miners.txt");
 full_path(miner , filename);

 fp = fopen(filename , "r");
  if(fp == NULL)
  {
   printf("\n\n\t\tERROR: Could not open %s to read." , filename);
   exit(1);
   }

for(i = 0; i < num ; i++)
{
 fscanf(fp , "%s" , temp);
 line();
 printf("\n\tMINER ID: %hu" , i);
 printf("\n\tMINER:     %s" , temp);
 }

fclose(fp);


 }




/*------------------------------------------------------------------*/
void delete_miner()
{
FILE *fp1;
 unsigned short j;

  start:
 line();
  printf("\n\tEnter Miner ID to delete: ");
   scanf("%hu", &j);

      t = 0;
     while(t != '\n')
      t = getchar();


     if(j >= num)
     {
      printf("\n\tINVALID MINER ID.");
      printf("\n\tYou are requested to opt to \"Display List of Miners\" and see MINER ID from there.");
      return;
      }      
 
  line();
  printf("\n\t\tCONFIRM");
  line();
//After that it will open file to check list that which miner, user wants to delete.
 strcpy(filename , "list_of_miners.txt");
 full_path(miner , filename);

 fp = fopen(filename , "r");
  if(fp == NULL)
  {
   printf("\n\n\t\tERROR: Could not open %s to read." , filename);
   exit(1);
   }

for(i = 0; i < num ; i++)
{
 fscanf(fp , "%s" , temp);
  if(i == j)
    break;
 }

printf("\n MINER record will be deleted: %s\n\n" , temp);

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
 full_path(miner , tempfile1);
 
 fp1 = fopen(tempfile1 , "w");
  if(fp == NULL)
  {
   printf("\n\n\t\tERROR: Could not open %s to write." , tempfile1);
   exit(1);
   }

for(i = 0 ; i<num ; i++)
{
 fscanf(fp , "%s" , temp);
 if(i != j)
 fprintf(fp1 , "%s\n" , temp);
 }
fclose(fp);
fclose(fp1);


num--;
 strcpy(tempfile2 , "no_of_miners.txt");
 full_path(miner , tempfile2);

 fp = fopen(tempfile2 , "w");
 if(fp == NULL)
 {
   printf("\n\n\t\tERROR: Could not open %s to write." , tempfile2);
   exit(1);
  }

fprintf(fp , "%hu" , num);
fclose(fp);


remove(filename);
rename(tempfile1 , filename);


printf("\n\tSUCCESSFULLY DELETED");



}

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/

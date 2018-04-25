#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"betacoin.h"


/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
int main()
{
 char ch;
 FILE fp;
 unsigned short num = 0;
 char host[NAME_SIZE];

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");

 strcpy(filename , "no_of_miners.txt")
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
  printf("\n\tEnter <user_name>@hostname of miner: ");
   scanf("%[^\n]s" host);
  line();
  printf("\t\tCONFIRM");
  line();

  printf("\n\tEnter 'C' to confirm and save.");
  printf("\n\tEnter 'R' to re-enter.");
  printf("\n\tEnter 'E' to discard and exit.");
   
   re:
    printf("\n\t\tEnter your choice: ");
    fflush(stdin);
    ch = getchar();
     while(getchar() != '\n');
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

 }

/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/
/*------------------------------------------------------------------*/

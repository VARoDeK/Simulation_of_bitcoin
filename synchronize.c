#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"betacoin.h"

/*------------------------------------------------------------------------------*/

FILE *fp;
char **hosts;

unsigned short no_of_hosts;
char block_name[FILE_SIZE];

void prerun_setup();
void generate_command(unsigned short , unsigned short);
void read_block();
/*------------------------------------------------------------------------------*/
struct block block_global;
struct transaction trans_global;
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/


int main()
{
unsigned long i , j , temp1, temp2;
system("rm ~/betacoin/verify/*");       //to delete all useless files, if present, inside verify folder
prerun_setup();

srand(time(0));
i = rand()%no_of_hosts;//call files from ay random miner

generate_command( i , 1);
printf("\n %s",command);
system(command);

strcpy(filename , "no_of_blocks.txt");
full_path(verify , filename);
 fp = fopen(filename , "r");
         if(fp == NULL)
         {
          printf("\n ERROR: Could not open: %s." , filename);
          exit(1);
          }
 fscanf(fp , "%lu" , &temp1);
 fclose(fp);
  
strcpy(filename , "no_of_blocks.txt");
full_path(blockchain , filename);
 fp = fopen(filename , "r");
         if(fp == NULL)
         {
          printf("\n ERROR: Could not open: %s." , filename);
          exit(1);
          }
 fscanf(fp , "%lu" , &temp2);
 fclose(fp);

if(temp1 == temp2)
{
 line();
 printf("\n\t\t\tYOUR CHAIN IS UP TO DATE");
 line();
 exit(0);
 }


else
{
 generate_command( i , 2);
 printf("\n %s", command);

 strcpy(filename , "block_list.txt");
 full_path(verify , filename);
 
  fp = fopen(filename , "r");
         if(fp == NULL)
         {
          printf("\n ERROR: Could not open: %s." , filename);
          exit(1);
          }
 
 for(j = 0; j< temp2 ; j++)
  fscanf(fp , "%s" , block_name);

 for( ; j< temp1 ; j++)
 {
  fscanf(fp , "%s" , block_name);
  strcpy(command , "scp ");
  strcat(command , hosts[i]);
  strcat(command , ":~/betacoin/BLOCKCHAIN/");
  strcat(command , block_name);

  strcat(command , " ");
  strcat(command , "~/betacoin/BLOCKCHAIN/");

  printf("\n %s",command);
  //system(command);


  } 

 fclose(fp);


 strcpy(filename , "no_of_blocks.txt");
 full_path(blockchain , filename);

  fp = fopen(filename , "w");
         if(fp == NULL)
         {
          printf("\n ERROR: Could not open: %s." , filename);
          exit(1);
          }
fprintf(fp , "%lu" , temp1);
fclose(fp);


generate_command( i , 2);
printf("\n %s",command);
//system(command);


 
system("rm ~/betacoin/BLOCKCHAIN/block_list.txt");
system("mv ~/betacoin/verify/block_list.txt ~/betacoin/BLOCKCHAIN/block_list.txt");
 

 }

}
 
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

void prerun_setup()
{
 unsigned short i;

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");

 strcpy(filename , "no_of_miners.txt");
 full_path(miner , filename);

 printf("\n Reading number of host names of miners saved in your system..");
 fp = fopen(filename , "r");
         if(fp == NULL)
         {
          printf("\n ERROR: Could not open: %s\n Maybe no record for any miner exists. Add miners to your list first." , filename);
          exit(1);
          }
  fscanf(fp , "%hu" , &no_of_hosts);
  fclose(fp);
 printf("\n Creating dynamic memory, for saving host names of miners..");

 hosts = (char**)malloc(sizeof(char*) * no_of_hosts);

 for(i = 0 ; i < no_of_hosts ; i++)
  hosts[i] = (char*)malloc(sizeof(char) * NAME_SIZE);

/*--read name of hosts.------------------------------------*/
 printf("\n Reading hostnames of miners..");

 strcpy(filename , "list_of_miners.txt");
 full_path(miner , filename);

 fp = fopen(filename , "r");
         if(fp == NULL)
         {
          printf("\n ERROR: Could not open: %s\n Maybe no record for any miner exists. Add miners to your list first." , filename);
          exit(1);
          }
 for(i = 0 ; i < no_of_hosts ; i++)
 {
  fscanf(fp , "%s" , hosts[i]);
  }
fclose(fp);

 }

/*------------------------------------------------------------------------------*/
void generate_command(unsigned short i, unsigned short flag)
{
 strcpy(command , "scp ");
 strcat(command , hosts[i]);
 strcat(command , ":~/betacoin/BLOCKCHAIN/");

 if(flag == 0)
  strcat(command , block_name);
 else if(flag == 1)
  strcat(command , "no_of_blocks.txt");
 else if(flag == 2)
  strcat(command , "block_list.txt");

 strcat(command , " ");
 strcat(command , "~/betacoin/verify/");
 }

/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

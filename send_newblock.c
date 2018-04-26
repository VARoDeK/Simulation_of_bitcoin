#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"betacoin.h"

FILE *fp;
char **hosts;

unsigned short no_of_hosts;
char block_name[FILE_SIZE];

void prerun_setup();
void generate_command(unsigned short , unsigned short);
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

int main()
{
 unsigned short i , j;
 system("~/betacoin/binary/create_list_of_new_blocks");
 prerun_setup();

 for(i = 0 ; i< no_of_hosts ; i++)
 {
  for(j = 0 ; j < 3 ; j++)
  {
   generate_command(i ,j);
   printf("\n%s", command);
//   system(command);
   }

  }

 }
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

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


/*--read name of block to be sent.------------------------------------*/
 printf("\n Reading name of block..");

 strcpy(filename , "list_of_new_blocks.txt");
 full_path(miner , filename);

 fp = fopen(filename , "r");
         if(fp == NULL)
         {
          printf("\n ERROR: Could not open: %s." , filename);
          exit(1);
          }
  fscanf(fp , "%s" , block_name);
fclose(fp);


 }

/*--------------------------------------------------------------------*/

void generate_command(unsigned short i, unsigned short flag)
{
 strcpy(command , "scp ");
 strcat(command , "~/betacoin/miner/");

 if(flag == 0)
  strcat(command , block_name);
 else if(flag == 1)
  strcat(command , "list_of_new_blocks.txt");
 else if(flag == 2)
  strcat(command , "no_of_new_blocks.txt");

 strcat(command , " ");
 strcat(command , hosts[i]);
 strcat(command , ":~/betacoin/verify/");

 }

/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

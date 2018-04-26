#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include"betacoin.h"

void create_genesis_block_hash();

FILE *fpg, *fp;                                                                 //"fpg" to open list.txt, "fp" to open transaction files.
struct block block_global;

/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

int main()
{
 short i;
 struct timeval tv;
 unsigned long time1 , time2;

 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");



 strcpy(filename , "block_list.txt");
 full_path(blockchain , filename);

 fp = fopen(filename , "r");
 if(fp != NULL)
 {
  printf("\n\n\t Genesis Block Exists.\n");
  fclose(fp);
  return 1;
  }
 
 printf("\n Writing record for genesis block in blocklist.txt..");
 fp = fopen(filename , "w");
      if(fp == NULL)
      {
       printf("\n\n ERROR: Could not open %s...\n", filename);
       return 1;
       }

  strcpy(filename , "0.block");
  fprintf(fp , "%s\n" , filename);
  fclose(fp);

 printf("\n Written record for genesis block in blocklist.txt..");



 strcpy(filename , "no_of_blocks.txt");
 full_path(blockchain , filename);
 fp = fopen(filename , "w");
      if(fp == NULL)
      {
       printf("\n\n ERROR: Could not open %s...\n", filename);
       return 1;
       }
  fprintf(fp , "%lu" , (unsigned long)0);
  fclose(fp);




 printf("\n Assigning Values to Variables in the Block..");
  block_global.magic_number = 0x54fc7f8e;
  block_global.block_size = sizeof(struct block);
  block_global.previous_block_hash[0] = '\0';
  block_global.merkle_hash[0] = '\0';
  block_global.no_of_transaction = 0; 


/*--read block_global.difficulty_target---------------------------------------------*/
 strcpy(filename , "difficulty_target.txt");
 full_path(miner , filename);
 fp = fopen(filename , "r");
       if(fp == NULL)
       {
        printf("\n\tERROR: COULD NOT OPEN %s TO READ DIFFICULTY TARGET." , filename);
        exit(1);
        }
 printf("\n Reading Difficulty Target From %s.." , filename);
 fscanf(fp , "%lu" , &(block_global.difficulty_target));
 fclose(fp);


 gettimeofday(&tv , NULL);
 block_global.timestamp = (unsigned long)tv.tv_sec;
 printf("\n Calculated timestamp..");

  printf("\n Calculating Hash..");
   gettimeofday(&tv , NULL);
   time1 = (unsigned long)tv.tv_sec;
 create_genesis_block_hash();
   gettimeofday(&tv , NULL);
   time2 = (unsigned long)tv.tv_sec;

 block_global.time_taken = (unsigned int)(time2 - time1);


 printf("\n OPERATION SUCCESSFUL. Current Block Hash Calculated..");
 printf("\nCurrent Block Hash: %s" , block_global.current_block_hash);
 printf("\nNonce code: %lu" , block_global.nonce);
 printf("\nTime Taken: %u sec" , block_global.time_taken);
 printf("\nTimestap: %lu sec" , block_global.timestamp);

   strcpy(filename , "0.block");
  full_path(blockchain , filename);
  fp = fopen(filename , "wb");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s." , filename);
           exit(1);
            }
  fwrite(&block_global , sizeof(struct block) , 1 , fp);

  printf("\n Written Block Header to %s.." , filename);
  fclose(fp);

  printf("\n New Block Created at %s.." , filename);


 }
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------*/

void create_genesis_block_hash()
{
 short i;
 char flag , count , p;
 unsigned long nonce;
 FILE *fp;

 flag = 0;
 p = 0;
 printf("\n Calculating SHA256 Of Current Block");


 for(nonce = 0 ; ; nonce++)
 {
  if(flag != 0)
   return;

  if(p != 0 && nonce == 0)
  {
   printf("\n\tERROR: THE CYCLE OF unsigned long nonce HAS COMPLETED.");
   exit(1);
   }

 p = 1;

  strcpy(filename , "input.txt");
  full_path(sha , filename);
  fp = fopen(filename , "w");
            if(fp == NULL)
            {
             printf("\nERROR: COULD NOT OPEN %s TO CALCULATE NONCE." , filename);
             exit(1);
             }
   fprintf(fp , "%u" , block_global.magic_number);
   fprintf(fp , "%u" , block_global.block_size);
   fprintf(fp , "%s" , block_global.previous_block_hash);
   fprintf(fp , "%s" , block_global.merkle_hash);
   fprintf(fp , "%lu" , block_global.timestamp);
   fprintf(fp , "%lu" , block_global.difficulty_target);
   fprintf(fp , "%lu" , nonce);
   fprintf(fp , "%hu" , block_global.no_of_transaction);
/*
- we will not take, current_block_hash into account for creating current_block_has :P , this is why it was not written into input.txt.
- time taken will also not be counted to same.
- these two things will be ommited for verfying also, in verify_block.c.
- nonce will work faster than block_global.nonce.
*/

  fclose(fp);

 system("python3 ~/betacoin/binary/SHA_function_DUP.py");

  strcpy(filename , "output.txt");
  full_path(sha , filename);
  fp = fopen(filename , "r");
            if(fp == NULL)
            {
             printf("\nERROR: COULD NOT OPEN %s TO CALCULATE NONCE." , filename);
             exit(1);
             }
  fscanf(fp , "%[^\n]s" , block_global.current_block_hash);
  fclose(fp);

  flag = 1;

  for(i = 0 ; i < block_global.difficulty_target ; i++)
   if(block_global.current_block_hash[i] != '0')
    {
     flag = 0;
     block_global.nonce = nonce;
     }


   }

                                                                                                                                                       }
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/













#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include"betacoin.h"

/*----------------------------------------------------------------------------------------------------------*/
FILE *fpg, *fp;                                                                 //"fpg" to open list.txt, "fp" to open transaction files.
void prerun_setup();
void read_transaction_files();
void create_current_block_hash();
void display_block();
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
char tempstring[FILE_SIZE];
struct transaction *trans_global;
struct block block_global, prev_block;
struct user user_global;
unsigned long bb;                                   //no of blocks in blockchain
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
int main()
{
 FILE *fp;
 short i;
 struct timeval tv;
 unsigned long time1 , time2;

 printf("\n\n CREATING BLOCK..\n");

 system("~/betacoin/binary/merkle_tree");
 
 prerun_setup();

 read_transaction_files();

 printf("\n Calculating Hash..");
   gettimeofday(&tv , NULL);
   time1 = (unsigned long)tv.tv_sec;
 create_current_block_hash();
   gettimeofday(&tv , NULL);
   time2 = (unsigned long)tv.tv_sec;

 block_global.time_taken = (unsigned int)(time2 - time1);
   

 printf("\n OPERATION SUCCESSFUL. Current Block Hash Calculated..");
 printf("\nCurrent Block Hash: %s" , block_global.current_block_hash);
 printf("\nNonce code: %lu" , block_global.nonce); 
 printf("\nTime Taken: %u sec" , block_global.time_taken);
 printf("\nTimestap: %lu sec" , block_global.timestamp);
 printf("\nMiner id: %s", block_global.miner_id);



 /*--Naming the newly created block----------------------------------*/
 strcpy(filename , "input.txt");
 full_path(sha , filename);
 fp = fopen(filename , "w");
         if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s FOR WRITING.\n" , filename);
           line();
           exit(1);
            }
 fprintf(fp , "%lu" , block_global.timestamp);
 fclose(fp);

 
  fp = fopen(filename , "r");
         if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s FOR WRITING.\n" , filename);
           line();
           exit(1);
            }
 fscanf(fp , "%s" , filename);
 fclose(fp);




/*--Writng-------------------------------------------------------*/
  strcat(filename , user_global.wallet_id);
  strcat(filename , ".newblock");
  full_path(miner , filename);
  fp = fopen(filename , "wb");
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s.\n" , filename);
           line();
           exit(1);
            }
  fwrite(&block_global , sizeof(struct block) , 1 , fp);

  printf("\n Written Block Header to %s.." , filename);
  for(i = 0 ; i < block_global.no_of_transaction ; i++)
  {
   fwrite(&(trans_global[i]) , sizeof(struct transaction) , 1 , fp);
   printf("\n Written %s to %s.." , trans_global[i].t_id , filename);
   }
  fclose(fp);

  printf("\nNew Block Created at %s.." , filename);

line();
// display_block();

 free(trans_global);
 printf("\n Freed the dynamic array, created for storing transaction records.");
 }
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

void prerun_setup()
{
 FILE *fp;
 struct timeval tv;
 unsigned long i;

 strcpy(folder , getenv("HOME")); //sets folder to "/home/<user-name>" in linux and "/Users/<user-name>" for OSX.
 strcat(folder , "/betacoin");    //sets folder to "/home/<user-name>/betacoin" in linux and "/Users/<user-name>/betacoin" for OSX. 

 strcpy(filename , "count_no_of_files_in_block.txt");
 full_path(miner , filename);
 fp = fopen(filename , "r");
       if(fp == NULL)
       {
        line();
        printf("\n\n\tERROR: COULD NOT OPEN %s TO READ NO OF TRANSACTIONS.\n" , filename);
        line();
        exit(1);
        }
 printf("\n Reading Count Of Transaction Files From %s.." , filename);
 fscanf(fp , "%hu" , &(block_global.no_of_transaction));
 fclose(fp);

/*--read block_global.merkle_hash---------------------------------------------*/

 strcpy(filename , "merkle_sha.txt");
 full_path(miner , filename);
 fp = fopen(filename , "r");
       if(fp == NULL)
       {
        line();
        printf("\n\n\tERROR: COULD NOT OPEN %s TO READ MERKLE SHA.\n" , filename);
        line();
        exit(1);
        }
 printf("\n Reading Merkle Hash From %s.." , filename);
 fscanf(fp , "%[^\n]s" , block_global.merkle_hash);
 fclose(fp);


/*--read block_global.difficulty_target---------------------------------------------*/
 strcpy(filename , "difficulty_target.txt");
 full_path(miner , filename);
 fp = fopen(filename , "r");
       if(fp == NULL)
       {
        line();
        printf("\n\n\tERROR: COULD NOT OPEN %s TO READ DIFFICULTY TARGET.\n" , filename);
        line();
        exit(1);
        }
 printf("\n Reading Difficulty Target From %s.." , filename);
 fscanf(fp , "%lu" , &(block_global.difficulty_target));
 fclose(fp);


 gettimeofday(&tv , NULL);
 block_global.timestamp = (unsigned long)tv.tv_sec;
 printf("\n Calculated timestamp..");
 
 block_global.block_size = sizeof(struct block) + block_global.no_of_transaction * sizeof(struct transaction);
 printf("\n Caluclated Block Size");

// printf("count : %lu", block_global.difficulty_target); 
  
 printf("\n Alloted Magic Number..");
 block_global.magic_number = 0x54fc7f8e;

 trans_global = (struct transaction*)malloc(sizeof(struct transaction) * block_global.no_of_transaction);
 printf("\n Allocated Memory For Array Of struct transaction..");

//different algo will be written to create previous block hash after creation of genesis block.
 strcpy(block_global.previous_block_hash , "temp");

 block_global.time_taken = 0;



/*--read user details-----------------------------------------------------*/
 strcpy(filename , "sha.256");
 full_path(binary , filename);
 fp = fopen(filename , "rb");
       if(fp == NULL)
       {
        line();
        printf("\n\n\tERROR: COULD NOT OPEN %s TO READ USER DETAILS.\n" , filename);
        line();
        exit(1);
        }
 printf("\n Reading User Details From %s.." , filename);
 fread(&user_global , sizeof(struct user) , 1 , fp);
 fclose(fp);
/*--Miner ID-------------------------------------------------------------*/
strcpy(block_global.miner_id , user_global.wallet_id);


/*--Reading Previous Block Hash---------------------------------------------*/
 strcpy(filename , "no_of_blocks.txt");
 full_path(blockchain , filename);
 fp = fopen(filename , "r");
       if(fp == NULL)
       {
        line();
        printf("\n\n\tERROR: COULD NOT OPEN %s TO READ PREVIOUS BLOCK.\n" , filename);
        line();
        exit(1);
        }

 printf("\n Reading Number of Blocks %s.." , filename);
 fscanf(fp , "%lu" , &bb);
 fclose(fp);


 strcpy(filename , "block_list.txt");
 full_path(blockchain , filename);
 fp = fopen(filename , "r");
       if(fp == NULL)
       {
        line();
        printf("\n\n\tERROR: COULD NOT OPEN %s TO READ PREVIOUS BLOCK.\n" , filename);
        line();
        exit(1);
        }
 
 printf("\n Reading Name of Block %s.." , filename);
 for(i = 0 ; i<bb ; i++)
  fscanf(fp , "%s" , filename);
 fclose(fp);

 full_path(blockchain , filename);
 fp = fopen(filename , "rb");
       if(fp == NULL)
       {
        line();
        printf("\n\n\tERROR: COULD NOT OPEN %s TO READ PREVIOUS BLOCK.\n" , filename);
        line();
        exit(1);
        }

 printf("\n Reading Block %s.." , filename);
  fread(&prev_block , sizeof(struct block) , 1 , fp);
 fclose(fp);

 
 strcpy(block_global.previous_block_hash , prev_block.current_block_hash);

}

 
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
void read_transaction_files()
{
 short i;

 strcpy(filename , "list.txt");
 full_path(miner , filename);
 fpg = fopen(filename , "r");
      if(fpg == NULL)
      {
       line();
       printf("\n\n\tERROR: COULD NOT OPEN %s TO FORM MERKLE TREE.\n" , filename);
       line();
       exit(1);
       }

 printf("\n Reading Transactions Record..");

 for(i = 0 ; i < block_global.no_of_transaction ; i++)
 {
  fscanf(fpg , "%s" , filename);
  full_path(miner , filename);

  fp = fopen(filename , "rb");
          if(fp == NULL)
          {
           line();
           printf("\n\n\tERROR: CANNOT OPEN %s IN binary_make().\n" , filename);
           line();
           exit(1);
            }
  printf("\n Reading Transaction Record %s.." , filename);
  fread(&(trans_global[i]) , sizeof(struct transaction) , 1 , fp);
  fclose(fp);
  }
 fclose(fpg); 
 }
/*----------------------------------------------------------------------------------------------------------*/
void create_current_block_hash()
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
   line();
   printf("\n\n\tERROR: THE CYCLE OF unsigned long nonce HAS COMPLETED.\n");
   line();
   exit(1);
   }  

 p = 1;

  strcpy(filename , "input.txt");
  full_path(sha , filename);
  fp = fopen(filename , "w");
            if(fp == NULL)
            {
             line();
             printf("\n\n\tERROR: COULD NOT OPEN %s TO CALCULATE NONCE.\n" , filename);
             line();
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

  
  for(i = 0; i < block_global.no_of_transaction ; i++)
  {
   fprintf(fp , "%s" , trans_global[i].t_id);
   fprintf(fp , "%Lf" , trans_global[i].amount);
   fprintf(fp , "%c" , trans_global[i].transaction_fee);
   fprintf(fp , "%ld" , trans_global[i].timestamp);
   }
  fclose(fp);

 system("python3 ~/betacoin/binary/SHA_function_DUP.py");

  strcpy(filename , "output.txt");
  full_path(sha , filename);
  fp = fopen(filename , "r");
            if(fp == NULL)
            {
             line();
             printf("\n\n\tERROR: COULD NOT OPEN %s TO CALCULATE NONCE.\n" , filename);
             line();
             exit(1);
             }
  fscanf(fp , "%[^\n]s" , block_global.current_block_hash);
  fclose(fp); 
 
  flag = 1;

  for(i = 0 ; i < block_global.difficulty_target ; i++)
   if(block_global.current_block_hash[i] != '0')
     flag = 0;

  if(flag == 1)
   block_global.nonce = nonce;


  }
 }
/*----------------------------------------------------------------------------------------------------------*/

void display_block()
{
 short i;
 printf("\nMagic number: %u", block_global.magic_number);
 printf("\nTime taken: %u" , block_global.time_taken);
 printf("\nBlock Size: %u" , block_global.block_size);
 printf("\nPrevious Hash: %s" , block_global.previous_block_hash);
 printf("\nCurrent Hash: %s" , block_global.current_block_hash);
 printf("\nMerkle Hash: %s" , block_global.merkle_hash);
 printf("\nMiner id: %s" , block_global.miner_id);
 printf("\nTimestamp: %lu", block_global.timestamp);
 printf("\nDifficulty target: %lu", block_global.difficulty_target);
 printf("\nnonce: %lu" , block_global.nonce);
 printf("\nnumber of transaction: %hu\n\n", block_global.no_of_transaction);

 for(i = 0; i< block_global.no_of_transaction; i++)
 {
  printf("\n\ntid: %s", trans_global[i].t_id);
  printf("\nsender id: %s", trans_global[i].sender_id);
  printf("\nreciever id: %s", trans_global[i].reciever_id);
  printf("\namount %LF" ,trans_global[i].amount);
  printf("\nt fee: %c" , trans_global[i].transaction_fee);
  printf("\ntime stamp %lu" , trans_global[i].timestamp);
  }
 }

/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

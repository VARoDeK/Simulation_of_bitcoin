#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>

#define FILE_SIZE 201                                                  //maximum length of filename
#define FOLDER_SIZE 51

/*----------------------------------------------------------------------------------------------------------*/
struct block
{
 unsigned int magic_number;                    //to define that the file is a block of blockchain.
 unsigned int time_taken;                      //no of seconds required to calculate hash.
 unsigned int block_size;                      //block size.
 unsigned char previous_block_hash[65]; 
 unsigned char current_block_hash[65];       
 unsigned char merkle_hash[65];                
 unsigned long timestamp;                      
 unsigned long difficulty_target; //no_of_zeros
 unsigned long nonce;
 unsigned short no_of_transaction;
 }block_global;

/*----------------------------------------------------------------------------------------------------------*/
struct transaction
{
 char t_id[FILE_SIZE];                     //It is the name of transaction file (*.transaction) which is string concat of wallet_id+timestamp;                  
 long double amount;                                //amount to be debited from account
 unsigned char transaction_fee;                     //char can be used a integer with range 0-255. Transaction fee will not be greater than that.
 unsigned long timestamp;
 /* data types for 'public key' of reciever,
    'digital signature' of sender and         */
 }*trans_global;

/*----------------------------------------------------------------------------------------------------------*/
char folder[FOLDER_SIZE];
char filename[FILE_SIZE];                                                   //will save the name of transaction file, which is read from "a.txt", which is to be opened.

char miner[] = "/miner/";
char sha[] = "/sha/";
char blockchain[] = "/BLOCKCHAIN/";
void full_path(char[],char[]); 


FILE *fpg, *fp;                                                                 //"fpg" to open list.txt, "fp" to open transaction files.
void prerun_setup();
void read_transaction_files();
void create_current_block_hash();
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
int main()
{
 FILE *fp;
 short i;
 struct timeval tv;
 unsigned long time1 , time2;
 
 printf("\n\n Creating Block..\n");

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
  strcpy(filename , "NEW_BLOCK.block");
  full_path(miner , filename);
  fp = fopen(filename , "wb");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s." , filename);
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

 }
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

void prerun_setup()
{
 FILE *fp;
 struct timeval tv;

 strcpy(folder , getenv("HOME")); //sets folder to "/home/<user-name>" in linux and "/Users/<user-name>" for OSX.
 strcat(folder , "/betacoin");    //sets folder to "/home/<user-name>/betacoin" in linux and "/Users/<user-name>/betacoin" for OSX. 

 strcpy(filename , "count_no_of_files_in_block.txt");
 full_path(miner , filename);
 fp = fopen(filename , "r");
       if(fp == NULL)
       {
        printf("\n\tERROR: COULD NOT OPEN %s TO READ NO OF TRANSACTIONS." , filename);
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
        printf("\n\tERROR: COULD NOT OPEN %s TO READ MERKLE SHA." , filename);
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
        printf("\n\tERROR: COULD NOT OPEN %s TO READ DIFFICULTY TARGET." , filename);
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
 block_global.previous_block_hash[0] = '\0';

 block_global.time_taken = 0;
 }
/*----------------------------------------------------------------------------------------------------------*/
void full_path(char subd[],char a[])
{
 unsigned short i;
 char temp[FILE_SIZE];

 for(i=0; ;i++)
 {
  if(a[i]=='\0')
  {
   if(a[i-1] == '\n')
    a[i-1] = '\0';
   break;
   }
  }

 strcpy(temp , folder);
 strcat(temp , subd);
 strcat(temp , a);
 strcpy(a , temp);
 }
/*----------------------------------------------------------------------------------------------------------*/
void read_transaction_files()
{
 short i;

 strcpy(filename , "list.txt");
 full_path(miner , filename);
 fpg = fopen(filename , "r");
      if(fpg == NULL)
      {
       printf("\n\tERROR: COULD NOT OPEN %s TO FORM MERKLE TREE." , filename);
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
           printf("\n\tERROR: CANNOT OPEN %s IN binary_make()" , filename);
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
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/

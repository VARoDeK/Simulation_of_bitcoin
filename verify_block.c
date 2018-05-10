#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>
#include"betacoin.h"
/***************************************************/

//Block header is read from NEW_BLOCK.txt
//Number of transactions are stored
//Loop is run to store read transactions from NEW_BLOCK.txt and store in a structure array
//Merkle tree is recompiled by re sending digests of all transactions within the block
//Send back the digest and compare with the digest saved in the block record
//If same then block is legitimate
//If different then the block has been tampered with
//Program proceeds to call for regeneration of blockchain
//Created tree is deleted to free space

/***************************************************/

/**********Global variables**********/

unsigned short height_global; //height of bin tree = ceil of log base 2 of count
unsigned short count_global;  //total number of transactions
unsigned short c_global; //counter to check if all transaction records have been inserted in the tree
unsigned long bb;         //no of blocks in current blockchain
char b_hash[SHA_HASH];

FILE *fpg, *fp;
/**********************************/

/**********Stuctures*************/
struct block test_block, prev_block;
struct transaction *test_trans;
struct merkle *root;
/*************************************************/

/*****************List of functions******************/
struct merkle* binary_make(struct merkle *head, unsigned short height_local, unsigned short h); //Creates a binary tree
struct merkle* create_merkle_node(); //Creates a node for the merkle tree
struct transaction* create_transaction_node(); //Create a node for transaction
void binary_correct(struct merkle *head, unsigned short height_local, unsigned short h); //Balances the tree if necessary
void merkle_hash(struct merkle *head, unsigned short height_local, unsigned short h); //Generates merkle hash
void delete_tree(struct merkle *head, unsigned short height_local, unsigned short h);//Deletes merkle tree
void create_block_hash();
void display_block();
/***************************************************/

/*****************Main function*********************/
int main()
{
 unsigned long i;
 unsigned long num;
 char tempstring[FILE_SIZE];
 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");


/*--reading file to know how many newblocks are created.-----------*/
  strcpy(filename , "list_of_new_blocks.txt");
  full_path(verify , filename);
  printf("\n Opening: %s..", filename);
  fp = fopen(filename , "r");
         if(fp == NULL)
         {
          line();
          printf("\n\n\tERROR: Could not open %s to read list of new blocks.\n" , filename);
          line();
          exit(1);
           }
  fscanf(fp , "%s" , tempstring);
   fclose(fp);

/*--now 'tempstring contains name of newblock---------------------'*/
  strcpy(filename , tempstring);
  full_path(verify , filename);
  printf("\n Opening: %s..", filename);
  fpg = fopen(filename , "rb");

  //Reading block header and transactions
  if (fpg == NULL)
  {
   line();
    printf("\n\n\tERROR: COULDN'T READ BLOCK RECORDS FROM %s. ABORTING PROCESS.\n", tempstring);
    line();
    exit(1);
  }

/*--Reading block header------------------------------------------------*/
  fread(&test_block, sizeof(struct block), 1, fpg);

  count_global = test_block.no_of_transaction;
  printf("\n Counted number of transactions records..");
  //confirming previous block hash
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

 if(strcmp(test_block.previous_block_hash , prev_block.current_block_hash) != 0)
 {
  line();
  printf("\n\n\tEROOR: Previous Block Hash Didn't Matched.\n");
  line();
  exit(1);
  }


/*--Reading transactions-------------------------------------------------*/

  test_trans = (struct transaction*)malloc(count_global * sizeof(struct transaction));

  for (i = 0; i < count_global; i++)
  {
    fread(&test_trans[i], sizeof(struct transaction), 1, fpg); //storing in test_trans
    printf("\n Read Transaction: %s.." , test_trans[i].t_id);
  }

  printf("\n Regenerating a merkle hash for reverification..\n");
  height_global = ceil(log2(count_global));

  root = NULL;
  c_global = 0;

  //Recreating of a merkle tree
  printf("\n Creating merkle tree..");
  root = binary_make(root , height_global , 0);

  //Balancing merkle tree
  printf("\n Correcting merkle Tree..");
  binary_correct(root , height_global , 0);

  //Generating a hash
  printf("\n Calculating Merkle Hash..");
  merkle_hash(root , height_global , 0);

  //Testing equality of previous merkle hash and current regenrated merkle hash. Tampering of block induces a change in the merkle hash
  printf("\nHash of merkle: %s\nCalculated Hash of merkle: %s\n" ,test_block.merkle_hash , root->hash);
  if (strcmp (root->hash , test_block.merkle_hash) == 0)
  {
   printf("\n\n\t No tampering detected in transaction records..\n");
   }
  else
  {
   printf("\n\n\t Transaction records of block has been tampered with. Regeneration of chain required..");
   exit(1);
   }

  //Deletes tree after use
  printf("\n Deleting Merkle Tree..");
  delete_tree(root , height_global , 0);
 
//  display_block();
  create_block_hash();
 //Testing equality of previous block hash and current regenrated block hash. Tampering of block induces a change in the block hash
  printf("\nHash of block: %s\nCalculated Hash of block: %s\n" , test_block.current_block_hash , b_hash);
  if (strcmp (test_block.current_block_hash , b_hash) == 0)
  {
   printf("\n\n\t No tampering detected in block..\n");
   }
  else
  {
   printf("\n\n\t Block has been tampered with. Regeneration of chain required..");
   exit(1);
   }

 strcpy(command , "mv ~/betacoin/verify/");
 strcat(command , tempstring);
 
 strcpy(filename , "no_of_blocks.txt");
 full_path(blockchain , filename);
 fp = fopen(filename , "r");
         if(fp == NULL)
         {
          line();
          printf("\n\n\tERROR: Could not open %s to read in long format.\n" , filename);
          line();
          exit(1);
           }

  fscanf(fp , "%lu" , &num);
  fseek(fp ,0 , SEEK_SET);
  fscanf(fp , "%s" , tempstring);
 fclose(fp);

 num++;

 fp = fopen(filename , "w");
         if(fp == NULL)
         {
          line();
          printf("\n\n\tERROR: Could not open %s to write.\n" , filename);
          line();
          exit(1);
           }
  fprintf(fp , "%lu" , num);
 fclose(fp);
/*
 fp = fopen(filename , "r");
         if(fp == NULL)
         {
          line();
          printf("\n\n\t ERROR: Could not open %s to read in string format.\n" , filename);
          line();
          exit(1);
           }
  fscanf(fp , "%s" , tempstring);
 fclose(fp);*/

 strcat(command , " ~/betacoin/BLOCKCHAIN/");
 strcat(tempstring , ".block");
 strcat(command , tempstring);                  //command created to cutpaste the newblock file after verifictaion.

 strcpy(filename , "block_list.txt");
 full_path(blockchain , filename);
 fp = fopen(filename , "a");
         if(fp == NULL)
         {
          line();
          printf("\n\n\tERROR: Could not open %s to write.\n" , filename);
          line();
          exit(1);
           }
  fprintf(fp , "%s\n" , tempstring);
 fclose(fp);
 
 printf("\n %s",command);
 system(command);                             //command run to cutpaste the new block file after verifcation

 system("rm ~/betacoin/verify/*");           //remove local files that were present to verify block


/*
This is to do after verification, if this miner contain those transaction files, whose block has been created, should be deleted.
*/
 for(i = 0 ; i < count_global ; i++)
 { 
  strcpy(filename , test_trans[i].t_id);
  strcat(filename , ".transaction");
  full_path(miner , filename);
  remove(filename);
  }

  free(test_trans);

}

/****************************************************/

/***************************************************/

struct merkle* binary_make(struct merkle *head, unsigned short height_local, unsigned short h)
{

 if(c_global == count_global)  //All transactions are listed in tree
  return head;

 if(h > height_local)   //Return if height of binary tree formed exceeds the predetermined height
  return head;

 head = create_merkle_node();

 if(head == NULL)
 {
  line();
   printf("\n\n\tERROR: MERKLE TREE CREATION FAILED AT HEIGHT %d.\n", height_local);
   line();
   exit(1);
 }

 if(h == height_local)
 {
   head->data = create_transaction_node();
   if(head->data == NULL)
   {
    line();
     printf("\n\n\tERROR: TRANSACTION NODE NOT CREATED AT HEIGHT %d.\n", height_local);
    line();
     exit(1);
   }

   *(head->data) = test_trans[c_global];
   c_global++;
 }

 head->left = binary_make(head->left, height_local, h+1);
 head->right = binary_make(head->right, height_local, h+1);

 return head;
}

/***************************************************/

struct merkle* create_merkle_node()
{
 short i;
 struct merkle *ptr;
 ptr = NULL;
 ptr = (struct merkle*)malloc(sizeof(struct merkle));

 if(ptr == NULL)
  return ptr;

 for(i = 0 ; i < 66; i++, ptr->hash[i]='\0');

 ptr->copy = 0;
 ptr->data = NULL;
 ptr->left = NULL;
 ptr->right = NULL;

 return ptr;
}

/***************************************************/

struct transaction* create_transaction_node()
{
 struct transaction *ptr;
 ptr = NULL;
 ptr = (struct transaction*)malloc(sizeof(struct transaction));

 if(ptr == NULL)
  return ptr;

 ptr->amount = 0;
 ptr-> transaction_fee = 0;

 return ptr;
}

/***************************************************/

void binary_correct(struct merkle *head, unsigned short height_local, unsigned short h)
{
  if(h > height_local)
   return;

  if(h <= height_local && head->right == NULL)
  {
   head->right = head->left;
   head->copy = 1; //copy previous records to balance tree
   }

  binary_correct(head->left, height_local, h+1);
  binary_correct(head->right, height_local, h+1);
}

 /***************************************************/

void merkle_hash(struct merkle *head, unsigned short height_local, unsigned short h)
{
  if(h == height_local)
  {
    strcpy(filename , "input.txt");
    full_path(sha , filename);

    fp = fopen(filename , "w");
    if(fp == NULL)
    {
     line();
      printf("\n\n\tERROR: CANNOT OPEN %s IN merkle_hash()\n" , filename);
     line();
      exit(1);
    }

  fprintf(fp , "%s" , head->data->t_id);
  fprintf(fp , "%s" , head->data->sender_id);
  fprintf(fp , "%s" , head->data->reciever_id);
  fprintf(fp , "%Lf" , head->data->amount);
  fprintf(fp , "%c" , head->data->transaction_fee);
  fprintf(fp , "%ld" , head->data->timestamp);


    fclose(fp);


    system("python3 ~/betacoin/binary/SHA_function_DUP.py");

    strcpy(filename , "output.txt");
    full_path(sha , filename);

    fp = fopen(filename , "r");
    if(fp == NULL)
    {
     line();
      printf("\n\n\tERROR: CANNOT OPEN %s IN merkle_hash().\n" , filename);
     line();
      exit(1);
    }

    fscanf(fp , "%s" , head->hash);
    fclose(fp);

    return;
  }

   merkle_hash(head->left , height_local , h+1);

   if(head->copy != 1)
   {
     merkle_hash(head->right , height_local , h+1);
   }

   strcpy(filename , "input.txt");
   full_path(sha , filename);

   fp = fopen(filename , "w");
   if(fp == NULL)
   {
    line();
     printf("\n\n\tERROR: CANNOT OPEN %s IN merkle_hash().\n" , filename);
    line();
     exit(1);
   }

   fprintf(fp,"%s%s" , head->left->hash , head->right->hash);
   fclose(fp);

   system("python3 ~/betacoin/binary/SHA_function_DUP.py");

   strcpy(filename , "output.txt");
   full_path(sha , filename);

   fp = fopen(filename , "r");
   if(fp == NULL)
   {
    line();
     printf("\n\n\tERROR: CANNOT OPEN %s IN merkle_hash().\n" , filename);
    line();
     exit(1);
   }

   fscanf(fp , "%s" , head->hash);
   fclose(fp);

   return;
}

/***************************************************/

 void delete_tree(struct merkle *head, unsigned short height_local, unsigned short h)
 {
   if(h > height_local)
    return;

   if(head == NULL)
    return;

   if(h == height_local)
    free(head->data);

   delete_tree(head->left, height_local, h+1);
   free(head->left);
   head->left = NULL;

   if(head->copy != 1)
   {
     delete_tree(head->right, height_local, h+1);
     free(head->right);
     head->right = NULL;
   }
 }

/***************************************************/

void create_block_hash()
{
short i;
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
   fprintf(fp , "%u" , test_block.magic_number);
   fprintf(fp , "%u" , test_block.block_size);
   fprintf(fp , "%s" , test_block.previous_block_hash);
   fprintf(fp , "%s" , test_block.merkle_hash);
   fprintf(fp , "%lu" , test_block.timestamp);
   fprintf(fp , "%lu" , test_block.difficulty_target);
   fprintf(fp , "%lu" , test_block.nonce);
   fprintf(fp , "%hu" , test_block.no_of_transaction);
/*
- we will not take, current_block_hash into account for creating current_block_has :P , this is why it was not written into input.txt.
- time taken will also not be counted to same.
- these two things will be ommited for verfying also, in verify_block.c.
- nonce will work faster than block_global.nonce.
*/


  for(i = 0; i < test_block.no_of_transaction ; i++)
  {
   fprintf(fp , "%s" , test_trans[i].t_id);
   fprintf(fp , "%Lf" , test_trans[i].amount);
   fprintf(fp , "%c" , test_trans[i].transaction_fee);
   fprintf(fp , "%ld" , test_trans[i].timestamp);
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
  fscanf(fp , "%[^\n]s" , b_hash);
  fclose(fp);

 }
/*-----------------------------------------------------------------*/
void display_block()
{
 short i;
 printf("\nMagic number: %u", test_block.magic_number);
 printf("\nTime taken: %u" , test_block.time_taken);
 printf("\nBlock Size: %u" , test_block.block_size);
 printf("\nPrevious Hash: %s" , test_block.previous_block_hash);
 printf("\nCurrent Hash: %s" , test_block.current_block_hash);
 printf("\nMerkle Hash: %s" , test_block.merkle_hash);
 printf("\nMiner id: %s" , test_block.miner_id);
 printf("\nTimestamp: %lu", test_block.timestamp);
 printf("\nDifficulty target: %lu", test_block.difficulty_target);
 printf("\nnonce: %lu" , test_block.nonce);
 printf("\nnumber of transaction: %hu\n\n", test_block.no_of_transaction);

 for(i = 0; i< test_block.no_of_transaction; i++)
 {
  printf("\n\ntid: %s", test_trans[i].t_id);
  printf("\nsender id: %s", test_trans[i].sender_id);
  printf("\nreciever id: %s", test_trans[i].reciever_id);
  printf("\namount %LF" ,test_trans[i].amount);
  printf("\nt fee: %c" , test_trans[i].transaction_fee);
  printf("\ntime stamp %lu" , test_trans[i].timestamp);
  }
 }


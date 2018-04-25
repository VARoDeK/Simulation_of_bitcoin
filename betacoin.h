#define FILE_SIZE 201                                                  //maximum length of filename
#define FOLDER_SIZE 51                                                 //maximum length of folder name
#define SHA_HASH 65                                                    //64 characters of sha, and one space extra for NULL character
#define NAME_SIZE 101                                                  //max length for name
/*----------------------------------------------------------------------------------------*/

struct block
{
 unsigned int magic_number;                    //to define that the file is a block of blockchain.
 unsigned int time_taken;                      //no of seconds required to calculate hash.
 unsigned int block_size;                      //block size.
 char previous_block_hash[SHA_HASH];           //hash of previous block
 char current_block_hash[SHA_HASH];            //hash of current block
 char merkle_hash[SHA_HASH];                   //hash of merkle tree of transactions
 char miner_id[71];                            //miner_id will be same as wallet_id of user
 unsigned long timestamp;                      //timestamp of moment the block started forming
 unsigned long difficulty_target;              //no of characters, from starting, that should be zero in SHA
 unsigned long nonce;                          //nonce code, responsible to achieve difficulty target
 unsigned short no_of_transaction;             //no of transaction records written in the block
 };


/*----------------------------------------------------------------------------------------*/

struct user
{
 char wallet_id[NAME_SIZE];              //strcat(md5(name,timestamp,location,user_and_hostname,email) + timestamp)
 char name[NAME_SIZE];
 unsigned long timestamp;
 char location[NAME_SIZE];
 char user_and_hostname[NAME_SIZE];      //for my system: varodek@varodek.local
 char email[NAME_SIZE];
 char miner_flag;
 };

/*----------------------------------------------------------------------------------------*/

struct transaction
{
 char t_id[FILE_SIZE];                             //It is the name of transaction file (*.transaction) which is string concat of timestamp+wallet_id;   
 long double amount;                               //amount to be debited from account
 unsigned char transaction_fee;                    //char can be used a integer with range 0-255. Transaction fee will not be greater than that.
 unsigned long timestamp;
 /* data types for 'public key' of reciever,
    'digital signature' of sender and         */
 };

/*----------------------------------------------------------------------------------------*/

char folder[FOLDER_SIZE];                  //will save the name of folder.
char filename[FILE_SIZE];                  //will save the name of files that we need to open.

char miner[] = "/miner/";
char sha[] = "/sha/";
char binary[] = "/binary/";
char blockchain[] = "/BLOCKCHAIN/";

/*----------------------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------------------*/

struct merkle
{
 unsigned char copy;                             //The need of this memeber is explained in the code of binary_correct() and delete_tree() function.
 char hash[SHA_HASH];                                  //hash is 64 characters long. 1 byte for NULL charactere.
 struct transaction *data;
 struct merkle *left;
 struct merkle *right;
 };


/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/


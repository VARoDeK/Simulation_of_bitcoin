/*
-This header file contains various structure definations for various programs.
-This header file contains various macro definition for various programs.
*/
#define FILE_SIZE 201                                                  //maximum length of filename
#define FOLDER_SIZE 51                                                 //maximum length of folder name
#define SHA_HASH 65                                                    //64 characters of sha, and one space extra for NULL character
#define NAME_SIZE 101                                                  //max length for name
#define COMMAND_SIZE 501                                               //max length of command to be run on terminal
/*----------------------------------------------------------------------------------------*/
/*
-This is the structure for block-header for the block of a blockchain.
-This is the first part of data which will be written in a block file.
*/
struct block
{
 unsigned int magic_number;                    //to define that the file is a block of blockchain.
 unsigned int time_taken;                      //no of seconds required to calculate hash.
 unsigned int block_size;                      //block size.
 char previous_block_hash[SHA_HASH];           //hash of previous block
 char current_block_hash[SHA_HASH];            //hash of current block
 char merkle_hash[SHA_HASH];                   //hash of merkle tree of transactions
 char miner_id[NAME_SIZE];                     //miner_id will be same as wallet_id of user
 unsigned long timestamp;                      //timestamp of moment the block started forming
 unsigned long difficulty_target;              //no of characters, from starting, that should be zero in SHA
 unsigned long nonce;                          //nonce code, responsible to achieve difficulty target
 unsigned short no_of_transaction;             //no of transaction records written in the block
 };


/*----------------------------------------------------------------------------------------*/
/*
This is the structure for user-details.
*/
struct user
{
 char wallet_id[NAME_SIZE];              //strcat(md5(name,timestamp,location,user_and_hostname,email) + timestamp)
 char name[NAME_SIZE];                   //name of user
 long double account_balance;            //account balance of user
 unsigned long timestamp;                 
 char location[NAME_SIZE];
 char user_and_hostname[NAME_SIZE];      //for my system: varodek@varodek.local
 char email[NAME_SIZE];
 char miner_flag;                        //flag to tell of user is also a miner
 };

/*----------------------------------------------------------------------------------------*/
/*
-This structure is for keeping record of one transaction.
*/
struct transaction
{
 char t_id[FILE_SIZE];                             //It is the name of transaction file (*.transaction) which is string concat of timestamp+wallet_id;   
 char sender_id[NAME_SIZE];                        //It is account_no/ wallet_id of sender.
 char reciever_id[NAME_SIZE];                      //It is account_no/ wallet_id of reciever
 long double amount;                               //amount to be debited from account
 unsigned char transaction_fee;                    //char can be used a integer with range 0-255. Transaction fee will not be greater than that.
 unsigned long timestamp;
 };

/*----------------------------------------------------------------------------------------*/
/*
-This structute is for records of beneficiaries.
-(Beneificiary is one to whom you are sending money, for any reason).
-It will be very impractical to type 35+ characters long account number of reciever everytime you pay to him/ her.
-So save the information of beneficiary for once and a temporary ID no will be created for it.
-Whenever you are paying, just feed the ID no and it wil automatically feed the reciever's account no.
*/
struct beneficiary
{
 char account_no[NAME_SIZE];
 char name[NAME_SIZE];
 char comment[COMMAND_SIZE];
 };

/*----------------------------------------------------------------------------------------*/

char folder[FOLDER_SIZE];                  //will save the name of folder.
char filename[FILE_SIZE];                  //will save the name of files that we need to open.
char command[COMMAND_SIZE];                //will save the command that we will run using system();

//below 5 strings are name of sub-folders.
char miner[] = "/miner/";
char sha[] = "/sha/";
char binary[] = "/binary/";
char blockchain[] = "/BLOCKCHAIN/";
char verify[] = "/verify/";

//extensions for various files
char trans_extension[] = ".transaction";   //extension for transaction files
char newblock_extension[] = ".newblock";   //extension for newblock
char block_extension[] = ".block";         //extension of block once it is verified
/*----------------------------------------------------------------------------------------*/
/*
-To explain working of a function let's see an example.
-The string, folder = "/home/<user_name>/betacoin" for linux or folder = "/Users/<user_name>/betacoin" for mac, is already initialized in every program.
EXAMPLE::
-strcpy(filename , "trial.txt");      
     so filename conatains, "trial.txt"

- full_path(miner , filename);
     so filename conatins, "/home/<user_name>/betacoin/miner/trial.txt"
*/
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
/*
-This is the structure definition for each node of merkle tree. 
-Merkle tree is a binary tree which is complete and balanced.
-You are advised to read more about Merkle tree on net for better undertsanding of codes.
*/
struct merkle
{
 unsigned char copy;                             //The need of this memeber is explained in the code of binary_correct() and delete_tree() function.
 char hash[SHA_HASH];                            //hash is 64 characters long. 1 byte for NULL charactere.
 struct transaction *data;
  /*
  -except leaves, no other nodes will carry transaction record. 
  -if we would have integrated transaction structure within merkle structure only, it would have been a wastage of space.
  -so we declared a pointer, if the current node is a leaf, it will create a dynamic transaction object and connect it to current node.
  - this way it will only use the space of size of a pointer type in every node, thus less wastage of space.
   */
 struct merkle *left;
 struct merkle *right;
 };


/*----------------------------------------------------------------------------------------*/

void line()
{
 printf("\n------------------------------------------------------------------");
 }
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/



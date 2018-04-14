/*All the software related files will reside in a folder name, "bitcoin", in root folder.*/


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>

#define MAX_SIZE 201                                                  //maximum length of filename
/*------------------------------------------------------------------------------------*/
// structure for transaction record.

struct transaction
{
 unsigned long amount;                                                //amount to be debited from account
 unsigned char transaction_fee;                                       //char can be used a integer with range 0-255. Transaction fee will not be greater than that.

 /* data types for 'public key' of reciever,
    'digital signature' of sender and 
    'time-stamp' yet to be declared.         */
 }; 

/*------------------------------------------------------------------------------------*/
//structure for hash node;

struct merkle
{
 unsigned short index;
 char hash[65];                                  //hash is 64 characters long. 1 byte for NULL charactere.
 struct transaction *data;
 struct merkle *left;
 struct merkle *right;
 } *root;


/*------------------------------------------------------------------------------------*/
unsigned short height;                                                           //stores the height of the binary tree
unsigned short count;          //counts the total number of transactions. The ceil() of log of count, with base 2, will give the height of binary tree.
unsigned short c;

char filename[MAX_SIZE];                                                   //will save the name of transaction file, which is read from "a.txt", which is to be opened.
char folder[MAX_SIZE];

FILE *fpg, *fp;                                                                 //to open a.txt

struct merkle* create_merkle_node();                                            //function to dynamically allocate memory for data type merkle.
struct transaction* create_transaction_node();                                  //function to dynamically allocate memory for data type transaction.
struct merkle* binary_make(struct merkle*, unsigned short, unsigned short);     //forms a binary tree out of transaction records.
void binary_traverse(struct merkle*, unsigned short, unsigned short);
void binary_correct(struct merkle*, unsigned short, unsigned short);

void prerun_setup();                                                            //initializes some important values, like path to the bitcoin folder.
/*function_by_shikhar: a function to be made by shikhar to list the names of files in current directory and count them*/

void char_refresh(char[],unsigned short);
void full_path(char[]);
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/


int main()
{
 unsigned short i;

 prerun_setup();               //to assign folder path, count no of files. 
 height = ceil(log2(count));  
 
 printf("\n%hu\n%hu\n%s\n\n\n\n",height,count,folder);

 strcpy(filename,"list.txt");
 full_path(filename);
 fpg = fopen(filename,"r");

 root = NULL;
 c=0;
 root = binary_make(root,height,0);

 fclose(fpg);

 if(root == NULL)
  printf("\n\nnull root\n\n");

 binary_correct(root,height,0);

 binary_traverse(root,height,0);
 return 0;
 }











/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
struct merkle* create_merkle_node()
{
 short i;
 struct merkle *ptr;
 ptr = NULL;
 ptr = (struct merkle*)malloc(sizeof(struct merkle));

 if(ptr == NULL)
  return ptr;

 for(i=0; i<66; i++, ptr->hash[i]='\0');

 ptr->data = NULL;
 ptr->left = NULL;
 ptr->right = NULL;

 return ptr;
 }
/*------------------------------------------------------------------------------------*/

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
/*------------------------------------------------------------------------------------*/

struct merkle* binary_make(struct merkle *head, unsigned short height, unsigned short h)
{
 if(c == count)  //'c' > 'count' means all transactions are listed in binary tree.
  return head;

 if(h>height)   //if height is getting larger tha the height decided, then it will stop making new nodes and return.
  return head;

 head = create_merkle_node();

 if(head == NULL)
 {
  printf("\n\n\tERROR: WHILE CREATING MERKLE TREE, AT HEIGHT %d",height);
  exit(1);
  }

printf("\nheight: %hu",h);


 if(h == height)
 {
  head->data = create_transaction_node();
  if(head->data == NULL)
  {
   printf("\n\n\tERROR: WHILE CREATING TRANSACTION DATA, AT HEIGHT %d",height);
   exit(1);
   }
  
  fscanf(fpg,"%s",filename);
  full_path(filename);

  fp = fopen(filename,"rb");
  fread(head->data, sizeof(struct transaction),1, fp);
  printf("\nblabla   %lu",head->data->amount);
  fclose(fp);
  c++;
 
  }


 head->left = binary_make(head->left, height, h+1);
 head->right = binary_make(head->right, height, h+1);

 return head;
 }



/*------------------------------------------------------------------------------------*/

void char_refresh(char a[], unsigned short n)
{
 unsigned short i;
 for(i=0; i<n; i++)
  a[i]='\0';                 //initializes each element of string with NULL character, so as no garbage value is there.
 }
/*------------------------------------------------------------------------------------*/

void full_path(char a[])
{
 unsigned short i;
 char temp[MAX_SIZE];
 for(i=0; ;i++)
 {
  if(a[i]=='\0')
  {
   if(a[i-1] == '\n')
    a[i-1] = '\0';
   break;
   }
  }

 strcpy(temp,folder);
 strcat(temp,a);
 strcpy(a,temp);
 }

/*------------------------------------------------------------------------------------*/

void prerun_setup()
{
 char temp[MAX_SIZE] = "/home/";
 DIR *dr;
 FILE *fp,*fp2;
 struct dirent *de;
 unsigned short len;
 
 getlogin_r(folder,201);                  //saves the current logged in user_name in "folder"
 strcat(folder,"/bitcoin/");
 strcat(temp,folder);
 strcpy(folder,temp);                     //finally folder contains: "/home/<user_name>/bitcoin/"
 
 dr = opendir(folder);

 if(dr == NULL)
 {
  printf("ERROR: CANNOT OPEN DIRECTORY IN prerun_setup.");
  exit(0);
  }


 strcpy(filename,"list.txt");
 full_path(filename);
 fp = fopen(filename,"w");
 
 count =0;
 while((de = readdir(dr)) != NULL)
 {
  if(strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0)                  //not to select "current directory" and "previous directory"
  continue;

 len = strlen(de->d_name);
 if(strncmp(de->d_name + len - 12, ".transaction",12) == 0)                        //length of string ".transaction" is 12.
 {
  fprintf(fp,"%s\n",de->d_name);
  count++;
  }
  }
 
 fclose(fp);
 closedir(dr);
 }
/*------------------------------------------------------------------------------------*/

void binary_traverse(struct merkle *head, unsigned short height, unsigned short h)
{
 if(head == NULL)
  return;

 if(h > height)
  return;


printf("\nheight traverde: %hu",h);
 if(h == height)
  printf("\n\n%lu", head->data->amount);

 binary_traverse(head->left, height, h+1);
 binary_traverse(head->right, height, h+1);

 }

/*------------------------------------------------------------------------------------*/
void binary_correct(struct merkle *head, unsigned short height, unsigned short h)
{
 if(h > height)
  return;

 if(h <= height && head->right == NULL)
  head->right = head->left;

 binary_correct(head->left, height, h+1);
 binary_correct(head->right, height, h+1); 
 }
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/

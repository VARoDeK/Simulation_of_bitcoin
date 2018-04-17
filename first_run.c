#include<sys/stat.h>                //for mkdir()
#include<string.h> 
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>                   //for errno and error values

 char static_path[51];


int main()
{
 FILE *fp;
 char tempname[101];
 
 strcpy(static_path , getenv("HOME"));
 strcat(static_path , "/betacoin");

 //Making ~/betacoin 
 if(mkdir(static_path , S_IRWXU) !=0)                //S_IRWXU - gives "read + write + execute" permission to current user.
 {
  if(errno != EEXIST)                    //mkdir throws non-zero number on failure. The errno is set to certain value. EEXIST means already exist.
  { 
   printf("\n\n\t\tCANNOT CREATE DIRECTORY %s." , static_path);
   exit(1);
   }
  }

 //Making ~/betacoin/miner
 strcpy(tempname , static_path);
 strcat(tempname , "/miner");
 if(mkdir(tempname , S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY %s." , tempname);
   exit(1);
   }
  }

 //Making ~/betacoin/sha
 strcpy(tempname , static_path);
 strcat(tempname , "/sha");

 if(mkdir(tempname , S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY %s." , tempname);
   exit(1);
   }
  }

 //Making ~/betacoin/BLOCKCHAIN
 strcpy(tempname , static_path);
 strcat(tempname , "/BLOCKCHAIN");
 
 if(mkdir(tempname , S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY %s." , tempname);
   exit(1);
   }
  }


 //Making ~/betacoin/binary
 strcpy(tempname , static_path);
 strcat(tempname , "/binary");

 if(mkdir(tempname , S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY %s." , tempname);
   exit(1);
   }
  }

 
 system("cp ./SHA_function.py ~/betacoin/miner/SHA_function_DUP.py");

 //Creating ~/betacoin/miner/difficulty_target.txt
 strcpy(tempname , static_path);
 strcat(tempname , "/miner/difficulty_target.txt");
 fp = fopen(tempname , "w");
         if(fp == NULL)
         {
          printf("\n\tERROR: COULD NOT OPEN %s TO WRITE DIFFICULTY TARGET." , tempname);
          exit(1);
          } 
 fprintf(fp , "%lu" , (unsigned long)2);
 fclose(fp);
 
 #ifdef __linux__ 
  system("gcc merkle_tree.c -o  ~/betacoin/binary/merkle_tree -lm");

 #elif __APPLE__ 
  system("gcc merkle_tree.c -o ~/betacoin/binary/merkle_tree");
  
 #endif 

 }

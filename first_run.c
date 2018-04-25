#include<sys/stat.h>                //for mkdir()
#include<string.h> 
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>                   //for errno and error values
#include"betacoin.h"

 char static_path[FOLDER_SIZE];


int main()
{
 FILE *fp;
 char tempname[101];
 
 if(system("python3 -V") != 0)
 {
  printf("\n]tERROR: CANNOT RUN python3. CHECK IF IT IS INSTALLED OR FOR OTHER ERRORS.");
  exit(1);
  }
 
 if(system("gcc -v") != 0)
 {
  printf("\n]tERROR: CANNOT RUN gcc. CHECK IF IT IS INSTALLED OR FOR OTHER ERRORS.");
  exit(1);
  }


 
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
 printf("\n Created folder %s.." , static_path);

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
 printf("\n Created folder %s.." , tempname);

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
 printf("\n Created folder %s.." , tempname);


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
 printf("\n Created folder %s.." , tempname);


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
 printf("\n Created folder %s.." , tempname);

 
 if(system("cp ./SHA_function.py ~/betacoin/binary/SHA_function_DUP.py") == 0)
   printf("\n Copied ./SHA_function.py to ~/betacoin/binary/SHA_function_DUP.py..");
 else
 {
  printf("\n\tERROR: Could not copy ./SHA_function.py to ~/betacoin/binary/SHA_function_DUP.py..");
  exit(1);
  }

 if(system("cp ./MD5_function.py ~/betacoin/binary/MD5_function_DUP.py") == 0)
   printf("\n Copied ./MD5_function.py to ~/betacoin/binary/MD5_function_DUP.py..");
 else
 {
  printf("\n\tERROR: Could not copy ./MD5_function.py to ~/betacoin/binary/MD5_function_DUP.py..");
  exit(1);
  }






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
 printf("\n Created file %s to set difficulty target.." , tempname);


 system("gcc create_account.c -o ~/betacoin/binary/create_account");
 
 #ifdef __linux__ 
  system("gcc merkle_tree.c -o  ~/betacoin/binary/merkle_tree -lm");

 #elif __APPLE__ 
  system("gcc merkle_tree.c -o ~/betacoin/binary/merkle_tree");
  
 #endif 

 }

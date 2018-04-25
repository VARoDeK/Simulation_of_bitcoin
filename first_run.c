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


   printf("\n Running command: \n\tcp ./SHA_function.py ~/betacoin/binary/SHA_function_DUP.py .."); 
 if(system("cp ./SHA_function.py ~/betacoin/binary/SHA_function_DUP.py") == 0)
   printf("\n Copied ./SHA_function.py to ~/betacoin/binary/SHA_function_DUP.py..");
 else
 {
  printf("\n\tERROR: Could not copy ./SHA_function.py to ~/betacoin/binary/SHA_function_DUP.py..");
  exit(1);
  }

  printf("\n Running command: \n\tcp ./MD5_function.py ~/betacoin/binary/MD5_function_DUP.py ..");
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

 printf("\n Running command: \vgcc create_account.c -o ~/betacoin/binary/create_account ..");
 if(system("gcc create_account.c -o ~/betacoin/binary/create_account") == 0)
  printf("\n\tCompiled create_account.c..");
 else
  {
   printf("\n\tERROR: Could not compile create_account.c ..");
   exit(1);
   }


 printf("\n Running command: \vgcc create_genesis_block.c -o ~/betacoin/binary/create_genesis_block ..");
 if(system("gcc create_genesis_block.c -o ~/betacoin/binary/create_genesis_block") == 0)
  printf("\n\tCompiled create_genesis_block.c..");
 else
  {
   printf("\n\tERROR: Could not compile create_genesis_block.c ..");
   exit(1);
   }


  printf("\n Running command: \vgcc create_block.c -o ~/betacoin/binary/create_block ..");
 if(system("gcc create_block.c -o ~/betacoin/binary/create_block") == 0)
  printf("\n\tCompiled create_block.c..");
 else
  {
   printf("\n\tERROR: Could not compile create_block.c ..");
   exit(1);
   }


  printf("\n Running command: \vgcc create_list_of_new_blocks.c -o ~/betacoin/binary/create_list_of_new_blocks ..");
 if(system("gcc create_list_of_new_blocks.c -o ~/betacoin/binary/create_list_of_new_blocks") == 0)
  printf("\n\tCompiled create_list_of_new_blocks.c..");
 else
  {
   printf("\n\tERROR: Could not compile create_list_of_new_blocks.c ..");
   exit(1);
   }






 
 #ifdef __linux__ 
  printf("\n Running command: \vgcc merkle_tree.c -o  ~/betacoin/binary/merkle_tree -lm ..");
  if(system("gcc merkle_tree.c -o  ~/betacoin/binary/merkle_tree -lm") == 0)
   printf("\n\tCompiled merkle_tree.c ..");
  else
  {
   printf("\n\tERROR: Could not compile merkle_tree.c ..");   
   exit(1);
   }


 #elif __APPLE__ 
  printf("\n Running command: \vgcc merkle_tree.c -o  ~/betacoin/binary/merkle_tree ..");
  if(system("gcc merkle_tree.c -o  ~/betacoin/binary/merkle_tree") == 0)
   printf("\n\tCompiled merkle_tree.c ..");
  else
  {
   printf("\n\tERROR: Could not compile merkle_tree.c ..");
   exit(1);
   }
  
 #endif 

 }

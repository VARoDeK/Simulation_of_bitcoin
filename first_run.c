#include<sys/stat.h>                //for mkdir()
#include<string.h> 
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>                   //for errno and error values

 char static_path[51];


int main()
{
 char tempfolder[101];
 
 strcpy(static_path , getenv("HOME"));
 strcat(static_path , "/betacoin");

 if(mkdir(static_path , S_IRWXU) !=0)                //S_IRWXU - gives "read + write + execute" permission to current user.
 {
  if(errno != EEXIST)                    //mkdir throws non-zero number on failure. The errno is set to certain value. EEXIST means already exist.
  { 
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"betacoin\" in home folder.");
   exit(1);
   }
  }

 strcpy(tempfolder , static_path);
 strcat(tempfolder , "/miner");
 if(mkdir(tempfolder , S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"miner\" in betacoin folder.");
   exit(1);
   }
  }


 strcpy(tempfolder , static_path);
 strcat(tempfolder , "/sha");

 if(mkdir(tempfolder , S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"sha\" in betacoin folder.");
   exit(1);
   }
  }

 system("cp ./SHA_function.py ~/betacoin/miner/SHA_function_DUP.py");

 strcpy(tempfolder , static_path);
 strcat(tempfolder , "/BLOCKCHAIN");
 
 if(mkdir(tempfolder , S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"BLOCKCHAIN\" in betacoin folder.");
   exit(1);
   }
  }




 }

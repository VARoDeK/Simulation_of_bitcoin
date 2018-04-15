#include<sys/stat.h>                //for mkdir()
#include<string.h> 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>                  //for getlogin_R()
#include<errno.h>                   //for errno and error values

int main()
{
 char uname[20];
 char t[44]="/home/";
 getlogin_r(uname,201);                 //returns user name
 
 strcat(t,uname);
 strcat(t,"/bitcoin");

 if(mkdir(t,S_IRWXU) !=0)                //S_IRWXU - gives "read + write + execute" permission to current user.
 {
  if(errno != EEXIST)                    //mkdir throws non-zero number on failure. The errno is set to certain value. EEXIST means already exist.
  { 
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"bitcoin\" in home folder.");
   exit(1);
   }
  }

 strcat(t,"/miner");

 if(mkdir(t,S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"miner\" in bitcoin folder.");
   exit(1);
   }
  }
 }
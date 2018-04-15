#include<sys/stat.h>                //for mkdir()
#include<string.h> 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>                  //for getlogin_R()
#include<errno.h>                   //for errno and error values

#ifdef __linux__
 char t[44] = "/home/";

#elif __APPLE__
 char t[44] = "/Users/";

#else
 printf("OS Not found");

#endif



int main()
{
 char uname[20];
 getlogin_r(uname,201);                 //returns user name
 
 strcat(t,uname);
 strcat(t,"/betacoin");

 if(mkdir(t,S_IRWXU) !=0)                //S_IRWXU - gives "read + write + execute" permission to current user.
 {
  if(errno == EACCES)                    //mkdir throws non-zero number on failure. The errno is set to certain value. EEXIST means already exist.
  { 
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"betacoin\" in home folder, permission denied.");
   exit(1);
   }
  }

 strcat(t,"/miner");

 if(mkdir(t,S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"miner\" in betacoin folder.");
   exit(1);
   }
  }
 }

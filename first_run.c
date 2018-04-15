#include<sys/stat.h>                //for mkdir()
#include<string.h> 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>                  //for getlogin_R()
#include<errno.h>                   //for errno and error values

#ifdef __linux__
 char static_path[44] = "/home/";

#elif __APPLE__
 char static_path[44] = "/Users/";

#else
 printf("OS Not found");

#endif



int main()
{
 char uname[20];
 char temp[201];
 getlogin_r(uname,201);                 //returns user name
 
 strcat(static_path,uname);
 strcat(static_path,"/betacoin");

 if(mkdir(static_path,S_IRWXU) !=0)                //S_IRWXU - gives "read + write + execute" permission to current user.
 {
  if(errno != EEXIST)                    //mkdir throws non-zero number on failure. The errno is set to certain value. EEXIST means already exist.
  { 
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"betacoin\" in home folder.");
   exit(1);
   }
  }

 strcpy(temp,static_path);
 strcat(temp,"/miner");

 if(mkdir(temp,S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"miner\" in betacoin folder.");
   exit(1);
   }
  }


 strcpy(temp,static_path);
 strcat(temp,"/sha");

 if(mkdir(temp,S_IRWXU) !=0)
 {
  if(errno != EEXIST)
  {
   printf("\n\n\t\tCANNOT CREATE DIRECTORY \"sha\" in betacoin folder.");
   exit(1);
   }
  }



 strcpy(temp,"cp SHA_function.py ");
 strcat(temp,static_path);
 strcat(temp,"/miner/SHA_function.py");
 system(temp);


 }

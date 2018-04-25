#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include"betacoin.h"

/*------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

int main()
{
 FILE *fp;
 unsigned short ext_len = strlen(newblock_extension);
 unsigned short count = 0, i, j ,len;
 struct dirent *de;
 DIR *dr;
 char tempfile[FILE_SIZE], *tempo ,**name;


/*--creating folder path----------------------------------*/
 strcpy(folder , getenv("HOME")); //sets folder to "/home/<user-name>" in linux and "/Users/<user-name>" for OSX.
 strcat(folder , "/betacoin");    //sets folder to "/home/<user-name>/betacoin" in linux and "/Users/<user-name>/betacoin" for OSX. 

 strcpy(tempfile , folder);
 strcat(tempfile , "/miner/");


/*--opening miner directory---------------------------------------------*/
 dr = opendir(tempfile);

 if(dr == NULL)
 {
  printf("ERROR: CANNOT OPEN %s DIRECTORY IN prerun_setup." , tempfile);
  exit(0);
  }

 printf("\n Inside Directory %s.." , tempfile);
 strcpy(filename , "list_of_new_blocks.txt");
 full_path(miner , filename);
 fp = fopen(filename , "w");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s IN prerun_setup()" , filename);
           closedir(dr);
           exit(1);
            }
 printf("\n Writing File %s.." , filename);
 count = 0;


/*--reading directory and writing---------------------------------------------*/
 while((de = readdir(dr)) != NULL)
 {
  if(strcmp(de->d_name , ".") == 0 || strcmp(de->d_name , "..") == 0)                  //not to select "current directory" and "previous directory"
  continue;

 len = strlen(de->d_name);

 if(strncmp(de->d_name + len - ext_len, newblock_extension , 12) == 0)                        //length of string ".transaction" is 12.
 {
  fprintf(fp , "%s\n" , de->d_name);
  count++;
  }
 }

 fclose(fp);
 closedir(dr);

/*--sorting name in alphabetical order---------------------------------------------*/
 name = (char**)malloc(sizeof(char*)*count);
 for(i = 0; i < count; i++)
  name[i] = (char*)malloc(sizeof(char*)*NAME_SIZE);

 fp = fopen(filename,"r");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s for reading to sort contents." , filename);
           exit(1);
            }

 printf("\n Reading File %s.." , filename);
 for(i = 0 ; i< count; i++)
  fscanf(fp,"%s",name[i]);
 fclose(fp);

 printf("\n Sorting contents of %s.." , filename);
 for(i=0; i < count; i++)
 {
  for(j=0; j < count-i-1; j++)
  {
   if(strcmp(name[j] , name[j+1])>0)
   {
    tempo = name[j];
    name[j] = name[j+1];
    name[j+1] = tempo;
    }
   }
  }


/*-----------------------------------------------*/
  strcpy(tempfile,"temp.txt");
  full_path(miner,tempfile);

   fp = fopen(tempfile,"w");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s for writing to sort contents." , filename);
           exit(1);
            }
 printf("\n Writing to %s.." , tempfile);
   for(i=0 ; i<count; i++)
   { 
    fprintf(fp,"%s\n",name[i]);
    free(name[i]);
    }


  free(name);
 printf("\n Freed the memory given to name..");

   fclose(fp);

remove(filename);
printf("\n Delelted %s.." , filename);
rename(tempfile , filename);
printf("\n Renamed %s to %s..", tempfile , filename);


/*-----------------------------------------------*/

strcpy(filename , "no_of_new_blocks.txt");
full_path(miner , filename);
   fp = fopen(filename , "w");
          if(fp == NULL)
          {
           printf("\n\tERROR: CANNOT OPEN %s  for writing number of new blocks." , filename);
           exit(1);
            } 
fprintf(fp , "%hu" , count);
fclose(fp);
printf("\n No of records written to %s.." , filename);
 }
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include"betacoin.h"


int main()
{
 strcpy(folder , getenv("HOME"));
 strcat(folder , "/betacoin");

 struct transaction temp;
 struct user use;
 FILE *fp;
 short i;
 char name[201];
 char t;
 struct timeval tv;

 printf("Enter name: ");
 scanf("%[^\n]s",name);
 t = 0;
 while(t != '\n')
  t = getchar();
 

 strcat(name,".transaction");

 
 printf("Enter recievers id: ");
  scanf("%[^\n]s", temp.reciever_id);
 t = 0;
 while(t != '\n')
  t = getchar();
 printf("Enter amount: ");
 scanf("%Lf",&temp.amount);
 printf("\n%LF\n" , temp.amount);
 

// printf("%s",name);
 gettimeofday(&tv, NULL);                //or system("date +%s"), tells us the number of seconds passed since 1970-01-01 00:00:00 UTC.

 temp.timestamp= tv.tv_sec;

 strcpy(filename , "sha.256");
 full_path(binary , filename);
 fp = fopen(filename , "rb");
 fread(&use , sizeof(struct user) , 1 , fp);
 fclose(fp);

 strcpy(temp.sender_id , use.wallet_id);

 strcpy(temp.t_id , name);
 full_path(miner , temp.t_id);
 
 temp.transaction_fee = 0;

 fp = fopen(temp.t_id , "wb");
 fwrite(&temp,sizeof(temp),1,fp);
 fclose(fp);
 }

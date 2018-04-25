#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>
#include"betacoin.h"


int main()
{
 struct transaction temp;
 FILE *fp;
 short i;
 char name[201];
 struct timeval tv;

 printf("Enter name: ");
 scanf("%[^\n]s",name);

 strcat(name,".transaction");

 printf("Enter amount: ");
 scanf("%Lf",&temp.amount);

 strcpy(temp.t_id , getenv("HOME"));
 strcat(temp.t_id ,"/betacoin/miner/");
 strcat(temp.t_id , name);

// printf("%s",name);
 gettimeofday(&tv, NULL);                //or system("date +%s"), tells us the number of seconds passed since 1970-01-01 00:00:00 UTC.

 temp.timestamp= tv.tv_sec;

 fp = fopen(temp.t_id , "wb");
 fwrite(&temp,sizeof(temp),1,fp);
 fclose(fp);
 }

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>

#define FILE_SIZE 201

struct transaction
{
 unsigned char t_id[FILE_SIZE];                     //It is the name of transaction file (*.transaction) which is string concat of wallet_id+timestamp;                  
 long double amount;                                                  //amount to be debited from account
 unsigned char transaction_fee;                                       //char can be used a integer with range 0-255. Transaction fee will not be greater than that.
 unsigned long timestamp;
 /* data types for 'public key' of reciever,
    'digital signature' of sender and         */
 }temp;



int main()
{
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

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>


#ifdef __linux__
 char t[201] = "/home/";

#elif __APPLE__
 char t[201] = "/Users/";

#else
 printf("OS Not found");

#endif



struct transaction
{
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
 char folder[20];
 struct timeval tv;

 printf("Enter name: ");
 scanf("%[^\n]s",name);

 strcat(name,".transaction");

 printf("Enter amount: ");
 scanf("%Lf",&temp.amount);

 getlogin_r(folder,201);                  //saves the current logged in user_name in "folder"

 strcat(t,folder);
 strcat(t,"/betacoin/miner/");
 strcat(t,name);
 strcpy(name,t);

 gettimeofday(&tv, NULL);                //or system("date +%s"), tells us the number of seconds passed since 1970-01-01 00:00:00 UTC.

 temp.timestamp= tv.tv_sec;

 fp = fopen(name, "wb");
 fwrite(&temp,sizeof(temp),1,fp);
 fclose(fp);
 }

#include<stdio.h>
#include<string.h>
#include<unistd.h>

struct transaction
{
 long double amount;                                                  //amount to be debited from account
 unsigned char transaction_fee;                                       //char can be used a integer with range 0-255. Transaction fee will not be greater than that.

 /* data types for 'public key' of reciever,
    'digital signature' of sender and 
    'time-stamp' yet to be declared.         */
 }temp;



int main()
{
 FILE *fp;
 short i;
 char name[201];
 char t[201]="/home/";
 char folder[20];

 printf("Enter name: ");
 scanf("%[^\n]s",name);

 printf("Enter amount: ");
 scanf("%Lf",&temp.amount);

 getlogin_r(folder,201);                  //saves the current logged in user_name in "folder"

 strcat(t,folder);
 strcat(t,"/bitcoin/miner/");
 strcat(t,name);
 strcpy(name,t);

 fp = fopen(name, "wb");
 fwrite(&temp,sizeof(temp),1,fp);
 fclose(fp);

 }

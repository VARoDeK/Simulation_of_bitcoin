#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>


struct block
{
 unsigned int magic_number;
 unsigned int block_size;
 unsigned char previous_block_hash[65];
 unsigned char merkle_hash[65];
 unsigned long timestamp;
 unsigned long difficulty_target; //no_of_zeros
 unsigned long nonce;
 unsigned int no_of_transaction;
 transaction_list;
 }

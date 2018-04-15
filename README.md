# Simulation_of_bitcoin

Steps for using this version is given at last.

This is the group project of our subject, SDF (Software Development Fundamentals), for our first year.

The boundaries decided by the syllabus and technical skills we acquired till now, are:
- we have to use any of the data structures we have leanred about. (linked lists or binary tree).
- The project has to be made using c.


The discussion finally ended on this topic, suggested by my cousin, to whom I asked for help. As Bitcoin is based on "block chain", it replicates the behaviour of linked list. The "hash" of previous block is stored in the current block. Also before the construction of a block, the transactions are buffered in a Merkle tree. Hence a binary tree is used.

1- We will use several POSIX machines and connect them to Internet using a signle router. Hence there will be zero probability of conflicting hostnames. 

2- Then we will make SCP protocols between those machines passwordless, by making SSH passwordless, as both SCP and SSH work with some same setting files. 

3- Whole "Betacoin" will not be written in a single .c file. The project will be divided in various .c files, each performing their own task.

4- For example, there will be sepearte .c programs to request transaction, create block, make merkle tree etc.

5- Suppose, 1st program generated an output which is an argument for another c program. Since project is divided into different .c files, we will save that ouput in a file so that when another program executes, it can read for arguments. 

6- All the data, of which sha256 has to be created, will be written in " ~/bitcoin/miner/input.txt " file. So that another 'c' program can read it from there and the output will be saved in " ~/bitcoin/miner/output.txt " file.

7- To generate sha256, we will not write 'c' function for it. sha256 is builtin in python, hence we will integrate python program to generate sha.




Steps for usage of this version
Note: only merkle tree has been built, and "first_run.c".

Step1- Compile and run "first_run.c" . This will create necessary folders on your system and copy some fies.

Step2- To test merkle tree, we need some fake transaction records. Hence, compile and run "create_temp_transaction.c". Enter name for that file and amount of transaction.In future updates of UI, the names for transaction files will be automatically generated. (Fake transactions will remain fake, once blockhain formation starts.)

Step3- Now compile and run "merkle_tree.c". Then go to " ~/betacoin/miner " folder and open "merkle_hash.txt", you will get your sha256 of your merkle tree.


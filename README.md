# Simulation_of_bitcoin
- [x] The Project is made for [POSIX](https://en.wikipedia.org/wiki/POSIX) systems.

##### * This is the group project of our subject, SDF (Software Development Fundamentals), for the first year of our college.
##### * Steps, for using this version, are given at last.

----------------------------------------------------------------------------------------------------

### The boundaries decided by the syllabus and technical skills we have acquired till now, are:
- Project has to include any of the data structures we have learned about. ([linked lists](https://www.geeksforgeeks.org/data-structures/linked-list/) and/or [binary tree](https://www.geeksforgeeks.org/binary-tree-data-structure/)).
- The project has to be made using [C](https://en.wikipedia.org/wiki/C_(programming_language)) language.
- Due to unawareness about socket programming and protocols, the transfer of files between two POSIX systems is made using "[SCP](https://en.wikipedia.org/wiki/Secure_copy)". That will be made password-less using [ssh](https://en.wikipedia.org/wiki/Secure_Shell) keygen.
- [SHA256](https://en.wikipedia.org/wiki/Secure_Shell) and [MD5](https://en.wikipedia.org/wiki/MD5) hashing is done using Python3 inbuilt functions.
- 2-3 Steps are Manual.
- At few places Safety and Security are compromised, as it is just a simulation and we are bound with syllabus.

----------------------------------------------------------------------------------------------------

## Summary on working
As [Bitcoin](https://en.wikipedia.org/wiki/Bitcoin) is based on "[block chain](https://en.wikipedia.org/wiki/Blockchain)", it replicates the behaviour of linked list. The "[hash](https://en.wikipedia.org/wiki/Cryptographic_hash_function)" of previous block is stored in the current block. Also before the construction of a block, the transactions are buffered in a [Merkle tree](https://en.wikipedia.org/wiki/Merkle_tree), hence a binary tree is used.

1- We will use several [POSIX](https://en.wikipedia.org/wiki/POSIX) systems, each of them having unique hostnames, and connect them to local network using a router. The work of router is just to eastablish the network, not to connect them to internet. Hence there will be zero probability of conflicting hostnames of systems for that router. 

2- Then we will make [SCP](https://en.wikipedia.org/wiki/Secure_copy) between those machines, passwordless, by making SSH keys, as both SCP and SSH work with same settings-files. 

3- Whole "Betacoin" will not be written in a single `.c` file. The project will be divided in various `.c` files, each performing their own task.

4- For example, there will be sepearte `.c` programs to request transaction, create block, make merkle tree etc.

5- We will use [system calls](https://www.geeksforgeeks.org/system-call-in-c/) to call and run different `.c` programs in between. Suppose while mining, during execution of a one `.c` program we will have to call the various `.c` programs:
  * `system(\_path_to_c_program_\.merkle_tree.out);` to calculate merkle [SHA256](https://en.wikipedia.org/wiki/Secure_Shell).
  * `system(\_path_to_c_program_\.create_block.out);` to create new block.
  * `system(\_path_to_c_program_\.send_newblock.out);` to send newly mined block to other miners for verification.
...etc.

6- Assume, 1st program generated an output which is an argument for 2nd [C](https://en.wikipedia.org/wiki/C_(programming_language)) program. Since project is divided into different `.c` files, we will save that ouput in a specific, file so that when 2nd program executes, it can read that particular file for arguments. 

7- All the data, of which [SHA256](https://en.wikipedia.org/wiki/Secure_Shell) has to be created, will be written in " `~/bitcoin/miner/input.txt` " file. So that another [C](https://en.wikipedia.org/wiki/C_(programming_language)) program can read it from there and the output will be saved in "` ~/bitcoin/miner/output.txt` " file.

8- To generate [SHA256](https://en.wikipedia.org/wiki/Secure_Shell), we will not write [C](https://en.wikipedia.org/wiki/C_(programming_language)) function for it. sha256 is builtin in python, hence we will integrate python program to generate [SHA256](https://en.wikipedia.org/wiki/Secure_Shell) using [system calls](https://www.geeksforgeeks.org/system-call-in-c/).

----------------------------------------------------------------------------------------------------

## STEPS FOR USAGE OF THIS VERSION

Assuming that users have cloned the software and have [gcc](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) and python3 installed.

* Step1- Compile and run `first_run.c`. This will create necessary folders on your system, copy some files and compile other `.c` files and store their executables in `~/betacoin/binary`.

* Step2- Open Terminal and type: `~/index`

* Step3- At first, it will ask you to create account. After submitting details, confirm.
 On account creation, you will get 1000 betacoins. This is similar to minimum account balance required to open account in conventional banking system.
  - THE `ACCOUNT NUMBER` IS SAME AS `WALLET ID`.
  -In main menu, opt to check user details, there you will get to know your `<user_name>@<host_name>`.
  - Take a group of systems, let's say system `A`, `B` and `C`.
  - CONNECT ALL THE SYSTEMS TO THE SAME ROUTER.
  - Then enable `password-less ssh` for each of the pair. `A->B` , `B->A` , `B->C` , `C->B` , `A->C` and `C->A`.
  - To go for passwrod-less ssh, follow instructions from net.
  - To do so, you will require `<user_name>@<host_name>` of other users, which you will get know from their user details. And other users will require your's which they will get from your user details.

* Step4- Opt for "`make a transaction`", you will be driven to another menu, `Transaction Menu`. 
 First you need to add beneficiaries to your account. Feed the account numbers of your beneficiaries.
 After adding, each beneficiary record will get an ID number which you can see by opting "`view beneficiary`" in Transaction Menu. 
   While making any transaction you just need to enter that ID number and details will be feeded in transaction record, automatically.

* Step5- Enter option `E` in main menu and become a miner.   

* Step6- After making several transactions, enter option `D` in main menu and mine your block. After mining, your block will be send to other miners for verification. 
    * Other miners should keep on checking their `~/betacoin/verify folder`.
    * Users should mine their block one by one. Simultaneously all systems should not mine their blocks together as this version of this software does not support this scenerio.
    * Once `~/betacoin/verify` is non-empty, it means a newblock is sent by any of the miner for verification.
    * In main menu of other miners, they will ente option `J` and verify the block.
    * Once the block is verified by other miners, it will be added to their blockchain.

* Step7- Opt for "`synchronize`" in main menu, your blockchain will also be updated.

* Step8- Opt for recalculation of balance, it will read each and every block of blockchain and calculate you balance.

And you can now make more transactions, mine your block keep going. 




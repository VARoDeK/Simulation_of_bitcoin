# Simulation_of_bitcoin

This is the group project of our subject, SDF (Software Development Fundamentals), for our first year.

The boundaries decided by the syllabus and technical skills we acquired till now, are:
- we have to use any of the data structures we have leanred about. (linked lists or binary tree).
- The project has to be made using c.


The discussion finally ended on this topic, suggested by my cousin, to whom I asked for help. As Bitcoin is based on "block chain", it replicates the behaviour of linked list. The "hash" of previous block is stored in the current block. Also before the construction of a block, the transactions are buffered in a Merkle tree. Hence a binary tree is used.

We will use several "LINUX" or "LINUX" based machines and connect them to Internet using a signle router. Hence it will not be a problem to find the IP addresses of machines, we want to use as "nodes". Most Probably we will provide the machines with unique local "Host names". So until they are connected to same router, we can ping them using their hostnames (No need of IP addresses).

As we don't know about socket programming we will send transaction request, in the form of a file, through "scp".

Merkle Tree will have 8 nodes. Hence each block of bitcoin chain will keep record of atmost 8 transactions.

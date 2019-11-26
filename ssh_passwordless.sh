#!/bin/bash
read -p "Enter the username: " uname
read -p "Enter hostname/ip: " host

ssh-keygen -t rsa
ssh $uname@$host mkdir -p .ssh
cat ~/.ssh/id_rsa.pub | ssh $uname@$host 'cat >> .ssh/authorized_keys'
ssh $uname@$host "chmod 700 .ssh; chmod 640 .ssh/authorized_keys"

echo "You can login now. Type: ssh $uname@$host "

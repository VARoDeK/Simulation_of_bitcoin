from hashlib import sha256
from os import environ
from sys import exit


homedir = environ['HOME']

path = homedir + "/betacoin/sha/" + "input.txt"
try:
    f = open(path, "r")
except FileNotFoundError:
    print("File doesn't exist at destination")
    exit()

a = f.read()
a = a[:-1].encode(encoding="utf-8")
f.close()

m = sha256()
m.update(a)

path = homedir + "/betacoin/sha/" + "output.txt"
f = open(path, "w")
f.write(m.hexdigest())
f.close()

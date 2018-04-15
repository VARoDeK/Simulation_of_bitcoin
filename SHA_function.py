import hashlib
import os
import sys


homedir = os.environ['HOME']

path = homedir + "/betacoin/sha/" + "input.txt"
try:
    f = open(path, "r")
except FileNotFoundError:
    print("File doesn't exist at destination")
    sys.exit()

a = f.read()
a = a[:-1].encode(encoding="utf-8")
f.close()

m = hashlib.sha256()
m.update(a)

path = homedir + "/betacoin/sha/" + "output.txt"
f = open(path, "w")
f.write(m.hexdigest())
f.close()

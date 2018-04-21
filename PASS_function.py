import getpass

try:
	p = getpass.getpass(prompt="Enter password: ")
except  Exception as error:
	print("Error: ", error)
else:
	print("Password entered: ", p)

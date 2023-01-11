from os import popen
from random import randint
from termcolor import colored

i = 1

while True:
	print(i)
	i += 1
	test = popen("./gen").read()
	f = open("input.txt", "w")
	f.write(test)
	f.close()
	bad = popen("./bad < input.txt").read()
	good = popen("./good < input.txt").read()
	if bad != good:
		print(colored("TEST", 'light_blue', attrs=['bold']))
		print(test)
		print(colored("BAD", 'red', attrs=['bold']))
		print(bad)
		print(colored("GOOD", 'green', attrs=['bold']))
		print(good)
		break

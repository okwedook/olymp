from os import popen
from random import randint

i = 1

while True:
	print(i)
	i += 1
	f = open("input.txt", "w")
	f.write(str(randint(1, 10000000)))
	f.close()
	test = popen("./gen < test.txt").read()
	f = open("input.txt", "w")
	f.write(test)
	f.close()
	bad = popen("./bad < input.txt").read()
	good = popen("./good < input.txt").read()
	if bad != good:
		print("TEST")
		print(test)
		print("BAD")
		print(bad)
		print("GOOD")
		print(good)
		break

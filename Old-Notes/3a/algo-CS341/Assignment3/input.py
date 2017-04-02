import random
import os
import time
import sys

inputs = [10, 50, 100, 150, 200, 250, 300, 500, 750, 1000]

for n in inputs:
    f = open('test.txt', 'w')
    f.write(str(n) + "\n")

    x = sorted(random.sample(range(1, 2000), n))
    y = random.sample(range(1, 2000), n)

    for i in xrange(n):
        f.write(str(x[i]) + " ")
        f.write(str(y[i]) + " ")
        f.write(str(random.randint(0, 1)) + "\n")

    f.close()

    #print n,
    #print "&",
    os.system("clang++ a3.cpp")
    start = time.time()
    os.system("./a.out < test.txt > output1.txt")
    end = time.time()
    #print end - start,

    #print "&",
    os.system("clang++ a3_brute.cpp")
    start = time.time()
    os.system("./a.out < test.txt > output2.txt")
    end = time.time()

    os.system("cat output1.txt")
    os.system("cat output2.txt")
    print(" ")

    #print end - start,
    #print "\\\\"
    #print "\\hline"

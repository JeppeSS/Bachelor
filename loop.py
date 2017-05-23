#!/usr/bin/python

import os

os.system("echo '' > out.txt")
for i in range(3) :
    os.system("./program.o >> out.txt")

fo = open("out.txt", "r")
f = fo.readlines()
fo.close()

fo = open("out.txt", "w")
for line in f :
    s = line.split(" ", 1)
    if (s[0] != "[OK]") :
        fo.write(line)
fo.close()
    
    

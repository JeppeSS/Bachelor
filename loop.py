#!/usr/bin/python

import os
import sys

# ------------------------ARGUMENTS-------------------------- #
# 1. Number of iterations                                     #
# 2. Plaintext bit string                                     #
# 3. 1 if result should be printed to terminal, 0 otherwise   #
# ----------------------------------------------------------- #

args = sys.argv
loops = int(args[1])
plain = args[2]
write = int(args[3])
match = 0

os.system("echo '-------------' > out.txt")
for i in range(loops) :
    os.system("./testKeyGen.o >> out.txt")
    os.system("echo '-------------' >> out.txt")

fo = open("out.txt", "r")
f = fo.readlines()
fo.close()

fo = open("out.txt", "w")
fo.write("Plaintext: " + plain + "\n")
fo.write("Decrypted ciphertexts:")
for line in f :
    s = line.split(" ", 1)
    if (s[0] != "[OK]") :
        if (s[0] == '-------------\n') :
            fo.write('\n' + line)
        else :
            fo.write(line.rstrip())
fo.close()

fo = open("out.txt", "r")
f = fo.readlines()
fo.close()
    
for line in f :
    if line.rstrip() == plain :
        match += 1

with open("out.txt", "a") as f :
    f.write("Matches: " + str(match) + "/" + str(loops)  + "\n")
f.close()

if write :
    with open("out.txt", "r") as f :
        lines = f.readlines()
        for line in lines :
            print line.rstrip()

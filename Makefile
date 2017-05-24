all: testKeyGen testSKWrite testPKWrite

HEADERS = Database.h Filemanager.h DGHV.h keyGen.h random.h

testKeyGen: testCrypto.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testKeyGen.o DGHV.c Filemanager.c random.c keyGen.c testCrypto.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

testPKWrite: testPKWrite.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testPKWrite.o DGHV.c Filemanager.c random.c keyGen.c testPKWrite.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

testSKWrite: testSKWrite.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testSKWrite.o DGHV.c Filemanager.c random.c keyGen.c testSKWrite.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

clean:
	-rm -f testPKWrite.o
	-rm -f testSKWrite.o
	-rm -f testKeyGen.o
	-rm -f testPKWrite
	-rm -f testKeyGen
	-rm -f testSKWrite

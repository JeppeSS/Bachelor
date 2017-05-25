all: testKeyGen testSKWrite testSKRead testPKRead testPKWrite testWrongKey

HEADERS = Database.h Filemanager.h DGHV.h keyGen.h random.h

testKeyGen: testCrypto.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testKeyGen.o DGHV.c Filemanager.c random.c keyGen.c testCrypto.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

testPKWrite: testPKWrite.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testPKWrite.o DGHV.c Filemanager.c random.c keyGen.c testPKWrite.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

testSKWrite: testSKWrite.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testSKWrite.o DGHV.c Filemanager.c random.c keyGen.c testSKWrite.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

testSKRead: testSKRead.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testSKRead.o DGHV.c Filemanager.c random.c keyGen.c testSKRead.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

testPKRead: testPKRead.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testPKRead.o DGHV.c Filemanager.c random.c keyGen.c testPKRead.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

testWrongKey: testWrongKey.c DGHV.c Filemanager.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o testWrongKey.o DGHV.c Filemanager.c random.c keyGen.c testWrongKey.c -lm -lgmp -fopenmp `mysql_config --cflags --libs`  

clean:
	-rm -f testPKWrite.o
	-rm -f testSKWrite.o
	-rm -f testSKRead.o
	-rm -f testPKRead.o
	-rm -f testKeyGen.o
	-rm -f testWrongKey.o
	-rm -f testPKWrite
	-rm -f testKeyGen
	-rm -f testSKWrite
	-rm -f testSKRead
	-rm -f testPKRead
	-rm -f testWrongKey

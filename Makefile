HEADERS = Database.h DGHV.h keyGen.h random.h

program.o: testCrypto.c DGHV.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -o program.o DGHV.c random.c keyGen.c testCrypto.c -lm -lgmp `mysql_config --cflags --libs`  
program: program.o
	gcc program.o -o program

clean:
	-rm -f program.o
	-rm -f program

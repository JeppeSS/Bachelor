HEADERS = Database.h keyGen.h test_keyGen.h tools.h partial_enc.h

program.o: testCrypto.c tools.c keyGen.c test_keyGen.c partial_enc.c $(HEADERS)
	gcc -Wall -std=c11 -o program.o keyGen.c tools.c testCrypto.c test_keyGen.c partial_enc.c -lm -lgmp `mysql_config --cflags --libs`
program: program.o
	gcc program.o -o program

clean:
	-rm -f program.o
	-rm -f program

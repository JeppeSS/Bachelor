HEADERS = Database.h Filemanager.h keyGen.h random.h

program.o: main.c Database.c random.c keyGen.c $(HEADERS)
	gcc -Wall -std=c11 -lgmp `mysql_config --cflags --libs` -o program.o Database.c Filemanager.c main.c  
program: program.o
	gcc program.o -o program

clean:
	-rm -f program.o
	-rm -f program

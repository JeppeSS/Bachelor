HEADERS = Database.h

program.o: main.c Database.c $(HEADERS)
	gcc -Wall -o program.o Database.c main.c `mysql_config --cflags --libs` 
program: program.o
	gcc program.o -o program

clean:
	-rm -f program.o
	-rm -f program

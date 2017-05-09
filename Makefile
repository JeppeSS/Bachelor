HEADERS = Database.h Filemanager.h

program.o: main.c Database.c $(HEADERS)
	gcc -Wall -std=c11 -o program.o Database.c Filemanager.c main.c `mysql_config --cflags --libs` 
program: program.o
	gcc program.o -o program

clean:
	-rm -f program.o
	-rm -f program

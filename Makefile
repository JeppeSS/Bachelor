TARGET = testCrypto.o testSKWrite.o testSKRead.o testPKRead.o testPKWrite.o testWrongKey.o testPlaintext.o
SRC = DGHV.c Filemanager.c random.c keyGen.c Plaintext.c
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g 
LIBS = -lm -lgmp -fopenmp $(mysql_config --cflags --libs)

$(info The Almanac program requires GMP version 6.1.2, see https://gmplib.org/)
$(info )


.PHONY: default all clean

default: $(TARGET)
all: $(TARGET)

HEADERS = $(wildcard *.h)

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): %.o: %.c
	$(CC) $< $(SRC) $(CFLAGS)$ $(LIBS)-o $@

clean:
	-rm -f *.o

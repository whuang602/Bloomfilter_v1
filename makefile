CC = g++
CFLAGS = -Wall -g

all: main.o bloomFilter.h hash.h utility.h 
	$(CC) $(CFLAGS) -o PA1 main.o

clean: 
	rm -f PA1 main.o
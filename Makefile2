all: ep1 ep1sh

queue.o: queue.c
	gcc -Wall -g -c -o queue.o queue.c	

ep1: ep1.o queue.o
	gcc -g -lreadline -pthread -o ep1 ep1.o queue.o

ep1.o: ep1.c queue.h
	gcc -Wall -g -c -o ep1.o ep1.c

ep1sh: ep1sh.o
	gcc -g -lreadline -pthread -o ep1sh ep1sh.o

ep1sh.o : ep1sh.c
	gcc -Wall -g -c -o ep1sh.o ep1sh.c
clean:
	rm -rf *.o
	rm ep1sh
	rm ep1

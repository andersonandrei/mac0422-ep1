all: ep1 ep1sh

ep1: ep1.o
	gcc -g -lreadline -pthread -o ep1 ep1.o

ep1.o: ep1.c
	gcc -Wall -g -c -o ep1.o ep1.c

ep1sh: ep1sh.o
	gcc -g -lreadline -pthread -o ep1sh ep1sh.o

ep1sh.o : ep1sh.c
	gcc -Wall -g -c -o ep1sh.o ep1sh.c
clean:
	rm -rf *.o
	rm ep1sh
	rm ep1

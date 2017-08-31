ep1sh: ep1sh.o
	gcc -g -lreadline -o ep1sh ep1sh.o

ep1sh.o : ep1sh.c
	gcc -Wall -g -c -o ep1sh.o ep1sh.c
clean:
	rm -rf *.o
	rm ep1sh

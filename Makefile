CC:=gcc
CFLAGS:=-Wall -g -lpthread


ep1: ep1.o schedulerSJF.o schedulerRoudRobin.o schedulerPriority.o queue.o
	$(CC) $(CFLAGS) -o $@ $^

# ep1sh: ep1sh.o ep1.o schedulerSJF.o schedulerRoudRobin.o schedulerPriority.o queue.o
# 	$(CC) $(CFLAGS) -o $@ $^
#General formulas for making objects
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o
	rm ep1sh
	rm ep1

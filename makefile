all: demo
CFLAGS = -Wall -Wextra

constructs.o: constructs.c
	$(CC) $(CFLAGS) -c constructs.c
supportivefuncs.o: supportivefuncs.c
	$(CC) $(CFLAGS) -c supportivefuncs.c
otherfuncs.o: otherfuncs.c
	$(CC) $(CFLAGS) -c otherfuncs.c
bitcellB.o: bitcellB.c
	$(CC) $(CFLAGS) -c bitcellB.c
ownerfuncs.o: ownerfuncs.c
	$(CC) $(CFLAGS) -c ownerfuncs.c 
contlist.o: contlist.c 
	$(CC) $(CFLAGS) -c contlist.c
fiolist.o: fiolist.c 
	$(CC) $(CFLAGS) -c fiolist.c

demo: constructs.o otherfuncs.o supportivefuncs.o bitcellB.o contlist.o ownerfuncs.o fiolist.o demo_4.c
	$(CC) $(CFLAGS) -o demo contlist.o constructs.o otherfuncs.o supportivefuncs.o bitcellB.o ownerfuncs.o fiolist.o demo_4.c -g

run: 
	clear && ./demo save out
	./demo load out
	./demo get 3 out
clean:
	rm demo
	rm *.o 

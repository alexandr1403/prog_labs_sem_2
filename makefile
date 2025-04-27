all: demo
CFLAGS = -Wall -Wextra -Werror

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

run = clear && ./demo

save_text: 
	$(run) save out -t 
save_bin:
	$(run) save out2 -b
load_text:
	$(run) load out -t 
load_bin:
	$(run) load out2 -b
list_text:
	$(run) list out -t 
list_bin:
	$(run) list out2 -b 
get_text:
	$(run) get 2 out -t 
get_bin:
	$(run) get 2 out2 -b 
demo_container_element_text:
	$(run) cont out -t 
demo_container_element_bin:
	$(run) cont out2 -b

run: 
# clear && ./demo save out -t
# ./demo load out2 -b
# ./demo get 3 out -b
	./demo list out -t
clean:
	rm *.o 
	rm demo


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

demo: constructs.o otherfuncs.o supportivefuncs.o bitcellB.o contlist.o ownerfuncs.o fiolist.o fiotest.c
	$(CC) $(CFLAGS) -o demo contlist.o constructs.o otherfuncs.o supportivefuncs.o bitcellB.o ownerfuncs.o fiolist.o fiotest.c -g

run = clear && ./demo

save_text: 
	$(run) save out -t 
save_bin:
	$(run) save out2 -b
load_text:
	$(run) load out -t > res
load_bin:
	$(run) load out2 -b > res
list_text:
	$(run) list out -t > res
list_bin:
	$(run) list out2 -b > res
get_text:
	$(run) get 2 out -t > res
get_bin:
	$(run) get 4 out2 -b > res 
demo_container_element_text:
	$(run) cont out -t > res 
demo_container_element_bin:
	$(run) cont out2 -b > res 
miss_few:
	$(run) out 
miss_incorrect:
	$(run) out out out

run: 
	./demo list out -t
clean:
	rm *.o 
	rm demo


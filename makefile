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

save_text_l: 
	$(run) save -l out -t 
save_bin_l:
	$(run) save -l out2 -b

save_text_m: 
	$(run) save -m out -t 
save_bin_m:
	$(run) save -m out2 -b

load_text_l:
	$(run) load -l out -t > res
load_bin_l:
	$(run) load -l out2 -b > res

load_text_m:
	$(run) load -m out -t > res
load_bin_m:
	$(run) load -m out2 -b > res

get_text_m:
	$(run) get 2 -m out -t > res
get_bin_m:
	$(run) get 4 -m out2 -b > res 

get_text_l:
	$(run) get 20 -l out -t > res
get_bin_l:
	$(run) get 55 -l out2 -b > res 

list_text:
	$(run) list out -t > res
list_bin:
	$(run) list out2 -b > res

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./demo save out -t

miss_few:
	$(run) out 
miss_incorrect:
	$(run) out out out out
miss_many:
	$(run) this input has too many arguments to start program

clean:
	rm *.o 
	rm demo

CC=gcc
CFLAGS=-pthread -I. -Wall -Wno-int-conversion -D_GNU_SOURCE 

binaries=primes

all: $(binaries)

primes: counter.c primes.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) -f $(binaries) *.o


 

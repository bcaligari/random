CC=gcc
CFLAGS=-g -Wall -Wextra

dummy :
	true

orphaniser : orphaniser.c
	$(CC) $(CFLAGS) -o orphaniser orphaniser.c

zombiemaker : zombiemaker.c
	$(CC) $(CFLAGS) -o zombiemaker zombiemaker.c

forkbomber : forkbomber.c
	$(CC) $(CFLAGS) -o forkbomber forkbomber.c

segfaulter : segfaulter.c
	$(CC) $(CFLAGS) -o segfaulter segfaulter.c

writer : writer.c
	$(CC) $(CFLAGS) -o writer writer.c

reader : reader.c
	$(CC) $(CFLAGS) -o reader reader.c

memeater : memeater.c
	$(CC) $(CFLAGS) -o memeater memeater.c

clone : clone.c
	$(CC) $(CFLAGS) -o clone clone.c

clean :
	rm -f *.o core.* \
	orphaniser zombiemaker forkbomber segfaulter \
	clone \
	writer reader \
	memeater

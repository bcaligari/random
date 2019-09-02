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

writer-write2 : writer-write2.c
	$(CC) $(CFLAGS) -o writer-write2 writer-write2.c

writer-fputs3 : writer-fputs3.c
	$(CC) $(CFLAGS) -o writer-fputs3 writer-fputs3.c

memeater : memeater.c
	$(CC) $(CFLAGS) -o memeater memeater.c

clone-pid-tid : clone-pid-tid.c
	$(CC) $(CFLAGS) -o clone-pid-tid clone-pid-tid.c

getuid : getuid.c
	$(CC) $(CFLAGS) -o getuid getuid.c

clean :
	rm -f *.o core.* \
	orphaniser zombiemaker forkbomber segfaulter \
	clone-pid-tid getuid \
	writer reader \
	memeater

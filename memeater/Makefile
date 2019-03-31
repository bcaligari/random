CC=gcc
CFLAGS=-g -Wall -Wextra
CFLAGS_STATIC=-g -Wall -Wextra -static -static-libgcc
DOCKER=docker

memeater : memeater.c
	$(CC) $(CFLAGS) -o memeater memeater.c

memeater-static : memeater.c
	$(CC) $(CFLAGS_STATIC) -o memeater-static memeater.c

container : memeater-static
	$(DOCKER) image build -t bcaligari/memeater .

clean :
	rm -f *.o core.* memeater memeater-static

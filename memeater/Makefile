CC=gcc
CFLAGS=-g -Wall -Wextra -static -static-libgcc
DOCKER=docker

memeater : memeater.c
	$(CC) $(CFLAGS) -o memeater memeater.c

container : memeater
	$(DOCKER) image build -t bcaligari/memeater .

clean :
	rm -f *.o core.* memeater

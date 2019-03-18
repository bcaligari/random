#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BS_MAX		256*1024*1024
#define BS_DEF		32*1024*1024
#define INTERVAL_MAX	3600
#define INTERVAL_DEF	5

int meat(int bs, int interval);

int main(int argc, char *argv[])
{
	int opt, parse_broken;
	long interval, bs;

	interval = (long) INTERVAL_DEF;
	bs = (long) BS_DEF;
	parse_broken = 0;
	while ((opt = getopt(argc, argv, "i:s:")) != -1) {
		switch (opt) {
 		case 's':
		 	errno = 0;
			bs = strtol(optarg, NULL, 10);
			if (errno != 0)
				parse_broken = 1;
			break;
 		case 'i':
			errno = 0;
			interval = strtol(optarg, NULL, 10);
			if (errno != 0)
				parse_broken = 1;
			break;
		default:
			parse_broken = 1;
 		}
	}

	if ((bs <= 0) || (bs > BS_MAX))
		parse_broken = 1;

	if ((interval < 0) || (interval > INTERVAL_MAX))
		parse_broken = 1;

	if (parse_broken) {
		fprintf(stderr, "Usage: %s [-i secs] [-s bytes]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	meat((int) bs, (int) interval);

	exit(EXIT_SUCCESS);
}

int meat(int bs, int interval)
{
	long total = 0;
	void *ptr;
	printf("%d: Allocating and filling %d bytes (%d MiB) with %d second intervals\n",
		(int) getpid(),
		bs,
		bs >> 20,
		interval
	);
	fflush(NULL);
	for (;;) {
		total += bs;
		printf("%d: Allocating total of %ld bytes (%ld MiB)\n",
			(int) getpid(),
			total,
			total >> 20);
		fflush(NULL);
		ptr = malloc((size_t) bs);
		if (ptr != NULL)
       			memset(ptr, 0, bs);
		sleep(interval);
	}
	return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

// These values are arbitrary af
#define BS_MAX		256*1024*1024
#define BS_DEF		32*1024*1024
#define INTERVAL_MAX	3600
#define INTERVAL_DEF	5
#define ITER_MAX	2600
#define ITER_DEF	-1
#define FNAME_MAX	64

int meat(int bs, int interval, int iterations, const char *logfile);

int main(int argc, char *argv[])
{
	int opt, parse_broken;
	long bs, interval, iterations;
	char logfile[FNAME_MAX];

	assert(FNAME_MAX <= FILENAME_MAX);

	iterations = (long) ITER_DEF;
	interval = (long) INTERVAL_DEF;
	bs = (long) BS_DEF;
	parse_broken = 0;
	logfile[0] = 0;
	while ((opt = getopt(argc, argv, "i:s:c:f:")) != -1) {
		switch (opt) {
		case 'c':
		 	errno = 0;
			iterations = strtol(optarg, NULL, 10);
			if (errno != 0)
				parse_broken = 1;
			break;
		case 'f':
			if (strlen(optarg) >= FNAME_MAX)
				parse_broken = 1;
			else
				strcpy(logfile, optarg);
			break;
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

	if ((iterations < -1) || (iterations > ITER_MAX))
		parse_broken = 1;

	if ((interval < 0) || (interval > INTERVAL_MAX))
		parse_broken = 1;

	if (parse_broken) {
		fprintf(stderr, "Usage: %s [-i secs] [-s bytes] [-c count] [-f logfile]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	meat((int) bs, (int) interval, (int) iterations, logfile);

	exit(EXIT_SUCCESS);
}

int meat(int bs, int interval, int iterations, const char *logfile)
{
	long total = 0;
	void *ptr;
	int i;
	FILE *f = NULL;
	char s[128];

	if (*logfile)
		if ((f = fopen(logfile, "a")) == NULL) {
			fprintf(stderr, "Fell over opening file %s\n", logfile);
			exit(EXIT_FAILURE);
		}

	sprintf(s, "%d: Consuming %d bytes (%d MiB); %d second intervals; %d max iterations\n",
		(int) getpid(),
		bs,
		bs >> 20,
		interval,
		iterations
	);
	fputs(s, stdout);
	if (f != NULL)
		fputs(s, f);
	fflush(NULL);
	for (i = iterations; i != 0; i--) {
		total += bs;
		sprintf(s, "%d: Allocating aggregate of %ld bytes (%ld MiB)\n",
			(int) getpid(),
			total,
			total >> 20);
		fputs(s, stdout);
		if (f != NULL)
			fputs(s, f);
		fflush(NULL);
		ptr = malloc((size_t) bs);
		if (ptr != NULL)
       			memset(ptr, 0, bs);
		else {
			sprintf(s, "%d: malloc(3) failed: %s (%d)\n",
				(int) getpid(),
				strerror(errno),
				errno);
			fputs(s, stdout);
				if (f != NULL)
					fputs(s, f);
		}
		sleep(interval);
	}
	if (f != NULL)
		fclose(f);
	pause();
	return 0;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define STACK_SIZE	8*1024
#define MSG_LEN		128

static inline void status();

int somevar = 10;

void sidefunc();

int main(void)
{
	char *stack;
	char *err;
	char msg_buf[MSG_LEN];
	stack = malloc((size_t) STACK_SIZE);
	fflush(NULL);
	if (stack == NULL) {
		// we are using GNU version of strerror_r
		if ((err = strerror_r(errno, msg_buf, MSG_LEN)) != NULL)
			printf("malloc(): %s\n", err);
		exit(EXIT_FAILURE);
	}
	status();
	// CLONE_VM => share memory space
	// CLONE_VFORK => wait until child is released
	// CLONE_SIGHAND => share signal handler table
	// CLONE_THREAD => place child in same threading group
	if (clone((void *) &sidefunc,
				(char *) stack + STACK_SIZE,
				CLONE_THREAD|CLONE_SIGHAND|CLONE_VM|CLONE_VFORK,
				NULL) == -1) {
		if ((err = strerror_r(errno, msg_buf, MSG_LEN)) != NULL)
			printf("clone(): %s\n", err);
		exit(EXIT_FAILURE);
	}
	status();
	free(stack);
	return 0;
}

void sidefunc()
{
	somevar = 13;
	status();
	return;
}

static inline void status()
{
	printf("PID: %d; TID: %d; PPID: %d; somevar = %d.\n",
			(int) syscall(SYS_getpid),
			(int) syscall(SYS_gettid),
			(int) syscall(SYS_getppid),
			somevar);
	fflush(NULL);
}

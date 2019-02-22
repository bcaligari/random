#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_FORKS	3				// -ve to fork until fork() fails

int main(void)
{
	int i, count;
	pid_t pid, cpid;

	pid = getpid();
	printf("%d: Forking %d children ...\n", (int) pid, MAX_FORKS);
	for (i = 0, count = 0; i != MAX_FORKS; i++) {
		cpid = fork();
		if (!cpid) {
			pause();
			return 0;
		} else if (cpid == -1) {
			perror("fork");
			break;
		}
		printf("%d: is a child\n", (int) cpid);
		count++;
	}
	printf("%d: pause()ing after forking %d children ...\n", pid, count);
	pause();
	return 0;
}

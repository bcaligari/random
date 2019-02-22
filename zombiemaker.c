#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define ZOMBIE_COUNT		5
#define SECS_BETWEEN_ZOMBIES	120

int main(void)
{
	int i;
	pid_t pid, ppid;

	ppid = getpid();
	printf("%d: parent process starting up\n", (int) ppid);
	for (i = 0; i < ZOMBIE_COUNT; i++) {
		pid = fork();
		if (!pid)
			return 0;
		else if (pid == -1)
			perror("fork");
		else {
			printf("%d: forked pid %d\n", (int) ppid, (int) pid);
			if (SECS_BETWEEN_ZOMBIES) {
				printf("%d: sleep(%d)\n", (int) ppid, SECS_BETWEEN_ZOMBIES);
				sleep(SECS_BETWEEN_ZOMBIES);
			}
		}
	}
	printf("%d: pause()\n", (int) ppid);
	pause();
	return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <syslog.h>

#define ORPHAN_COUNT	2

int main(void)
{
	int i;
	pid_t pid, old_ppid, new_ppid;
	char logmsg[128];

	old_ppid = getpid();
	printf("%d: is parent\n", (int) old_ppid);
	for (i = 0; i < ORPHAN_COUNT; i++) {
		pid = fork();
		if (!pid) {
			pid = getpid();
			for (;;) {
				new_ppid = getppid();
				if (new_ppid != old_ppid) {
					openlog(NULL, LOG_PID, LOG_USER);
					sprintf(logmsg, "ppid changed from %d to %d\n", old_ppid, new_ppid);
					syslog(LOG_DEBUG, logmsg);
					closelog();
					old_ppid = new_ppid;
				}
				sleep(1);
			}
		} else if (pid == -1) {
			perror("fork");
		}
		printf("%d: is a child\n", (int) pid);
	}
	printf("%d: will return after sleep(2) ...\n", old_ppid);
	sleep(2);
	return 0;
}

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
	printf("%d: is parent [pgid = %d; sid = %d]\n",
		(int) old_ppid,
		(int) getpgid((pid_t) 0),
		(int) getsid((pid_t) 0));
	for (i = 0; i < ORPHAN_COUNT; i++) {
		pid = fork();
		if (!pid) {
			pid = getpid();
			for (;;) {
				new_ppid = getppid();
				if (new_ppid != old_ppid) {
					openlog(NULL, LOG_PID, LOG_USER);
					sprintf(logmsg, "ppid changed from %d to %d [pgid = %d; sid = %d]\n",
						old_ppid,
						new_ppid,
						(int) getpgid((pid_t) 0),
						(int) getsid((pid_t) 0));
					syslog(LOG_DEBUG, logmsg);
					closelog();
					old_ppid = new_ppid;
				}
				sleep(1);
			}
		} else if (pid == -1) {
			perror("fork");
		}
		printf("%d: is a child [pgid = %d; sid = %d]\n",
			(int) pid,
			(int) getpgid((pid_t) 0),
			(int) getsid((pid_t) 0));	
	}
	printf("%d: will return after sleep(2) ...\n", old_ppid);
	sleep(2);
	return 0;
}

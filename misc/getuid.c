#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#define UNKNOWN		"???"

/*
	getpwuid etc return a ptr to a struct allocated from some
	internal buffer and doesn't need to be manually freed

	sudo configuration:
		sysop  ALL=(elsebody:players) NOPASSWD: ALL

	$ make getuid
	gcc -g -Wall -Wextra -o getuid getuid.c

	$ chmod u+s,g+s getuid

	$ id
	uid=1000(sysop) gid=100(users) groups=100(users),458(docker),461(vboxusers)

	$ sudo -u elsebody -g players ./getuid
	uid = 1001 (elsebody)
	euid = 1000 (sysop)
	gid = 1000 (players)
	egid = 100 (users)
*/

int main(void)
{
	uid_t uid, euid;
	gid_t gid, egid;
	struct passwd *pw, *epw;
	struct group *gr, *egr;

	uid = getuid();
	pw = getpwuid(uid);
	printf("uid = %d (%s)\n", (int) uid, pw ? pw->pw_name : UNKNOWN);

	euid = geteuid();
	epw = getpwuid(euid);
	printf("euid = %d (%s)\n", (int) euid, pw ? epw->pw_name : UNKNOWN);

	gid = getgid();
	gr = getgrgid(gid);
	printf("gid = %d (%s)\n", (int) gid, gr ? gr->gr_name : UNKNOWN);

	egid = getegid();
	egr = getgrgid(egid);
	printf("egid = %d (%s)\n", (int) egid, egr ? egr->gr_name : UNKNOWN);

	return 0;
}
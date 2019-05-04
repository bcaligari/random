#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//#include <pwd.h>
//#include <grp.h>

/*
	# chown someusr:somgrp ./getuid
	# chmod u+s ./getuid
	# chmod g+s ./getuid
	$ ./getuid
*/

int main(void)
{
	uid_t uid, euid;
	gid_t gid, egid;

	/* TODO - add id to name translation
	struct passwd user, euser;
	struct group grp, egrp;
	*/

	uid = getuid();
	euid = geteuid();
	gid = getgid();
	egid = getegid();

	printf("uid = %d ()\n", (int) uid);
	printf("euid = %d ()\n", (int) euid);
	printf("gid = %d ()\n", (int) gid);
	printf("egid = %d ()\n", (int) egid);
	return 0;
}


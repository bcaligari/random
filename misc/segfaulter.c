#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void somefunc(int i, int j, int *p);

void deepfunc(int i, int *p);

int main(void)
{
	pid_t pid;
	int *p;

	pid = getpid();
	printf("%d: starting up\n", (int) pid);
	p = (int *) &main;
	somefunc(4, 9, p);
	return 0;
}

void somefunc(int i, int j, int *p)
{
	deepfunc(i + j, p);
}

void deepfunc(int i, int *p)
{
	*p = i;
}

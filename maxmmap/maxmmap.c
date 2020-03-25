#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    char *addr;
    int fd;
    // not sure whether character devices are meant to be mmap()ed
    char filename[128] = "/dev/zero";
    size_t mapping_size = (size_t)(1024 * 1024 * 8);
    long total = 0;

    if ((fd = open(filename, O_RDONLY)) == -1) {
        int errsv = errno;
        fprintf(stderr, "Fell over opening file %s: %s (%d)\n", filename, strerror(errsv), errsv);
		exit(EXIT_FAILURE);
    }

    printf("We limit virutal memory (in kbytes) with 'ulimit -v <somethign>'\n");
    printf("mmap()ing lengths of %d == %dK == %dM from %s\n",
        mapping_size,
        mapping_size / 1024,
        mapping_size / (1024 * 1024),
        filename);

    // we do not explicitly munmap() because we don't care
    for (int i = 0; i < 666; i++) {
        if (mmap(NULL, mapping_size, PROT_READ, MAP_PRIVATE, fd, 0) == MAP_FAILED) {
            int errsv = errno;
            fprintf(stderr, "mmap() failed: %s (%d)\n", strerror(errsv), errsv);
		    exit(EXIT_FAILURE);
        }
        total += (int)mapping_size;
        printf("%8ldM  [%5d]\n", total / (1024 * 1024), i);
    }

    close(fd);
    return 0;
}

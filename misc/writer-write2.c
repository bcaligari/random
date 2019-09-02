#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME    "/srv/cluster-nfs/tmp/test.txt"
#define INTERVAL    1
#define MAX_LINES   1000
#define MAX_BUF     1024

int main(void)
{
    int i;
    int fd;
    size_t str_len, written;
    ssize_t ws;
    char str_buf[MAX_BUF];

    if ((fd = open(FILENAME, O_WRONLY|O_CREAT|O_TRUNC|O_SYNC, (mode_t) 0666)) == -1) {
        perror("open(2)");
        return 1;
    }
    for (i = 0; i < MAX_LINES; i++) {
        printf("Writing sequence %d\n", i);
        sprintf(str_buf, "%255d\n", i);
        str_len = strlen(str_buf);
        written = 0;
        while (written < str_len) {
            ws = write(fd, str_buf + written, str_len - written);
            if (ws == -1) {
                perror("write(2)");
                break;
            }
            written += ws;
        }
        sleep(INTERVAL);
    }
    close(fd);
    return 0;
}

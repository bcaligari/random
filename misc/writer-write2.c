#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define INTERVAL    1
#define MAX_BUF     1024
#define MAX_LINES   2^16

int main(int argc, char *argv[])
{
    int i;
    int fd;
    ssize_t written, ws;
    size_t str_len;
    char str_buf[MAX_BUF];
    char hostname[MAX_BUF];
    char filepath[MAX_BUF];

    if (argc != 2) {
        printf("Usage %s <filename>\n", argv[0]);
        exit(1);
    }

    printf("Writing to: %s\n", argv[1]);

    if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC|O_SYNC, (mode_t) 0666)) == -1) {
        perror("open(2)");
        return 1;
    }

    for (i = 0; i < MAX_LINES; i++) {
        printf("Writing sequence %d\n", i);
        sprintf(str_buf, "%d\n", i);
        str_len = strlen(str_buf);
        ws = write(fd, str_buf, str_len);
        if (ws == -1) {
           perror("write(2)");
           exit(1);
        }
        if (ws != (ssize_t) str_len)
            printf("Wrote %d instead of %d ... LOL\n", (int) ws, (int) str_len);
        sleep(INTERVAL);
    }
    close(fd);
    return 0;
}

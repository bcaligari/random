#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define FILENAME    "/srv/cluster-nfs/tmp/test.txt"
#define INTERVAL    1
#define MAX_LINES   1000
#define MAX_BUF     1024

int main(void)
{
    int i;
    FILE *f;
    char str_buf[MAX_BUF];

    if ((f = fopen(FILENAME, "w")) == NULL) {
        perror("open");
        return 1;
    }
    for (i = 0; i < MAX_LINES; i++) {
        printf("Writing sequence %d\n", i);
        sprintf(str_buf, "%255d\n", i);
        if (fputs(str_buf, f) == EOF)
            perror("fputs(3)");
        if (fflush(f) == EOF)
            perror("fflush(3)");
        sleep(INTERVAL);
    }
    fclose(f);
    return 0;
}

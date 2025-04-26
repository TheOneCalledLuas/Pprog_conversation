#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
    printf("usleep(1000);\n");
    usleep(1000000);
    printf("nanosleep(1000);\n");
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 100000000000000;
    nanosleep(&ts, NULL);
    printf("sleep(1000);\n");
    sleep(3);

    return 0;
}
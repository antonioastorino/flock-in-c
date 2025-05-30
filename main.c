#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
// #define LOCK_SH 1 /* shared lock */
// #define LOCK_EX 2 /* exclusive lock */
// #define LOCK_NB 4 /* don't block when locking */
// #define LOCK_UN 8 /* unlock */
#define FILE_NAME "tmp.txt"

int main(void)
{
    int pid = fork();
    if (pid)
    {
        int fd = open(FILE_NAME, O_WRONLY | O_CREAT, 0666);
        for (int i = 0; i < 20; i++)
        {
            printf("[PRODUCER] locking with blocking\n");
            flock(fd, LOCK_EX);
            printf("[PRODUCER] \e[31mlocked\e[0m - pretend writing\n");
            sleep(1);
            flock(fd, LOCK_UN);
            printf("[PRODUCER] \e[32munlocked\e[0m\n");
            sleep(1);
        }
    }
    else
    {
        int fd = open(FILE_NAME, O_RDONLY);
        for (int i = 0; i < 20;)
        {
            printf("\t\t[CONSUMER] try locking\n");
            if (flock(fd, LOCK_SH | LOCK_NB) == -1 && errno == EWOULDBLOCK)
            {
                printf("\t\t[CONSUMER] file not ready\n");
                usleep(500000);
            }
            else
            {
                i++;
                printf("\t\t[CONSUMER] \e[31mlocked\e[0m - pretend reading\n");
                sleep(1);
                flock(fd, LOCK_UN);
                printf("\t\t[CONSUMER] \e[32munlocked\e[0m\n");
                usleep(10000);
            }
        }
        wait(NULL);
    }
    return 0;
}

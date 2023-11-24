#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int pid = fork();
    if (pid > 0)
    {
        printf("I am parent process\n");
        printf("PID = %d\n\n", getpid());
    }
    else if (pid == 0)
    {
        printf("I am child process\n");
        printf("PID = %d\n", getpid());
    }
    else
    {
        printf("Failed to create child process");
    }
    return 0;
}
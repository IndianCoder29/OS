#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
int main()
{ 
    int pid=fork(); 
    int new_nice; 
    if(pid==0){ 
        new_nice=nice(-15);
        printf("\nI am child process, PID = %d\n",getpid()); 
        printf("\nChild gets higher priority %d\n",new_nice);
    } 
    else if(pid>0){ 
        new_nice=nice(15); 
        printf("\nI am parent process, PID = %d\n",getpid()); 
        printf("\nParent gets lower priority %d\n",new_nice);
    } 
    return 0;
}

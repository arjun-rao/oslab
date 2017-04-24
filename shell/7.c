#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_COUNT 2


void  ChildProcess(int num)
{
     int   i;
     printf("Child %d Pid: %d\n",num,getpid());         
     printf("*** Child process is done ***\n");
}


int main()
{
    
    printf("Parent Pid: %d\n",getpid());
    pid_t pid;
    int i;

    for(i=0;i<2;i++){
        pid = fork();
        if (pid < 0) 
            exit(0);
        else if (pid == 0)
            ChildProcess(i);
    }

}
/*Using fork() create a child process. The child prints its own process id and parent id and then exits
The parent process waits for its child to finish ( by executing wait() )
and prints its own process id and the id of its child process and then exits*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COUNT 2


void  ChildProcess(void)
{
     int   i;
     printf("Child Pid: %d\nChild's parent: %d\n",getpid(),getppid());    
     for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     printf("   *** Child process is done ***\n");
}

void  ParentProcess(void)
{
     int   i;
     printf("ParentProcess Pid: %d\n",getpid());    
     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     printf("*** Parent is done ***\n");
}

int main()
{
    
    printf("Parent Pid: %d\n",getpid());
    pid_t pid = fork();
    if (pid == 0) 
        ChildProcess();
    else {
        pid = wait(NULL);
        if(pid>0)
        {
            printf("From Parent: Child Pid: %d\n",pid);                
        }
        ParentProcess();
    }

}
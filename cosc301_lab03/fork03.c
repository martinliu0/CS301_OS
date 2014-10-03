#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv)
{
    char *cmd[] = { "/bin/ls", "-ltr", ".", NULL };
    pid_t pid;
    pid = fork();
    if (pid == 0){
        if (execv(cmd[0], cmd) < 0) {
             fprintf(stderr, "execv failed: %s\n", strerror(errno));
        }
    }
    else{
        
        int child;
        if((pid = wait(&child))>-1){  
            printf("This should print to the screen, right?\n");
        }
    }
       

    return 0;
}


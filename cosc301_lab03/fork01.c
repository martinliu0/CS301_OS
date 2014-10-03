#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int s(char *sw){
    return NULL;
}
int main(int argc, char **argv) {    
    char *fuckyou = "023a";
   
    printf("what is fy: %i\n", atoi(fuckyou));
    char *s = "I am a process!";
    int value = 100;

    pid_t pid = fork();
    if (pid == 0) {
        s = "Or am I?";
        value -= 50;
    } else {
        s = "Who are you?";
        value += 50;
    }

    pid_t my_process_id = getpid();
    printf("%s with id %d, and my value is %d\n", s, my_process_id, value);
    return 0;
}

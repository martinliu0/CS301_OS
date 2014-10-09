#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <signal.h>
#include "functs.h"


char **prompt(){
	char str[1024];
	char **temp;
	printf("%s", "prompt> ");
	fgets(str, 1024, stdin);
	replace_pound(str);
	temp = tokenify(str);
/*	int i = 0;
	while(temp[i] != NULL){
		printf("what is command:%s\n", temp[i]);
		i++;
	}*/
	char **tokens = malloc(sizeof(temp));
	tokens = temp;
	return tokens; //free tokens
}


void sequential(char **s){
	int i = 1;
	while(s[i] != NULL)	{
		execv("/bin/ls", s);
		i++;
	}
}	

int main(int argc, char **argv) {
	printf("%s\n","ShellIntelligenti: to exit, type exit");
	char **command {"ls", command};
	execv("/bin/ls", "ls");
	while(1){
		
		command = prompt();
		printf("what is checkpoint1: %s\n", command[0]);
		if (command[0] == NULL){
			printf("NO");
			free(command);
			exit(0);
		}

		int i = strcasecmp(command[0],"s");
		printf("what is checkpoint2: %d\n", i);
		if(strcasecmp(command[0],"s") == 0){
			printf("yes!!!");
			sequential(command);
		}
	
		free(command);
	}
    // a blank slate :-)
    return 0;
}


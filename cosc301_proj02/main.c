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
#include <errno.h>
#include <time.h>
#include "functs.h"


char **prompt(){
	char str[1024];
	char **temp;
	printf("%s", "prompt> ");
	fgets(str, 1024, stdin);
	replace_pound(str);
	temp = tokenify(str, ";");
	return temp; //remember to free tokens
}


int find_mode(char *s){	
	char *copy = strdup(s);
	char **mode = tokenify(copy," \t\n");

	if (strcasecmp(mode[0], "mode") == 0){
		if(strcasecmp(mode[1], "s")==0){
			free(copy);
			free_tokens(mode);
			free(mode);
			return 0; // 0 is sequential mode
		}

		else if(strcasecmp(mode[1], "p")==0){
			free(copy);
			free_tokens(mode);
			free(mode);

			return 1; // 1 is parallel mode
		}

		else{
			free(copy);
			free_tokens(mode);
			free(mode);

			printf("Invalid mode: '%s'\n", s);
			return -1; //-1 is invalid mode input
		}
	}
	free(copy);
	free_tokens(mode);
	free(mode);

	return 2;
}

int find_exit(char **s){
	int i = 0;
	if (s[i] == NULL){
		return -1;
	}

	while(s[i] != NULL){
		char *copy = strdup(s[i]);
		char **copy2 = tokenify(copy, " \n\t");
		if(strcasecmp(copy2[0], "exit") == 0){
			return i; //there is exit command 
		}
		i++;
		free(copy);
		free(copy2);
	}


	return -1; //no exit command

}

int sequential(char **s, int i, int exit_index){ //returns the location the end of command
	int mode = -1;
	while(s[i] != NULL && mode != 1){
		mode = find_mode(s[i]);
		if (mode == 0 || mode == -1 || i == exit_index){
			i++;
			continue;
		}
		char *commands = strdup(s[i]); // might need to free commands
		char **temp = tokenify(commands, " \t\n");
		pid_t pid;
		pid = fork();
		//printf("what is pid: %d\n", pid);
		if (pid == 0){
			if(execv(temp[0], temp)<0){
			//	printf("executing child\n");
				fprintf(stderr, "execv failed: %s\n", strerror(errno));
			}
		}
		else{
			int child;
			if((pid = wait(&child))>-1) {
				i++;
			}
		}
		free(commands);
		free(temp);
	}	
	//printf("what is index: %d\n", i);
	return i;

}
int parallel(char **s, int index){
	printf("Entering parallel mode \n");
	index++;
	return index;
}
int run_command(char **s, int current_mode, int exit_index){
	int i = 0;
	int k = 0;
	//printf("what is mode: %d\n", find_mode(s[1]));
	while(s[i]!=NULL){
		//printf("is is here?\n");
		if(i == exit_index){
			i++;
			continue;
		}
		int mode = find_mode(s[i]);
		if((current_mode == 0 && mode == 2) || mode == 0){
			current_mode = 0;
			i = sequential(s, i, exit_index);
			//printf("what is i: %d\n", i);
			k++;
			if(k>2){
				break;
			}
			
		}
		else if((current_mode == 1 && find_mode(s[i]) == 2) || find_mode(s[i]) == 1){
			current_mode = 1;
			i = parallel(s,i);

		}

	}
	return current_mode;
	
}	


int main(int argc, char **argv) {
	printf("%s\n","ShellIntelligenti: to exit, type exit");
	char **command;
	int *mode_switches;
	int curr_mode = 0; //default mode is sequential

	while(1){
		command = prompt();
		int exit_index = find_exit(command);
		printf("exit index: %d\n", exit_index);
		if (command[0] == NULL){
			printf("Terminating shell .");

/*			time(1);
			printf(".");
			time(2);
			printf(".\n");*/

			free(command);
			exit(0);
		}

		//printf("got here\n");
		curr_mode = run_command(command, curr_mode, exit_index);

		if (exit_index != -1){
			free(command);
			exit(0);
		}
		free(command);

	}
	free(mode_switches);
    // a blank slate :-)
    return 0;
}


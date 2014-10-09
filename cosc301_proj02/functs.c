#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>


char** tokenify(char *s) {
    char *strcopy = strdup(s); 
    char *token = strtok(strcopy, " \n\t;");
    printf("what is the token: %s\n", token);
    int str_arr_size = sizeof(token);
    char *mode = NULL;
    while (token != NULL) {
        token = strtok(NULL, " \n\t;");
       // printf("what is the token: %s\n", token);
        if(token == NULL){
            break;
        }
		if(strcasecmp("mode", token)==0){
			mode = strtok(NULL, " \n\t;");
            //printf("what is mode: %s\n", mode);
		}
        str_arr_size += sizeof(token);
		
    }

    free(strcopy);
    char *another_copy = strdup(s);
    char *another_token = strtok(another_copy, " \n\t;");
    char **strarr = malloc(str_arr_size);
    int count = 1;
	strarr[0] = mode; 

    while (another_token != NULL) {
		if(strcasecmp(another_token, "mode") != 0 && strcasecmp(another_token, "s") != 0 && strcasecmp(another_token, "p") != 0){
			strarr[count] = another_token; //no strdup?
            //printf("another_token: %s\n", another_token);
			another_token = strtok(NULL, " \n\t");
			count++;
		}
        else{
            another_token = strtok(NULL, " \n\t");  
        }
    }
    free(another_copy);
    strarr[count] = NULL;   
    return strarr; 
}


void replace_pound(char *s){
    for (int i = 0; i < strlen(s); i++){
        if (s[i] == '#'){
            s[i] = '\0';
            break;
        }
    }
}


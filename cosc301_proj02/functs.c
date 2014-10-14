#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>


char** tokenify(const char *s, char *delimiter) {
    char *strcopy = strdup(s); 
    char *token = strtok(strcopy, delimiter);
    int str_arr_size = sizeof(token);
    while (token != NULL) {
        token = strtok(NULL, delimiter);
        str_arr_size += sizeof(token);
    }
    free(strcopy);
    char *another_copy = strdup(s);
    char *another_token = strtok(another_copy, delimiter);
    char **strarr = malloc(str_arr_size);
    int count = 0;
    while (another_token != NULL) {
        strarr[count] = strdup(another_token);
        another_token = strtok(NULL, delimiter);
        count++;
    }
    free(another_copy);
    strarr[count] = NULL;   
    return strarr; 
}

void free_tokens(char **tokens){
    int i = 0;
    while(tokens[i] != NULL){
        free(tokens[i]);
    }
}

void replace_pound(char *s){
    for (int i = 0; i < strlen(s); i++){
        if (s[i] == '#'){
            s[i] = '\0';
            break;
        }
    }
}


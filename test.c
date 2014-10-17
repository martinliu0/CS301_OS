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
        i++;
    }
}
//static void test(int p);

int main(void)
{
    //int i = malloc(sizeof(int));
    //i = 0;
    /*int arr[] = {30, 450, 14, 5, 0, 10, '\0'};

    test(arr);
    
    return 0;*/
    //printf("what is i: %d\n", i);
    char *s = " mode p ";
    char *copy = strdup(s);
    char **commands = tokenify(copy, " \n\t");
    free_tokens(commands);
    free(copy);
    return 0;
}

/*static void test(int i)
{
    i = 1;
    int current_mode = 0;
    while(*p) {
        printf("Array values [ %d ]\n", *p++);
    }
    int i = 0;
    int k = 0;
    for (; i < 10; i++){
        k++;
    }
    printf("what is k: %d\n", k);
    char *s[3] = {"what", "the", "fuck"};
    printf("fuck this: %s\n", *(s+1));
    char *c = s+5;
    printf("what is mode: %s\n", c);
    if (strncasecmp(s,"mode",4) == 0){
        printf("hell yea\n");
    }
    int i = 0;
    while(s[i]!=0){
    	printf("string is: %c\n", *s++);
    }
    int j = 0;
    for ( ; j < 10; j++){
    	printf("what is j: %d\n", j);
    }

}*/
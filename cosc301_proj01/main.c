/*
 *
 * Martin Liu, Anindya Guha
 * 9/28/2014
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>

#include "list.h" 

/* 
 * Input: The string to be tokenized. 
 * Output: An array of strings, containing whitespace delimited words 
 * from the string.
 */
char** tokenify(const char *s) {
    char *strcopy = strdup(s); 
    char *token = strtok(strcopy, " \n\t");
    int str_arr_size = sizeof(token);
    while (token != NULL) {
        token = strtok(NULL, " \n\t");
        str_arr_size += sizeof(token);
    }
    free(strcopy);
    char *another_copy = strdup(s);
    char *another_token = strtok(another_copy, " \n\t");
    char **strarr = malloc(str_arr_size);
    int count = 0;
    while (another_token != NULL) {
        strarr[count] = strdup(another_token);
        another_token = strtok(NULL, " \n\t");
        count++;
    }
    free(another_copy);
    strarr[count] = NULL;   
    return strarr; 
}

/* 
 * Frees up the heap space taken up by array of tokens.
*/
void free_tokens(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]); // free each string
        i++;
    }
    free(tokens); // then free the array
}

/* 
 * Checks if the str is a valid int. Returns 0 if false, 1 if true.
 */
int valid_int(char *str){

    if (str == NULL || str[0] == '\0' || (isdigit(str[0]) == 0 && str[0] != '-')) {
        return 0;
    }
    for(int i = 1; i < strlen(str); i++){
        if (isdigit(str[i]) == 0) {
            return 0;
        } 
    }
    return 1;
}

/* 
 * Replaces the '#' sign with a null byte. 
 */
char *replace_pound(char *str) {
    char *newstr = malloc(strlen(str) + 1);
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '#') {
            newstr[j] = str[i];
            j++;
        }
        else {
            str[i] = '\0';
            break;
        }
    }
    newstr[j] = '\0';
    return newstr;
}

void process_data(FILE *input_file) {
    
    Node *head = NULL;
    char line[1024];
    while (fgets(line, 1024, input_file) != NULL) {
        int slen = strlen(line);
        line[slen-1] = '\0';
        char **token_array = tokenify(line);
        int i = 0;
        while (token_array[i] != NULL) {
            if (strcasestr(token_array[i], "#") != NULL) {
                char *str = replace_pound(token_array[i]);
                if (strcasestr(str, ".") == NULL && valid_int(str) != 0) {
                    int data = atoi(str);
                    sorted_insert(data, &head);
                }    
                free(str);
                break;
            }    
            if (strcasestr(token_array[i], ".") != NULL || valid_int(token_array[i]) == 0) {
                i++;
                continue;
            }
            else {
                int data  = atoi(token_array[i]);
                sorted_insert(data, &head);
                i++;
            }
        }
        free_tokens(token_array);
    }
    list_print(head);
    list_clear(head);
    
    /* CPU usage calculation and statistics. */
    struct rusage usg;
    struct timeval usr, sys;

    getrusage(RUSAGE_SELF, &usg);

    usr = usg.ru_utime;
    sys = usg.ru_stime;

    double total_user_time = usr.tv_sec + usr.tv_usec/1000000.0;
    double total_sys_time = sys.tv_sec + sys.tv_usec/1000000.0;

    printf("User time: %f\n", total_user_time);    
    printf("System time: %f\n", total_sys_time);
}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}


#ifndef AUTOTEST
int main(int argc, char **argv) {
    
    FILE *datafile = NULL;
    
    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** tokenify(const char *s) {
    // your code here
    char **buffer = malloc((strlen(s)+1)*sizeof(char*));
    buffer[0] = NULL;
    char *copy1 = strdup(s);
    char *copy2 = strdup(s);
    int count = 0;
    int run = 1;
    int index = 1; 
    char *tokens = malloc((strlen(s)+1)*sizeof(char*));

    tokens = strtok(copy1," \n\t");
    while (run){
        tokens = strtok(NULL," \n\t");
        if (tokens == NULL){
            break;
        }
        count++;
    }
    
    char *temp1 = malloc((count+1)*sizeof(char*));
    temp1 = strtok(copy2, " \n\t");
    if (temp1 == NULL){
        return buffer;
    }
    else{
        buffer[0] = strdup(temp1);
        while(index < count+1){
            temp1 = strtok(NULL, " \n\t");
            buffer[index] = strdup(temp1);
            //printf("word: %s\n", temp1);
            if (temp1 == NULL){
                buffer[index] = NULL;
                return buffer;
            }
            index++;      
       }         
    
    }
    
    return buffer;

}


#ifndef AUTOTEST
void print_tokens(char *tokens[]) {
    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token %d: %s\n", i+1, tokens[i]);
        i++;
    }
}

void free_tokens(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]); // free each string
        i++;
    }
    free(tokens); // then free the array
}

int main() {
    char *fuckyou = "abc";
    printf("what is fy: %i\n", atoi(fuckyou));
    const char *tmp1 = "go red sox";
    char **results = tokenify(tmp1);
    print_tokens(results);
    free_tokens(results);
    const char *tmp2 = " another\nexample\t  to test    with\n";
    results = tokenify(tmp2);
    print_tokens(results);
    free_tokens(results);
    return 0;
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

void removewhitespace(char s[]) {
    // your code here
    char temp[strlen(s)+1];
    int b=0;
    for (int i =0; i < strlen(s); i++){
        if (isspace(s[i]) == 0){
            temp[b] = s[i];
            b++;
        }
    }
    temp[b]='\0';
//    printf("<%s>\n", temp);
    for (int i =0; i <= b; i++){
        s[i] = temp[i];
    }
}


bool c2pascal(char s[]) {
    // your code here

    if (strlen(s) > 127){
        return false;
    }
    else{
        int temp = strlen(s);
        for (int i = strlen(s); i > 0; i--){
            s[i] = s[i-1];
        }
        s[0] = temp;
        return true;
    }

}

void pascal2c(char s[]) {
    // your code here
    int temp = s[0];  
    for (int i = 0; i < temp; i++){
        s[i] = s[i+1];
        
    }
    s[temp] = '\0';
 //   printf("sl: %d", strlen(s));
//    printf("str: %s", s);
}

#ifndef AUTOTEST
int main(int argc, char **argv)
{
    // strdup makes a newly allocated (malloced) copy of a string
    char *orig = strdup("a b c");
 
    /* ********************************** */
    /*    test of whitespace removal      */
    /* ********************************** */
    printf("remove whitespace: before <%s>", orig);
    removewhitespace(orig);
    printf(" and after <%s>\n", orig);
    assert(0==strcmp(orig, "abc"));
    free(orig);
 
    /* ********************************** */
    /*  c to pascal and back to c tests   */
    /* ********************************** */
    const char *s2orig = "ABC";
    char s2[] = "ABC";
    c2pascal(s2);
    assert(s2[0] == '\3');
    for (int i = 0; i < strlen(s2orig); i++) {
        assert(s2[i+1] == s2orig[i]);
    }

    pascal2c(s2);
    printf("converted pascal string back to c.  orig: <%s> reconversion: <%s>\n", s2orig, s2);
    assert(0 == strcmp(s2orig, s2));

    printf("If you got here without crashing, then some very basic tests have passed.\n");
 
    return 0;
}
#endif

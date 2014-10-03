#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>


/*
 * Be happy you didn't have to write this function.
 * Prints a low-tech ASCII gallows.  Max number of misses
 * is 7 (i.e., if there are 7 misses, the player loses and
 * the poor sap gets hung).  
 */
void print_gallows(int num_missed) {
    // make sure that we got called in a reasonable way
    assert(num_missed >= 0 && num_missed <= 7);

    printf("\n\n       |||========|||\n");
    if (num_missed > 0) {
        printf ("       |||         |\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 1) {
        printf ("       |||         O\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 2) {
        if (num_missed > 4) {
            printf ("       |||        /|\\\n");
        } else if (num_missed > 3) {
            printf ("       |||        /| \n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    if (num_missed > 5) {
        if (num_missed > 6) {
            printf ("       |||        / \\\n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    printf ("       |||\n");
    printf ("       |||\n");
    printf ("     =================\n\n");
}

/*
 * Play one game of Hangperson.  The secret word is passed as a
 * parameter.  The function should return true if the player won,
 * and false otherwise.
 */

bool win(const char *word, char s[]){
	for (int i = 0; i < strlen(word); i++){
		if (word[i] != s[i]){
			return false;
		}
	}
	return true;
}	
char getC(){
	char guess[32];
    printf("What is your guess?"); 
	bool go_on = true;
	if (fgets(guess, 32, stdin) == NULL){
		printf("\nOk, terminating program...\n");
		return '+';
	}
	
	while (go_on){ 
		if (isalpha(guess[0]) != 0 && guess[1] == '\n' && guess[2] == '\0'){
			go_on = false;
		}
		else{
			printf("How about a letter.  Seriously.\n");
			printf("What is your guess?");
			fgets(guess, 32, stdin);
		}
		
		
	}
	printf("\n");
    
	//fgets(guess, 1,stdin);
	return tolower(guess[0]);
}
bool good_guess(char c, const char *word, char *p){
    bool idk_what2callitanymore = false;
    for (int i = 0; i < strlen(word); i++){
        if (c == word[i]){
            *(p+i) = c;
            idk_what2callitanymore = true;
        }

    }
    if (idk_what2callitanymore){
        return true;
    }
    return false;
}
int setup_state(char *p, const char *word){
	for (int i = 0; i < strlen(word); i++){
        *(p+i) = '_';
    } 
	*(p+strlen(word)) = '\0';
	return 0;
}
bool already_guessed(char c, char s[]){
    for (int i = 0; i<strlen(s); i++){
        if (c == s[i]){
            printf("You have already guessed '%c'. \n", c);
            return true;
        }
    }
    return false;
}

int curr_state(int i, char c, char s[], bool good_guess){

    printf("Already guess: %s \n", s);
   
    if (!(s[0] == '(') && good_guess){
        printf("Good guess. \n");
    }
    else if (!good_guess) {
        printf("Bad guess. You stink. \n");
    }
    printf("Missed: %i \n", i);
    return 0;
}

bool one_game(const char *word) {
 
    char guess = '_';
    int missed = 0;
	char guessed[32] = "(none)\0";	
	//setup_guessed(gp);
    int trys = 0;
    char state[strlen(word)+1];
    char *p = &state[0];
    setup_state(p,word);
   // char *(*p[strlen(word)]) = &state;
    print_gallows(missed);
    curr_state(0, ' ', guessed,true);
    while (missed < 7 ){
		guess = getC();	
		if (guess == '+'){
			return false;
		}
        while (already_guessed(guess,guessed)){
            guess = getC();
        }
		guessed[trys] = guess;
		guessed[trys+1] = '\0';
		
        if (good_guess(guess, word, p) == true){
            print_gallows(missed);
           	printf("%s \n",state);
            curr_state(missed, guess ,guessed,true);
        }   
        else{
            missed++;
            print_gallows(missed);
            printf("%s \n",state);
            curr_state(missed,guess,guessed,false);
        } 
        trys++;
        if (win(word,state)){
            return true;
        }
    }
	return false;
}


int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = random() / divisor;
    } while (retval > limit);

    return retval;
}

char *rstrip(char *s){
	char *copy = malloc((strlen(s) +1)*sizeof(char));
	for (int i =0; i < strlen(s); i++){
		copy[i] = s[i];
	}
	int i = strlen(copy) -1;
	while (isspace(copy[i])){
		copy[i] = '\0';
		i--;
	}
	return copy;
}
		
char *lower(char *s){
	char *copy = malloc((strlen(s)+1)*sizeof(char));
	for (int i = 0; i < strlen(s); i++){
		copy[i] = tolower(s[i]);
	}
	return copy;
}
#ifndef AUTOTEST
/*
 * The main function is where everything starts.  Choose a random
 * word and call one_game.  Feel free to modify the words array,
 * but don't forget to modify the modulus (currently 4) for choosing 
 *  a random word from the array.
 */
int main() {
    srandom(time(NULL));
   // char *words[] = { "SUMMER", "AUTUMN", "WINTER", "SPRING" };
   	FILE * pFile;
	pFile = fopen("words.txt", "r");
	
	char *words[235886];
	int count =0;
	char str[32];
	char *temp;	
	while(count < 235886 && fgets(str, 32, pFile)){
		temp = rstrip(str);
		words[count] = lower(temp);
		
		count ++;
	}
	fclose(pFile);
	printf("count: %d", count);	
    int word = random() % count;//rand_lim(235886); //% 235886;
    if (one_game(words[word])){
        printf("Ok you won. Who cares.\n");
    }  
    else{
        printf("You lost. The word was: %s \n", words[word]);
    }

	for (int k = 0; k<count; k++){
		free(words[k]);
	}
    return 0;
}
#endif

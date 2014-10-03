#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char name[128];
    struct node *next; 
};

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void list_print_matches(const char *name, const struct node *head) {
    // your code here
	while(head!=NULL){
		if (strcasestr(head->name,name)!=NULL){
			return;
		}
		head= head->next;
	}
    
}

void list_print(const struct node *list) {
    int i = 0;
    printf("In list_print\n");
    while (list != NULL) {
        printf("List item %d: %s\n", i++, list->name);
        list = list->next;
    }
}


int list_delete(const char *name, struct node **head) {
    // your code here
	if (strcasecmp(name, (*head)->name) == 0){
		struct node *temp = *head;
		*head = (*head)->next;
		free(temp);
		return 1;
	}
	else{
		struct node *temp = *head;
		while(temp && strcasecmp(name, (temp->next)->name) != 0){
			temp = temp->next;

		}
		if (strcasecmp(name, (temp->next)->name) == 0){
			struct node *tibet = temp->next;
			temp = tibet->next;
			free(tibet);
			return 1;
		}
		else{
			return 0;
		}

	}


}
	

void list_append(const char *name, struct node **head) {
    // your code here
	struct node *copy_head = malloc(sizeof(struct node)); 
	strcpy(copy_head->name, name);
	struct node *temp = *head;
	if ((*head) == NULL){
		*head = copy_head;
		(*head)->next = NULL;

	} else {
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = copy_head;
		copy_head->next = NULL;

	}


}

void list_reverse(struct node **head) {
    // your code here
	if(*head ==NULL || (*head)->next == NULL){
		return;
	}	
	else if((*head)->next != NULL && ((*head)->next)->next == NULL){
		struct node *temp = (*head)->next;
		(*head)->next = NULL;
		temp->next = *head;
		*head = temp;

	}
	else {
		struct node *n1 = *head;
		struct node *n2 = (*head)->next;
		struct node *n3 = ((*head)->next)->next;
		n1->next = NULL;
		while(n3!= NULL){
			n2->next = n1;
			n1 = n2;
			n2 = n3;
			n3 = n3->next;
		}
		n2->next = n1;
		*head = n2;	
	}
		 	
}



void list_sort(struct node **head) {
    // your code here

	struct node *phead1 = *head;
	struct node *phead2 = phead1->next;
    struct node *phead3 = phead1;
	struct node *temp2 = phead1;
	struct node *temp = NULL;
	printf("fuck1");
	while(1){
		printf("fuck1");
		while(phead1 && phead2){
			printf("fuck2");
			if (strcasecmp(phead1->name, phead2->name) < 0){
				phead1 = phead2;
			}
            
			phead2 = phead2->next;
            phead3 = phead3->next;
		}
		printf("fuck3");
		if (strcasecmp(phead1->name, temp2->name)==0){
    		temp2 = temp2->next;
	    	phead1->next = temp;
	    	temp = phead1;
			printf("fuck4");
		}

		else{

            phead3->next = phead1->next;
            phead1->next = temp;
            temp = phead1;
            printf("fuck5");
		}

        phead1 = temp2;
		phead2 = phead1->next;
        if(phead1->next == NULL){
        	printf("fuck6");
            phead1->next = temp;
            temp = phead1;
            break;
        }
	
	}

	*head = temp;
}


#ifndef AUTOTEST
int main(int argc, char **argv) {
    char buffer[128];

    struct node *head = NULL;
    printf("Next string to add: \n");
    fflush(stdout);
    while (fgets(buffer, 128, stdin) != NULL) {
        // fgets includes the newline character at
        // the end of a string as the last character.
        // let's squash it.
        int slen = strlen(buffer);
        buffer[slen-1] = '\0';

        list_append(buffer, &head);
		printf("buffer: %s\n", head->name);
        printf("Adding %s\n", buffer);

        printf("Next string to add (or ctrl+d to exit): ");
        fflush(stdout);
    }

    printf("\nHere is the list before sorting:\n");
    list_print(head);

    printf("\nAnd here is the list after sorting:\n");
    list_sort(&head);
    list_print(head);

    printf("\nAnd here is the list after reversing:\n");
    list_reverse(&head);
    list_print(head);

    printf("Printing matches for the string \"a\"\n");
    list_print_matches("a", head);

    if (head) {
        printf("Now we'll delete the first element\n");
        list_delete(head->name, &head);
        list_print(head);
    }

    list_clear(head);

    return 0;
}
#endif

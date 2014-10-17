#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* your list function definitions */

void list_print(const Node *list) {
    printf("*** List contents begin *** \n");
    while (list != NULL) {
        printf("%d\n", list->data);
        list = list->next;
    }
    printf("*** List contents end *** \n");
}

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void sorted_insert(int data, Node **head) {
    if ((*head) == NULL) {
        Node *newnode = malloc(sizeof(Node));
        newnode->data = data;
        newnode->next = NULL;
        *head = newnode; 
    }
    else if ((*head)->data >= data) {
        Node *newnode = malloc(sizeof(Node));
        newnode->data = data;
        newnode->next = *head;
        *head = newnode;
    }
    else {
        Node *curr = *head;
        while (curr->next != NULL) {
            if ((curr->next)->data >= data) {
                Node *newnode = malloc(sizeof(Node));
                newnode->data = data;
                Node *tmp = curr->next;
                curr->next = newnode;
                newnode->next = tmp;
                return;
            }  
            curr = curr->next;
        }
        Node *newnode = malloc(sizeof(Node));
        newnode->next = NULL;
        newnode->data = data;
        curr->next = newnode;
    }


}

void insert(int data, Node **head){
    if ((*head) == NULL) {
        Node *newnode = malloc(sizeof(Node));
        newnode->data = data;
        newnode->next = NULL;
        *head = newnode; 
    }
    else{
        Node *curr = *head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        Node *newnode = malloc(sizeof(Node));
        newnode->next = NULL;
        newnode->data = data;
        curr->next = newnode;

    }
}




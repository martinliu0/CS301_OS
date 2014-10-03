#ifndef __LIST_H__
#define __LIST_H__

/* your list data structure declarations */

typedef struct node {
    int data; 
    struct node *next;
} Node;

/* your function declarations associated with the list */
void list_print(const Node *list);
void sorted_insert(int data, Node **head);
void list_clear(Node *list);

#endif // __LIST_H__

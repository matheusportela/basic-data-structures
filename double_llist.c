/**
 * Implementation of doubly linked list, following the approach explained at
 * Introduction to Algorithms - Cormen et. al (Chapter 10), for didactic
 * purposes.
 *
 * Author: Matheus V. Portela (matheus.v.portela@gmail.com)
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * Linked list structure, holding its head.
 */
struct llist {
    struct llist_element* head;
};

/*
 * Linked list element, holding satellite data and pointers to other elements.
 */
struct llist_element {
    char data;
    struct llist_element* prev;
    struct llist_element* next;
};

/*
 * Create linked list.
 */
struct llist* create_list();

/*
 * Delete linked list and its elements.
 */
void delete_list(struct llist* list);

/*
 * Print linked list elements.
 */
void print_list(struct llist* list);

/*
 * Create linked list element.
 */
struct llist_element* create_element(char data);

/*
 * Delete linked list element.
 */
void delete_element(struct llist* list, struct llist_element* element);

/*
 * Insert linked list element to the beginning of the list.
 */
void insert_element(struct llist* list, struct llist_element* element);

/*
 * Search for a linked list element in linear time (O(n)).
 */
struct llist_element* search_element(struct llist* list, char data);

/*
 * Print linked list element.
 */
void print_element(struct llist_element* element);

int main() {
    printf("Creating list\n");
    struct llist* list = create_list();

    printf("\nInserting three elements to the list\n");
    insert_element(list, create_element('a'));
    insert_element(list, create_element('b'));
    insert_element(list, create_element('c'));
    print_list(list);

    printf("\nSearching for element \"b\"\n");
    print_element(search_element(list, 'b'));

    printf("\nSearching for element \"d\", which is not in the list\n");
    print_element(search_element(list, 'd'));

    printf("\nDeleting element \"b\"\n");
    delete_element(list, search_element(list, 'b'));
    print_list(list);

    printf("\nDeleting list\n");
    delete_list(list);

    return 0;
}

struct llist* create_list() {
    struct llist* list = malloc(sizeof(struct llist));
    list->head = NULL;
    return list;
}

void delete_list(struct llist* list) {
    struct llist_element* element = list->head;
    struct llist_element* next = element;

    while (next != NULL) {
        next = element->next;
        free(element);
        element = next;
    }

    free(list);
}

void print_list(struct llist* list) {
    struct llist_element* element = list->head;

    printf("List: ");

    while (element != NULL) {
        printf("%c ", element->data);
        element = element->next;
    }
    printf("\n");
}

struct llist_element* create_element(char data) {
    struct llist_element* element = malloc(sizeof(struct llist_element));
    element->data = data;
    element->prev = NULL;
    element->next = NULL;
    return element;
}

void delete_element(struct llist* list, struct llist_element* element) {
    /* If the element doesn't have prev, it must be the beginning of the list */
    if (element->prev)
        element->prev->next = element->next;
    else
        list->head = element->next;

    if (element->next)
        element->next->prev = element->prev;

    free(element);
}

void insert_element(struct llist* list, struct llist_element* element) {
    element->prev = NULL;
    element->next = list->head;

    if (list->head != NULL)
        list->head->prev = element;

    list->head = element;
}

struct llist_element* search_element(struct llist* list, char data) {
    struct llist_element* element = list->head;

    while (element != NULL && element->data != data)
        element = element->next;

    return element;
}

void print_element(struct llist_element* element) {
    printf("Element: ");

    if (element != NULL)
        printf("%c\n", element->data);
    else
        printf("nil\n");
}

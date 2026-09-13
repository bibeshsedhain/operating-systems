// list/list.c
//
// Implementation for linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


list_t *list_alloc()
{
    list_t *mylist = malloc(sizeof(list_t));

    if (mylist == NULL)
        return NULL;

    mylist->head = NULL;

    return mylist;
}


/*
 * Free every node first, then free the list itself.
 */
void list_free(list_t *l)
{
    if (l == NULL)
        return;

    node_t *curr = l->head;

    while (curr != NULL)
    {
        node_t *next = curr->next;

        free(curr);

        curr = next;
    }

    free(l);
}


/*
 * Print the linked list.
 *
 * Example:
 * 10->20->30->NULL
 */
void list_print(list_t *l)
{
    if (l == NULL)
    {
        printf("NULL\n");
        return;
    }

    node_t *curr = l->head;

    while (curr != NULL)
    {
        printf("%d->", curr->value);
        curr = curr->next;
    }

    printf("NULL\n");
}


/*
 * Convert the linked list to a string.
 *
 * Caller is responsible for freeing returned string.
 */
char *listToString(list_t *l)
{
    char *buf = malloc(sizeof(char) * 10024);

    if (buf == NULL)
        return NULL;

    /*
     * Important:
     * strcat requires buf to initially contain a valid
     * empty string.
     */
    buf[0] = '\0';

    char tbuf[20];

    if (l != NULL)
    {
        node_t *curr = l->head;

        while (curr != NULL)
        {
            sprintf(tbuf, "%d->", curr->value);
            strcat(buf, tbuf);

            curr = curr->next;
        }
    }

    strcat(buf, "NULL");

    return buf;
}


/*
 * Create one node on the heap.
 */
node_t *getNode(elem value)
{
    node_t *mynode = malloc(sizeof(node_t));

    if (mynode == NULL)
        return NULL;

    mynode->value = value;
    mynode->next = NULL;

    return mynode;
}


/*
 * Return number of nodes.
 */
int list_length(list_t *l)
{
    if (l == NULL)
        return 0;

    int count = 0;

    node_t *curr = l->head;

    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }

    return count;
}


/*
 * Add element to end of list.
 */
void list_add_to_back(list_t *l, elem value)
{
    if (l == NULL)
        return;

    node_t *new_node = getNode(value);

    if (new_node == NULL)
        return;

    /*
     * Empty list.
     */
    if (l->head == NULL)
    {
        l->head = new_node;
        return;
    }

    node_t *curr = l->head;

    /*
     * Find last node.
     */
    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    curr->next = new_node;
}


/*
 * Add element to beginning.
 */
void list_add_to_front(list_t *l, elem value)
{
    if (l == NULL)
        return;

    node_t *cur_node = getNode(value);

    if (cur_node == NULL)
        return;

    cur_node->next = l->head;
    l->head = cur_node;
}


/*
 * Insert at a 1-based index.
 *
 * Example:
 *
 * 10 -> 20 -> 30
 *
 * add_at_index(list, 99, 2)
 *
 * 10 -> 99 -> 20 -> 30
 */
void list_add_at_index(list_t *l, elem value, int index)
{
    if (l == NULL || index < 1)
        return;

    /*
     * Inserting at first position.
     */
    if (index == 1)
    {
        list_add_to_front(l, value);
        return;
    }

    node_t *curr = l->head;

    /*
     * Move to node immediately BEFORE insertion point.
     */
    for (int i = 1; i < index - 1 && curr != NULL; i++)
    {
        curr = curr->next;
    }

    /*
     * Index was too large.
     */
    if (curr == NULL)
        return;

    node_t *new_node = getNode(value);

    if (new_node == NULL)
        return;

    new_node->next = curr->next;
    curr->next = new_node;
}


/*
 * Remove last element.
 */
elem list_remove_from_back(list_t *l)
{
    if (l == NULL || l->head == NULL)
        return -1;

    /*
     * Only one node.
     */
    if (l->head->next == NULL)
    {
        elem value = l->head->value;

        free(l->head);

        l->head = NULL;

        return value;
    }

    node_t *curr = l->head;

    /*
     * Stop at second-to-last node.
     */
    while (curr->next->next != NULL)
    {
        curr = curr->next;
    }

    node_t *last = curr->next;

    elem value = last->value;

    curr->next = NULL;

    free(last);

    return value;
}


/*
 * Remove first node.
 */
elem list_remove_from_front(list_t *l)
{
    if (l == NULL || l->head == NULL)
        return -1;

    node_t *old_head = l->head;

    elem value = old_head->value;

    l->head = old_head->next;

    free(old_head);

    return value;
}


/*
 * Remove node at 1-based index.
 */
elem list_remove_at_index(list_t *l, int index)
{
    if (l == NULL || l->head == NULL || index < 1)
        return -1;

    if (index == 1)
    {
        return list_remove_from_front(l);
    }

    node_t *curr = l->head;

    /*
     * Move to node immediately BEFORE the node
     * being deleted.
     */
    for (int i = 1; i < index - 1 && curr != NULL; i++)
    {
        curr = curr->next;
    }

    /*
     * Invalid index.
     */
    if (curr == NULL || curr->next == NULL)
        return -1;

    node_t *removed = curr->next;

    elem value = removed->value;

    curr->next = removed->next;

    free(removed);

    return value;
}


/*
 * Search for value.
 */
bool list_is_in(list_t *l, elem value)
{
    if (l == NULL)
        return false;

    node_t *curr = l->head;

    while (curr != NULL)
    {
        if (curr->value == value)
            return true;

        curr = curr->next;
    }

    return false;
}


/*
 * Return element at a 1-based index.
 */
elem list_get_elem_at(list_t *l, int index)
{
    if (l == NULL || index < 1)
        return -1;

    node_t *curr = l->head;

    int current_index = 1;

    while (curr != NULL)
    {
        if (current_index == index)
            return curr->value;

        curr = curr->next;
        current_index++;
    }

    return -1;
}


/*
 * Return first index where value occurs.
 *
 * Indexing begins at 1.
 */
int list_get_index_of(list_t *l, elem value)
{
    if (l == NULL)
        return -1;

    node_t *curr = l->head;

    int index = 1;

    while (curr != NULL)
    {
        if (curr->value == value)
            return index;

        curr = curr->next;
        index++;
    }

    return -1;
}
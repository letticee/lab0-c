/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    if (q == NULL) {
        return;
    }
    while (q->head != NULL) {
        list_ele_t *ele = q->head;
        q->head = ele->next;
        free(ele->value);
        free(ele);
    }

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }

    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL) {
        return false;
    }

    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    /*
        (newh->value) = strdup(s);
        if ((newh->value) == NULL) {
            free(newh);
            return false;
        }
    */
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL) {
        q->tail = newh;
    }
    q->size = q->size + 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;

    if (q == NULL) {
        return false;
    }
    newt = malloc(sizeof(list_ele_t));

    if (newt == NULL) {
        return false;
    }

    newt->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);

    newt->next = NULL;
    q->tail->next = newt;
    q->tail = newt;
    if (q->head == NULL) {
        q->head = newt;
    }
    q->size = q->size + 1;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if ((q == NULL) || (q->head == NULL)) {
        return false;
    }
    if (sp != NULL) {
        // sp = malloc(bufsize);
        // strncpy((q->head)->value, sp, bufsize - 1);
        // memcpy(sp, (q->head)->value, bufsize);
        memset(sp, '\0', bufsize);
        strncpy(sp, (q->head)->value, bufsize - 1);
    }

    list_ele_t *oldh = q->head;
    q->head = q->head->next;
    free(oldh->value);
    free(oldh);
    q->size = q->size - 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if ((q == NULL) || (q->head == NULL)) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if ((q == NULL) || (q->head == NULL)) {
        return;
    }

    list_ele_t *pre = NULL;
    list_ele_t *itr = q->head;
    list_ele_t *post = itr->next;
    q->tail = q->head;
    while (post != NULL) {
        itr->next = pre;

        pre = itr;
        itr = post;
        post = post->next;
    }
    itr->next = pre;
    q->head = itr;

}

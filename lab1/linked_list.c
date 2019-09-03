#include <limits.h>
#include "linked_list.h"

node *linked_list_init(){
    node *head = (node*)malloc(sizeof(node));
    head->count = 0;
    head->next = NULL;
    return head;
}

void linked_list_free(node *head){
    node *cur = head;
    node *last;
    while(cur != NULL){
        last = cur;
        cur = cur->next;
        free(last);
    }
}

// FIXME: buffer overflow!
char linked_list_string[0x10000];

char *linked_list_tostring(node *head){
    node *cur = head->next;
    char *position;
    int length = 0;
    while(cur != NULL){
        position = linked_list_string + length;
        length += sprintf(position, "%d", cur->value);
        cur = cur->next;
        if(cur != NULL){
            position = linked_list_string + length;
            length += sprintf(position, "->");
        }
    }
    position = linked_list_string + length;
    length += sprintf(position, "%c", '\0');
    return linked_list_string;
}

int linked_list_size(node *head){
    return head->count;
}

void linked_list_append(node *head, int val){
    node *cur = head;
    node *new_node;
    while(cur->next != NULL){
        cur = cur->next;
    }
    new_node = (node*)malloc(sizeof(node));
    new_node->value = val;
    new_node->next = NULL;
    cur->next = new_node;
    head->count++;
}

/* your implementation goes here */

/* insert val at position index */
void linked_list_insert(node *head, int val, int index) {
    // do nothing if index is out of bound
    if (index > head->count || index < 0)
        return;  // check if is tail?
    // move to index
    node *cur = head;
    for (int i = 0; i < index; ++i) {
        cur = cur->next;
    }
    // insert a new node
    node *new_node = (node*)malloc(sizeof(node));
    new_node->value = val;
    new_node->next = cur->next;
    cur->next = new_node;
    head->count++;
}

/* delete node at position index */
void linked_list_delete(node *head, int index) {
    // do nothing if index is out of bound
    if (index >= head->count || index < 0)
        return;
    // move to index
    node *cur = head;
    for (int i = 0; i < index; ++i) {
        cur = cur->next;
    }
    // delete
    node *old = cur->next;
    cur->next = old->next;
    free(old);
    head->count--;
}

/* remove the first occurrences node of val */
void linked_list_remove(node *head, int val) {
    // find
    node *cur = head;
    while (cur->next != NULL && cur->next->value != val) {
        cur = cur->next;
    }
    // return if not found
    if (cur->next == NULL)
        return;
    // delete found node
    node *old = cur->next;
    cur->next = old->next;
    free(old);
    head->count--;
}

/* remove all occurrence of val */
void linked_list_remove_all(node *head, int val) {
    node *cur = head;
    while (cur->next != NULL) {
        if (cur->next->value == val) {
            node *old = cur->next;
            cur->next = old->next;
            free(old);
            head->count--;
        } else {
            cur = cur->next;
        }
    }
}

/* get value at position index */
int linked_list_get(node *head, int index) {
    // do nothing if out of bound
    if (index >= head->count || index < 0)
        return INT_MIN;
    // search
    node *cur = head->next;
    for (int i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur->value;
}

/* search the first index of val */
int linked_list_search(node *head, int val) {
    node *cur = head;
    int index;
    for (index = 0; cur->next != NULL && cur->next->value != val; ++index) {
        cur = cur->next;
    }
    if (cur->next == NULL)  // not found
        return -1;
    return index;
}

/* search all indexes of val */
node *linked_list_search_all(node *head, int val) {
    node *indexes = linked_list_init();
    node *tail = indexes;
    int idx = 0;
    for (node *cur = head->next; cur != NULL; cur = cur->next, ++idx) {
        if (cur->value == val) {
            // append index at the tail
            tail->next = (node*)malloc(sizeof(node));
            tail = tail->next;
            tail->value = idx;
            indexes->count++;
        }
    }
    tail->next = NULL;
    return indexes;
}

#include "list.h"
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

struct entry {
    struct entry *next;
    void *data;
};

struct list {
    struct entry *entries;
    struct entry *end;
    size_t length;
};

struct list *list_create()
{
    struct list *ls = malloc(sizeof(struct list));
    ls->entries = malloc(sizeof(struct entry));
    ls->end = ls->entries;
    ls->length = 0;
    return ls;
}

void list_destroy(struct list *ls)
{
    struct entry *tmp;
    while((tmp = ls->entries)) {
        printf("destroi %p\n", tmp);
        ls->entries = ls->entries->next;
        free(tmp);
    }
    free(ls);
}

void list_push(struct list *ls, void *data)
{
    assert(ls);
    
    struct entry *item = malloc(sizeof(struct entry));
    item->data = data;
    item->next = NULL;
    
    ls->end->next = item;
    ls->end = item;
    ls->length++;
}

void list_push_front(struct list *ls, void *data)
{
    assert(ls);
    printf("entrou\n"); 
    struct entry *item = malloc(sizeof(struct entry));
    item->data = data;
    item->next = ls->entries->next;
    ls->entries->next = item;
    ls->length++;
}

struct list_iterator *list_get_iterator(struct list *ls)
{
    struct list_iterator *it = malloc(sizeof(struct list_iterator));
    it->target = ls->entries->next;
    return it;
}

void *list_next(struct list_iterator *it)
{
    assert(it);
    if(!it->target) return NULL;
    void *data = it->target->data;
    it->target = it->target->next;
    return data;
}

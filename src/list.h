#ifndef _LIST_H_
#define _LIST_H_

typedef struct entry entry_t;
typedef struct list_iterator list_iterator_t;
typedef struct list list_t;

struct entry;
struct list;
struct list_iterator {
    struct entry *target;
};

struct list *list_create();
void list_destroy(struct list *ls);
void list_push(struct list *ls, void *data);
void list_push_front(struct list *ls, void *data);
struct list_iterator *list_get_iterator(struct list *ls);
void *list_next(struct list_iterator *it);

#endif

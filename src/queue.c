#include "queue.h"

typedef struct _node{
    u32 index;
    u32 color;
    struct _node *next;
}* node;

struct _queue{
    node first;
    node last;
    char *cache;
    u32 length;
};

// Retorna el puntero a queue si todo sale bien.
// Si el alloc sale mal, devuelve NULL.
queue queue_init(u32 max_size){
    queue q = calloc(1,sizeof(struct _queue));
    if (q != NULL){
        q->cache = calloc(max_size,sizeof(char));
        q->first = NULL;
        q->last = NULL;
        q->length = 0;
    }

    return q;
}

queue queue_destroy(queue q){
    if (q != NULL){
        node to_free = q->first;
        node next_node;

        while (to_free != NULL){
            next_node = to_free->next;
            free(to_free);
            to_free = next_node;
        }

        free(q->cache);
        free(q);
    }
    return NULL;
}

// S
queue queue_add(u32 index, u32 color, queue q){
    node n = calloc(1,sizeof(struct _node));
    if (n != NULL){
        n->index = index;
        n->color = color;
        n->next = NULL;

        q->cache[index] = 1;

        if (q->length == 0){
            q->first = n;
        } else {
            q->last->next = n;
        }

        q->last = n;
        q->length ++;

        return q;
    } else {
        queue_destroy(q);
        return NULL;
    }
}

u32 queue_get_index(queue q){
    return q->first->index;
}

u32 queue_get_color(queue q){
    return q->first->color;
}

void queue_remove(queue q){
    node n = q->first;

    q->cache[queue_get_index(q)] = 0;
    q->first = q->first->next;
    if (q->length == 1){
        q->last = NULL;
    }
    q->length --;

    free(n);
}

u32 queue_length(queue q){
    return q->length;
}

char queue_in(u32 v, queue q){
    char ret = 0;

    if (q->cache[v] == 1){
        ret = 1;
    }

    return ret;
}

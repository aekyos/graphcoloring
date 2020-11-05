#ifndef _QUEUE
#define _QUEUE

#include "../veinteveinte.h"

typedef struct _queue *queue;

/*instantiate an empty queue*/
queue queue_init();
/*destroy a queue*/
queue queue_destroy(queue q);
/*add (i)th index, (c)olor element*/
queue queue_add(u32 i, u32 c, queue q);
/*pops first element from queue*/
void queue_remove(queue q);
/*returns color of first element*/
u32 queue_get_color(queue q);
/*returns index of first element*/
u32 queue_get_index(queue q);
/*self explanatory*/
u32 queue_length(queue q);
/*checks if v is in queue*/
char queue_in(u32 v, queue q);

#endif

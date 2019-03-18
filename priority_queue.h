#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include "priority_queue_types.h"



// initialize min/max queue of size 'size',
// use values close to working set to avoid resizes
// returns queue struct
p_queue * init_queue( size_t size, enum Order order); 

// insert (priority, ptr to object) to queue
// returns queue struct
p_queue * insert(p_queue * queue, tuple * item); 

// remove tuple of highest/lowest priority from queue and
// return it
tuple * pop(p_queue * queue);

// get tuple of highest/lowest priority from queue
// without removing it
tuple * peek(p_queue * queue);

// set queue ordering (max/min)
// returns queue struct
p_queue * set_order(p_queue * q, enum Order order);

// self explanatory for valid queues
// returns -1 if provided with a null queue
int is_empty(p_queue * q);



// clear list
// behavior = PURE: free memory of contents and free queue struct
// behavior = OVERWRITE: zero contents and reset struct
// returns 0 for success, -1 for failure
int queue_clear(p_queue * q, enum DEEPCLEAR behavior);





//helper functions

void swap(tuple *a, tuple *b)
{
    tuple temp;
    if (a && b) // if null, nothing to do
    {
        temp = *a;
        *a = *b;
        *b = temp;
    }
}

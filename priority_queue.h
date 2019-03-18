#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

// queue consists of tuples of double priorities
// and pointers to items
// type should be handled by explicit user casting

typedef struct{
    double priority;
    void * item;
} tuple;

enum Order {MAX = 1, MIN = 0};
enum DeepClear {PURGE,OVERWRITE};

// actual queue
typedef struct{
    int count; // items contained
    size_t curr_size; //current size
    tuple * data; // contents
    enum Order order; // 1- max queue, 0 min_queue
} p_queue;


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
p_queue * setOrder(p_queue * q, enum Order order);

// self explanatory for valid queues
// returns -1 if provided with a null queue
int isEmpty(p_queue * q);



// clear list
// behavior = PURE: free memory of contents and free queue struct
// behavior = OVERWRITE: zero contents and reset struct
// returns 0 for success, -1 for failure
int queue_clear(p_queue * q, enum DeepClear behavior);





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

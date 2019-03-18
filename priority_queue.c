#include "priority_queue.h"
#include <string.h>

/* implementation notes 
-- Queue is 1-indexed for easier index calculation */

void queue_debug(p_queue * queue)
{
    tuple j;
    if (queue)
    {
        for (int i=1;i <= queue->count; i++)
        {
           j = queue->data[i]; 
           printf("item #%d priority: %f \n",i,j.priority);
        }
        return;
    }

    printf("Invalid header");
}

p_queue * set_order(p_queue * q, enum Order order)
{
    // set min or max queue
    if (q)
    {
        q->order = order;
        return q;
    }
    else
    {
        return NULL;
    }
}

p_queue * init_queue( size_t size, enum Order order)
{
    // allocation function
    // Should be called with size approximate to working set
    // to avoid resizes
    p_queue * q;
    
    // allocate memory
    q = calloc(size + 1,sizeof(*q));
    

    //failed to allocate
    if (q == NULL)
    {
        // errno will be set
        return NULL;
    }

    q->count = 0;
    q->curr_size = size;
    q->order = order;

    //allocate mem
    q->data = (tuple *)malloc((size+1) * sizeof(tuple));
    if (!q)
    {
        // out of memory
        return NULL;
    }
   
    //  valid queue     
    return q; 
    
}

p_queue * push(p_queue * queue, tuple * item)
{
    tuple * temp;
    // invalid queue
    if (!queue)
    {
        // Null queue pointer
        return NULL; // insert error
    }


    // not enough space allocated
    if (queue->count > queue->curr_size - 1)
    {
        printf("No space");
        // zero size queue
        if (queue->curr_size == 0)
        {
            queue->data =(tuple *)malloc(5 * sizeof(tuple));
            if (queue->data)
            {
                queue->curr_size = 5;
            }  
            else
                return NULL; // out of memory
        }
        else 
        {
            // reallocate memory, doubling allocated space
            temp = (tuple *)realloc(queue->data, ((queue->curr_size << 1) + 1) * sizeof(tuple));
            if (temp)
            {
                queue->data = temp;
                queue->curr_size <<= 1;
            }
                    
            else
                return NULL; // out of memory
        }
    }

    // add new item to end of heap
    queue->count++;
    queue->data[queue->count] = *item;
    

    // sift up

    /* parent(n)
     /       \
  child(2n)      child2 (2n + 1) */

    
    int child = queue->count; // child node
    int parent = child >> 1;  // parent
    int should_swap = 0;

    for (; parent >= 1; parent >>= 1)
    {
        should_swap = (queue->order == MIN && queue->data[child].priority < queue->data[parent].priority) || // min queue
                        (queue->order == MAX && queue->data[child].priority >  queue->data[parent].priority) ; // max queue
        
        if (should_swap)
        {
            swap(&queue->data[child], &queue->data[parent]);
        }
        else
        {
            break;
        }
        

        child = parent;
    
    }

    return queue; // insert OK, non NULL pointer
     
}

int is_empty(p_queue * q)
{
    // return -1 for null queue
    return q ? q->count == 0: -1;
}

tuple * peek(p_queue * queue)
{
    // returns tuple of (data, priority) from the root of 
    // the heap

     // invalid queue
    if (!queue)
    {
        // null queue
        return NULL; // insert error
    }

    if (queue->count > 0)
        return queue->data + 1;
    else
    {
        // return null if no item inserted in heap
        return NULL;
    }
        
}

tuple * pop(p_queue * queue)
{
    tuple * tup; // return value
    if (!queue)
    {
        //Null queue pointer
        return NULL;
    }
    

    if (queue->count != 0)
    {
        // root of heap
        tup = malloc(sizeof(tuple));
        *tup = queue->data[1];
    }
    else // empty heap
    {
        return NULL;
    }

    // copy last item to root and reduce heap size
    queue->data[1] = queue->data[queue->count];
    queue->count--;

    // sift down

    int parent = 1;
    int left_child, right_child, child;

    while(parent <= queue->count)
    {
        // check node children
        left_child = parent << 1;
        right_child = left_child + 1;

        if (left_child > queue->count) // node has no children (no left child)
        {
            return tup; // pop OK!
        }
        else if (right_child <= queue->count ) // both children available 
        {
            // choose child tuple with less or more priority
            if (queue->order == MIN) // min queue
            {
                child = queue->data[left_child].priority < queue->data[right_child].priority ? left_child: right_child;
            }
            else
                child = queue->data[left_child].priority > queue->data[right_child].priority ? left_child: right_child;      
        }
        else
        {
            // only left child exists
            child = left_child;  
        }

        if (queue->order == MIN) // min queue
            {
                
                if (queue->data[child].priority < queue->data[parent].priority)
                    {
                        swap(&queue->data[child],&queue->data[parent]);
                    }
                else
                    {
                        break;
                    }
            }
            else
                if (queue->data[child].priority > queue->data[parent].priority)
                    swap(&queue->data[child],&queue->data[parent]);
                else
                {
                    break;
                }
        

        parent = child;
        
    }

    return tup; // heap fixed

}

int queue_clear(p_queue * q, enum DEEPCLEAR behavior)
{
    /* PURGE will free all the memory and erase the queue
    OVERWRITE zeroes contents and resets the structure
    keeping its previous size 
    
    Returns 0 on success and -1 on failure
    */


    if (q)  //null queue
    {
       
            switch (behavior)
            {
                case PURGE:
                    if (q->data) //if null contents nothing to do
                    { 
                        free(q->data);
                    }

                    free(q); // delete structure

                    return 0; // whole queue freed 
                case OVERWRITE: // only queue contents
                    q->count = 0;
                    memset(q->data, '\0', q->curr_size * sizeof(tuple)); // zero everything
                    return 0;
                default:
                    return -1; // shouldn't happen
            }
           
    }
    else
    {
        return -1;
    }
        
}

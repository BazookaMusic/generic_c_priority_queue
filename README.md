#### Generic C priority queue

This is an implementation of a simple generic priority queue in pure C ,using a binary heap. I made it because heaps are useful
and to freshen up my knowledge of C. 

Usage:

Data is encapsulated in a tuple struct:
```
typedef struct{
    double priority;
    void * item;
} tuple;

```

The priority field is used to order the data. Data is included as a pointer and should be casted to their proper type 
when retrieved.

Example data:
```
typedef struct hello
{
    int a;
    int b;
    int c[10000];
} hello;
```

Example:
```
 p_queue * queue; // queue struct
 tuple * tup; // struct which will contain our data
 
hello * a; // pointer to data



queue = init_queue(1000,MAX); // initialize queue at a size of 1000 and using a max heap
                              // items returned in descending order
                              
                              
for(size_t i = 0; i < 1000; i++)
{
    a = malloc(sizeof(hello)); //make data
    a->a = i;
    a->b = i+1;
    
    //put data in tuple
    tup = malloc(sizeof(tuple)); 
    tup->item = a;
    tup->priority = a->a * a->b;
    

    // put data in queue
    push(queue,tup);
}

for(size_t i = 0; i < 1000; i++)
{
    //get data 
    tup = pop(queue);

    // cast into proper type
    a = (hello *)(tup->item);
    
    // hooray, queue returns in proper order
    printf("%d %d : %f \n",a->a, a->b ,tup->priority);

}
```

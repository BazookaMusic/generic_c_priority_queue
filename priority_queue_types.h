// queue consists of tuples of double priorities
// and pointers to items
// type should be handled by explicit user casting

typedef struct{
    double priority;
    void * item;
} tuple;

enum Order {MAX = 1, MIN = 0};
enum DEEPCLEAR {PURGE,OVERWRITE};

// actual queue
typedef struct{
    int count; // items contained
    size_t curr_size; //current size
    tuple * data; // contents
    enum Order order; // 1- max queue, 0 min_queue
} p_queue;

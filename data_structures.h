typedef struct TAG_VERTEX
{
    int index;
    char color;
    double disc;
    int pi;
    int position;
} VERTEX;
typedef VERTEX ELEMENT;
typedef ELEMENT *PELEMENT;

typedef struct TAG_EDGE
{
    int index;
    int start_edge;
    int end_edge;
    double weight;
    TAG_EDGE *next;
} EDGE;
typedef EDGE *PEDGE;

typedef struct TAG_HEAP
{
    int capacity;
    int size;
    PELEMENT *H;
} HEAP;
typedef HEAP *PHEAP;
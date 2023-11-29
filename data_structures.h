#include <deque>

typedef struct TAG_EDGE
{
    int index = -1;
    int start_edge;
    int end_edge;
    double weight;
    TAG_EDGE *next;
} EDGE;
typedef EDGE *PEDGE;

typedef struct TAG_VERTEX
{
    std::deque<EDGE> adj;
    int name;
    char color = 'W';
    double dist = INT_MAX;
    double fin = 0;
    int pi = -1;
    double heapPos = -1;
} VERTEX;
typedef VERTEX ELEMENT;
typedef ELEMENT *PELEMENT;

typedef struct TAG_HEAP
{
    int capacity;
    int size;
    int callCounter;
    PELEMENT *H;
} HEAP;
typedef HEAP *PHEAP;

typedef struct TAG_STACK
{
    int top;
    VERTEX *S[100];
} STACK;
typedef STACK *PSTACK;
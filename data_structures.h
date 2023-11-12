typedef struct TAG_VERTEX
{
    int index;
    char color;
    double disc;
    int pi;
    int position;
} VERTEX;
typedef VERTEX *PVERTEX;

typedef struct TAG_NODE
{
    int index;
    int start_edge;
    int end_edge;
    double weight;
    TAG_NODE *next;
} NODE;
typedef NODE *PNODE;
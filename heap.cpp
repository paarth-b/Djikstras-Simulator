#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include "heap.h"

HEAP *init(int capacity) // Create heap using int capacity
{
    HEAP *heap = new HEAP(); // Allocate memory for heap
    if (!heap)
    { // If heap is null, print error message and return null
        std::cerr << "Error: Heap is null";
        return nullptr;
    }

    heap->capacity = capacity;
    heap->size = 0;

    heap->H = new ELEMENT *[capacity];
    if (!heap->H)
    { // If heap->H is null, print error message and return null
        std::cerr << "Error: heap->H is null";
        delete heap;
        return nullptr;
    }

    return heap;
}

void swap(ELEMENT **H, ELEMENT **b)
{
    ELEMENT *temp = *H;
    *H = *b;
    *b = temp;
}

void minHeapify(HEAP *heap, int size, int parent)
{
    int smallest = parent;  // Initialize smallest as root
    int l = 2 * parent + 1; // Left child index
    int r = 2 * parent + 2; // Right child index

    // If left child dist is smaller than the root's dist
    if (l < size && heap->H[l]->dist < heap->H[smallest]->dist)
        smallest = l;

    // If right child dist is smaller than the smallest so far
    if (r < size && heap->H[r]->dist < heap->H[smallest]->dist)
        smallest = r;

    // If smallest is not the root
    if (smallest != parent)
    {
        // swap(&heap->H[parent], &heap->H[smallest]);
        VERTEX *temp = heap->H[parent];
        heap->H[parent] = heap->H[smallest];
        heap->H[smallest] = temp;
        // printf("Swapped %lf with %lf\n", arr[parent]->dist, arr[smallest]->dist);
        // Recursively apply minHeapify to the affected subtree
        minHeapify(heap, size, smallest);
    }
}

void buildHeap(HEAP *heap)
{
    heap->callCounter = 0;
    int n = heap->size;
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heap->callCounter++;
        minHeapify(heap, n, i);
    }
}

void print(HEAP *heap) // Print heap
{
    if (!heap)
    { // If heap is null, print error message and return
        std::cerr << "Error: Heap is NULL";
        return;
    }

    printf("Heap Size: %d\n", heap->size);

    for (int i = 0; i < heap->size; i++)
    { // Print each element in heap
        printf("Vertex: %d, Distance: %.2lf, Heap Position: %d\n", heap->H[i]->name, heap->H[i]->dist, i);
    }
}

void write(HEAP *heap, FILE *fp)
{                                    // Write heap to file fp
    fprintf(fp, "%d\n", heap->size); // Write number of elements in heap
    for (int i = 0; i < heap->size; i++)
    { // Print each element in heap
        fprintf(fp, "%lf\n", heap->H[i]->dist);
    }
}

void read(HEAP *heap, FILE *fp, int flag)
{ // Read heap from file fp
    int n;
    fscanf(fp, "%d", &n); // Read number of elements in heap

    if (heap->capacity < n)
    { // If heap->capacity is less than n, print error message
        std::cerr << "Error: heap capacity is less than heap size\n";
        return;
    }
    for (int j = 0; j < n; j++)
    { // Read each element in heap
        ELEMENT *element = (ELEMENT *)malloc(sizeof(ELEMENT));
        fscanf(fp, "%lf", &element->dist);
        heap->H[j] = element;
    }
    heap->size = n;  // Set heap->size to n
    buildHeap(heap); // Build heap
    if (flag == 1)
        printf("Number of Heapify calls: %d\n", heap->callCounter);
    heap->callCounter = 0;
}

void insert(HEAP *heap, VERTEX *element)
{ // Insert dist into heap
    if (heap->size == heap->capacity)
    { // If heap is full, print error message and return
        std::cerr << "Error: heap is full\n";
        return;
    }

    // Create new element and insert into heap
    heap->H[heap->size] = element;
    heap->size++;

    // buildHeap(heap); // Build heap
    heap->callCounter = 0;
}

VERTEX *extractMin(HEAP *heap)
{                             // Extract minimum element from heap
    VERTEX *min = heap->H[0]; // Store minimum element
    if (heap->size == 0)
    { // If heap is empty, print error message and return
        std::cerr << "Error: heap is empty\n";
    }

    // Swap root with last element and swap rootPos
    heap->H[0] = heap->H[heap->size - 1];
    heap->H[heap->size - 1] = min;
    heap->H[0]->heapPos = 0;
    heap->H[heap->size - 1]->heapPos = heap->size - 1;

    heap->size--; // Decrement heap size

    minHeapify(heap, heap->size - 1, 0); // Build heap

    return min;
}

// void decreaseKey(HEAP *heap, VERTEX *v, double dist)
// { // Decrease dist at position in heap
//     if (v->name - 1 < 0 || v->name - 1 > heap->size || v->dist < dist)
//     { // If position is out of bounds, print error message and return
//         // std::cerr << "Error: invalid call to decreaseKey";
//         return;
//     }
//     v->dist = dist; // Set dist at position to new dist

//     while (v->name - 1 > 0 && heap->H[(v->name - 1) / 2]->dist > v->dist)
//     {
//         swap(&heap->H[(v->name - 1) / 2], &heap->H[v->name - 1]);
//         v->name = (v->name - 1) / 2;
//     }
//     // buildHeap(heap); // Build heap
// }

void decreaseKey(HEAP *heap, int index, double dist)
{
    if (index < 0 || index > heap->size || heap->H[index]->dist < dist)
    {
        return;
    }
    heap->H[index]->dist = dist;
    while (index > 0 && heap->H[(index - 1) / 2]->dist > heap->H[index]->dist)
    {
        int parentPos = heap->H[(index - 1) / 2]->heapPos;
        int childPos = heap->H[index]->heapPos;

        swap(&heap->H[(index - 1) / 2], &heap->H[index]);
        heap->H[(index - 1) / 2]->heapPos = parentPos;
        heap->H[index]->heapPos = childPos;

        index = (index - 1) / 2;
    }
}

#include "heap.h"
#include <stdlib.h>
#include <cstdio>
#include <iostream>

HEAP *init(int capacity) // Create heap using int capacity
{
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP)); // Allocate memory for heap
    if (!heap)
    { // If heap is null, print error message and return null
        std::cerr << "Error: Heap is null";
        return nullptr;
    }

    heap->capacity = capacity;
    heap->size = 0;

    heap->A = (ELEMENT **)malloc(sizeof(ELEMENT *) * capacity);
    if (!heap->A)
    { // If heap->A is null, print error message and return null
        std::cerr << "Error: heap->A is null";
        delete heap;
        return nullptr;
    }

    return heap;
}

void swap(ELEMENT **a, ELEMENT **b)
{
    ELEMENT *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(HEAP *heap, int size, int parent)
{
    int smallest = parent;  // Initialize smallest as root
    int l = 2 * parent + 1; // Left child index
    int r = 2 * parent + 2; // Right child index

    // If left child key is smaller than the root's key
    if (l < size && heap->A[l]->key < heap->A[smallest]->key)
        smallest = l;

    // If right child key is smaller than the smallest so far
    if (r < size && heap->A[r]->key < heap->A[smallest]->key)
        smallest = r;

    // If smallest is not the root
    if (smallest != parent)
    {
        swap(&heap->A[parent], &heap->A[smallest]);
        // printf("Swapped %lf with %lf\n", arr[parent]->key, arr[smallest]->key);
        // Recursively apply minHeapify to the affected subtree
        heap->callCounter++;
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

    printf("%d\n", heap->size);

    for (int i = 0; i < heap->size; i++)
    { // Print each element in heap
        printf("%lf\n", heap->A[i]->key);
    }
}

void write(HEAP *heap, FILE *fp)
{                                    // Write heap to file fp
    fprintf(fp, "%d\n", heap->size); // Write number of elements in heap
    for (int i = 0; i < heap->size; i++)
    { // Print each element in heap
        fprintf(fp, "%lf\n", heap->A[i]->key);
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
        fscanf(fp, "%lf", &element->key);
        heap->A[j] = element;
    }
    heap->size = n;  // Set heap->size to n
    buildHeap(heap); // Build heap
    if (flag == 1)
        printf("Number of Heapify calls: %d\n", heap->callCounter);
    heap->callCounter = 0;
}

void insert(HEAP *heap, double *key)
{ // Insert key into heap
    if (heap->size == heap->capacity)
    { // If heap is full, print error message and return
        std::cerr << "Error: heap is full\n";
        return;
    }

    // Create new element and insert into heap
    ELEMENT *element = (ELEMENT *)malloc(sizeof(ELEMENT));
    element->key = *key;
    heap->A[heap->size] = element;
    heap->size++;

    buildHeap(heap); // Build heap
    heap->callCounter = 0;
}

void extractMin(HEAP *heap, int flag)
{ // Extract minimum element from heap
    if (heap->size == 0)
    { // If heap is empty, print error message and return
        std::cerr << "Error: heap is empty\n";
        return;
    }

    fprintf(stdout, "ExtractMin: %lf\n", heap->A[0]->key);
    // Print minimum element

    // Swap root with last element
    swap(&heap->A[0], &heap->A[heap->size - 1]);
    heap->size--; // Decrement heap size

    heap->callCounter++;
    minHeapify(heap, heap->size, 0); // Build heap
    if (flag == 1)
        printf("Number of Heapify calls: %d\n", heap->callCounter);
    heap->callCounter = 0;
}

void decreaseKey(HEAP *heap, double *position, double *key)
{ // Decrease key at position in heap
    int index = static_cast<int>(*position) - 1;
    if (index < 0 || index > heap->size || heap->A[index]->key < *key)
    { // If position is out of bounds, print error message and return
        std::cerr << "Error: invalid call to decreaseKey";
        return;
    }
    heap->A[index]->key = *key; // Set key at position to new key

    buildHeap(heap); // Build heap
}

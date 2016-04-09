#pragma once

#define CAPACITY 1

struct elem_t {
    size_t size;
    void* data;
};


struct queue_t {
    int size;
    int capacity;
    size_t itemSize;
    struct elem_t* items;
};

typedef struct queue_t Queue;

int addQ(Queue* queue, const void* item);
void* peekQ(const Queue* queue);
void* pollQ(Queue* queue, void* head);
int emptyQ(const Queue* queue);

void initQ(Queue* queue, size_t itemSize);
void reallocateQ(Queue** queue);
void freeQ(Queue* queue);
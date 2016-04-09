#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

void initQ(Queue* queue, size_t itemSize) {
    if (queue == NULL || itemSize <= 0) return;
    
    int i = 0;
    queue->capacity = CAPACITY;
    queue->size = 0;
    queue->itemSize = itemSize;
    queue->items = (struct elem_t*)calloc(queue->capacity, sizeof(struct elem_t));
    for (; i < queue->capacity; ++i) {
        queue->items[i].size = itemSize;
    }
    for (i = 0; i < queue->capacity; ++i) {
        queue->items[i].data = malloc(itemSize);
        memset(queue->items[i].data, 0, itemSize);
    }
}

int addQ(Queue* queue, const void* data) {
    if (queue == NULL || data == NULL) return -1;
    if (queue->size + 1 < queue->capacity) {
        queue->items[queue->size].data = malloc(queue->itemSize);
        memcpy(queue->items[queue->size].data, data, sizeof(queue->items[queue->size].data));
        queue->size++;
    } else {
        reallocateQ(&queue);
        queue->items[queue->size].data = malloc(queue->itemSize);
        memcpy(queue->items[queue->size].data, data, sizeof(queue->items[queue->size].data));
        queue->size++;
    }
    return 1;
}

int emptyQ(const Queue* queue) {
    if (queue == NULL) return -1;
    return queue->size == 0;
}

void* peekQ(const Queue* queue) {
    if (queue == NULL || queue->size == 0) {
        return NULL;
    }
    return queue->items[0].data;
}

void* pollQ(Queue* queue, void* head) {
    if (queue == NULL || head == NULL || queue->size == 0) return NULL;
    memcpy(head, queue->items[0].data, sizeof(queue->items[0].data));
    
    int i = 1;
    for (; i < queue->size; ++i) {
        memmove(queue->items[i - 1].data, queue->items[i].data, sizeof(queue->itemSize));
    }
    queue->size--;
    return head;
}

void reallocateQ(Queue** queue) {
    if (queue == NULL) return;

    Queue temp;
    temp.capacity = (*queue)->capacity;
    temp.size = (*queue)->size;
    temp.itemSize = (*queue)->itemSize;
    temp.items = (struct elem_t*)calloc(temp.capacity, sizeof(struct elem_t));

    int i = 0;
    for (; i < temp.capacity; ++i) {
        temp.items[i].size = temp.itemSize;
    }
    for (i = 0; i < temp.size; ++i) {
        temp.items[i].data = malloc(temp.itemSize);
        memmove(temp.items[i].data, (*queue)->items[i].data, sizeof(temp.items[i].data));
    }
    freeQ(*queue);

    (*queue)->capacity = temp.capacity + CAPACITY;
    (*queue)->size = temp.size;
    (*queue)->itemSize = temp.itemSize;
    (*queue)->items = (struct elem_t*)calloc((*queue)->capacity, sizeof(struct elem_t));
    for (; i < (*queue)->capacity; ++i) {
        (*queue)->items[i].size = temp.itemSize;
    }
    for (i = 0; i < (*queue)->size; ++i) {
        (*queue)->items[i].data = malloc((*queue)->itemSize);
        memmove((*queue)->items[i].data, temp.items[i].data, sizeof((*queue)->items[i].data));
    }
    freeQ(&temp);
}

void freeQ(Queue* queue) {
    if (queue == NULL) return;
    
    int i = 0;
    for (; i < queue->capacity; ++i) {
        free(queue->items[i].data);
    }
    free(queue->items);
}
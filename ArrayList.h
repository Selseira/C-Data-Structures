#pragma once

#define CAPACITY 1

struct elem_t {
    size_t size;
    void* data;
};


struct list_t {
    int size;
    int capacity;
    size_t itemSize;
    struct elem_t* items;
};

typedef struct list_t ArrayList;

int addAL(ArrayList* list, void* item);
void addAtAL(ArrayList* list, int index, const void* item);
void clearAL(ArrayList* list);
int containsAL(const ArrayList* list, const void* item);
void* getAL(const ArrayList* list, int index);
int indexOfAL(const ArrayList* list, const void* item);
int lastIndexOfAL(const ArrayList* list, const void* item);
int isEmptyAL(const ArrayList* list);
void* setAL(const ArrayList* list, int index, const void* item);
int sizeAL(const ArrayList* list);
int subListAL(const ArrayList* list, ArrayList* sublist, int fromIndex, int toIndex);
int removeAL(ArrayList* list, int index);
int removeItemAL(ArrayList* list, const void* item);
void* toArrayAL(const ArrayList* list, void* array);
void initAL(ArrayList* list, size_t itemSize);
void reallocateAL(ArrayList** list);
void freeAL(ArrayList* list);
void printAL(const ArrayList* list);
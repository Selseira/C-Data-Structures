#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"


int addAL(ArrayList* list, void* item) {
    if (list == NULL || item == NULL) return -1;
    if (list->size < list->capacity) {
        list->items[list->size].data = malloc(list->itemSize);
        memcpy(list->items[list->size].data, item, sizeof(list->items[list->size].data));
        list->size++;
    } else {
        reallocateAL(&list);
        list->items[list->size].data = malloc(list->itemSize);
        memcpy(list->items[list->size].data, item, sizeof(list->items[list->size].data));
        list->size++;
    }
    return 1;
}

void addAtAL(ArrayList* list, int index, const void* item) {
    if (list == NULL || item == NULL || index < 0 || index >= list->size) return;
 
    if (list->items[index].data == NULL) {
        list->items[list->size].data = malloc(list->itemSize);
        memcpy(list->items[list->size].data, item, sizeof(list->items[list->size].data));
        list->size++;
    } else {
        if (list->size == list->capacity) {
            reallocateAL(&list);
        }
        int i = 0;
        
        for (i = list->size - 1; i >= index; --i) {
            if (list->items[i + 1].data == NULL) {
                list->items[i + 1].data = malloc(list->itemSize);
            }
            memcpy((list->items[i+1].data), (list->items[i].data), sizeof(list->itemSize));
        }
        memcpy((list->items[index].data), item, sizeof(list->itemSize));
        list->size++;
    }
}

void clearAL(ArrayList* list) {
    if (list == NULL) return;

    int i = 1;
    for (; i < list->size; ++i) {
        free(list->items[i].data);
    }
    int t = 0x00;
    memcpy(list->items[0].data, &t, sizeof(list->items[0].data));
    list->size = 0;
}

int containsAL(const ArrayList* list, const void* item) {
    if (list == NULL || item == NULL || list->size == 0) return 0;
    
    int i = 0;
    for (; i < list->size; ++i) {
        if (memcmp(list->items[i].data, item, sizeof(list->items[i].data)) == 0) {
            return 1;
        }
    }
    return 0;
}

void* getAL(const ArrayList* list, int index) {
    if (list == NULL || index < 0 || list->size <= index) return NULL;
    return list->items[index].data;
}

int indexOfAL(const ArrayList* list, const void* item) {
    if (list == NULL || item == NULL || list->size == 0) return -1;
    
    int i = 0;
    for (; i < list->size; ++i) {
        if (memcmp(list->items[i].data, item, sizeof(list->items[i].data)) == 0) {
            return i;
        }
    }
    return -1;
}

int isEmptyAL(const ArrayList* list) {
    if (list == NULL) return -1;
    return list->size == 0;
}

int lastIndexOfAL(const ArrayList* list, const void* item) {
    if (list == NULL || item == NULL || list->size == 0) return -1;

    int i = list->size - 1;
    for (; i >= 0; --i) {
        if (memcmp(list->items[i].data, item, sizeof(list->items[i].data)) == 0) {
            return i;
        }
    }
    return -1;
}

void* setAL(const ArrayList* list, int index, const void* item) {
    if (list == NULL || item == NULL || list->size == 0 || index < 0 || index >= list->size) {
        return NULL;
    }
    memcpy(list->items[index].data, item, sizeof(list->items[index].data));
    return list->items[index].data;
}

int sizeAL(const ArrayList* list) {
    if (list == NULL) return 0;
    return list->size;
}

int subListAL(const ArrayList* list, ArrayList* sublist, int fromIndex, int toIndex) {
    if (list == NULL || sublist == NULL || list->size == 0
        || fromIndex < 0 || fromIndex >= list->size
        || toIndex < 0 || toIndex >= list->size || toIndex - fromIndex <= 0) {
        return -1;
    }
    int i = 0;
    for (i = fromIndex; i <= toIndex; ++i) {
        addAL(sublist, list->items[i].data);
    }
    return 1;
}

int removeAL(ArrayList* list, int index) {
    if (list == NULL || list->size == 0 || index < 0 || index >= list->size) {
        return -1;
    }
    int i = 0;
    for (i = index; i < list->size - 1; ++i) {
        memcpy(list->items[i].data, list->items[i + 1].data, sizeof(list->items[i].data));
    }
    free(list->items[list->size - 1].data);
    list->size--;
    return 1;
}

int removeItemAL(ArrayList* list, const void* item) {
    if (list == NULL || item == NULL || list->size == 0) {
        return -1;
    }
    int index = indexOfAL(list, item);
    return removeAL(list, index);
}

void* toArrayAL(const ArrayList* list, void* array) {
    if (list == NULL || array == NULL || list->size == 0) {
        return NULL;
    }
    
    int i = 0;
    for (; i < list->size; ++i) {
        memcpy(array, list->items[i].data, sizeof(list->items[i].data));
        char *c = (char*)array + list->itemSize;
        array = (void*)c;
    }
    return array;
}

void initAL(ArrayList* list, size_t itemSize) {
    int i = 0;
    list->capacity = CAPACITY;
    list->size = 0;
    list->itemSize = itemSize;
    list->items = (struct elem_t*)calloc(list->capacity, sizeof(struct elem_t));
    for (; i < list->capacity; ++i) {
        list->items[i].size = itemSize;
    }
    for (i = 0; i < list->capacity; ++i) {
        list->items[i].data = NULL;
    }
}

void reallocateAL(ArrayList** list) {
    if (list == NULL) return;

    ArrayList temp;
    temp.capacity = (*list)->capacity;
    temp.size = (*list)->size;
    temp.itemSize = (*list)->itemSize;
    temp.items = (struct elem_t*)calloc(temp.capacity, sizeof(struct elem_t));

    int i = 0;
    for (; i < temp.capacity; ++i) {
        temp.items[i].size = temp.itemSize;
    }
    for (i = 0; i < temp.size; ++i) {
        temp.items[i].data = malloc(temp.itemSize);
        memmove(temp.items[i].data, (*list)->items[i].data, sizeof(temp.items[i].data));
    }
    freeAL(*list);

    (*list)->capacity = temp.capacity + CAPACITY;
    (*list)->size = temp.size;
    (*list)->itemSize = temp.itemSize;
    (*list)->items = (struct elem_t*)calloc((*list)->capacity, sizeof(struct elem_t));
    for (; i < (*list)->capacity; ++i) {
        (*list)->items[i].size = temp.itemSize;
    }
    for (i = 0; i < (*list)->size; ++i) {
        (*list)->items[i].data = malloc((*list)->itemSize);
        memmove((*list)->items[i].data, temp.items[i].data, sizeof((*list)->items[i].data));
    }
    freeAL(&temp);
}

void printAL(const ArrayList* list) {
    if (list == NULL) return;

    int i = 0;
    for (; i < list->size - 1; ++i) {
        printf("%d --> ", *(int*)(list->items[i].data));
    }
    printf("%d\n", *(int*)(list->items[i].data));
}

void freeAL(ArrayList* list) {
    if (list == NULL) return;
    
    int i = 0;
    for (; i < list->size; ++i) {
        free(list->items[i].data);
    }
    free(list->items);
}
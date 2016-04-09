#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void initStack(Stack* stack, size_t itemSize) {
    int i = 0;
    stack->capacity = CAPACITY;
    stack->size = 0;
    stack->itemSize = itemSize;
    stack->items = (struct elem_t*)calloc(stack->capacity, sizeof(struct elem_t));
    for (; i < stack->capacity; ++i) {
        stack->items[i].size = itemSize;
    }
    for (i = 0; i < stack->capacity; ++i) {
        stack->items[i].data = malloc(itemSize);
        memset(stack->items[i].data, 0, itemSize);
    }
}

void push(Stack* stack, void* data) {
    if (stack->size + 1 < stack->capacity) {
        stack->items[stack->size].data = malloc(stack->itemSize);
        memcpy(stack->items[stack->size].data, data, sizeof(stack->items[stack->size].data));
        stack->size++;
    } else {
        reallocateStack(&stack);
        stack->items[stack->size].data = malloc(stack->itemSize);
        memcpy(stack->items[stack->size].data, data, sizeof(stack->items[stack->size].data));
        stack->size++;
    }
}

void* pop(Stack* stack) {
    if (stack->size - 1 < 0) {
        return NULL;
    }
    stack->size--;
    return stack->items[stack->size].data;
}

int empty(const Stack* stack) {
    return stack->size == 0;
}

void* peek(const Stack* stack) {
    if (stack->size - 1 < 0) {
        return NULL;
    }
    return stack->items[stack->size].data;
}

int search(const Stack* stack, const void* data, int isString) {
    if (stack->size <= 0) return -1;
    
    int i = 0;
    for (; i < stack->size; ++i) {
        /*if (!isString) {
            if ((stack->items[i].data) == data) {
                return stack->size - i;
            }
        } else {
            if (strncmp((char*)(stack->items[i].data), (char*)data, stack->itemSize) == 0) {
                return stack->size - i;
            }
        }*/
        if (memcmp(stack->items[i].data, data, sizeof(stack->items[i].data)) == 0) {
            return stack->size - i;
        }
    }
    return -1;
}

void reallocateStack(Stack** stack) {
    Stack temp;
    temp.capacity = (*stack)->capacity;
    temp.size = (*stack)->size;
    temp.itemSize = (*stack)->itemSize;
    temp.items = (struct elem_t*)calloc(temp.capacity, sizeof(struct elem_t));
    
    int i = 0;
    for (; i < temp.capacity; ++i) {
        temp.items[i].size = temp.itemSize;
    }
    for (i = 0; i < temp.size; ++i) {
        temp.items[i].data = malloc(temp.itemSize);
        memmove(temp.items[i].data, (*stack)->items[i].data, sizeof(temp.items[i].data));
    }
    freeStack(*stack);

    (*stack)->capacity = temp.capacity + CAPACITY;
    (*stack)->size = temp.size;
    (*stack)->itemSize = temp.itemSize;
    (*stack)->items = (struct elem_t*)calloc((*stack)->capacity, sizeof(struct elem_t));
    for (; i < (*stack)->capacity; ++i) {
        (*stack)->items[i].size = temp.itemSize;
    }
    for (i = 0; i < (*stack)->size; ++i) {
        (*stack)->items[i].data = malloc((*stack)->itemSize);
        memmove((*stack)->items[i].data, temp.items[i].data, sizeof((*stack)->items[i].data));
    }
    freeStack(&temp);
}

void printStack(const Stack* stack) {
    int i = stack->size - 1;
    for (; i > 0; --i) {
        printf("%s\n", (stack->items[i].data));
    }
    printf("%s\n", (stack->items[i].data));
}

void printStack2(const Stack* stack, char* format) {
    int i = stack->size - 1;
    for (; i > 0; --i) {
        printf(format, (stack->items[i].data));
    }
    printf(format, (stack->items[i].data));
}

void freeStack(Stack* stack) {
    int i = 0;
    for (; i < stack->capacity; ++i) {
        free(stack->items[i].data);
    }
    free(stack->items);
}
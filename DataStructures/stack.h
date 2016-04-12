#pragma once

#define CAPACITY 10

struct elem_t {
    size_t size;
    void* data;
};

struct stack_t
{
    int size;
    int capacity;
    size_t itemSize;
    struct elem_t* items;
};

typedef struct stack_t Stack;

void initStack(Stack* stack, size_t itemSize);
void push(Stack* stack, void* data);
void* pop(Stack* stack);
int empty(const Stack* stack);
void* peek(const Stack* stack);
int search(const Stack* stack, const void* data, int isString);
void reallocateStack(Stack** stack);
void printStack(const Stack* stack);
void printStack2(const Stack* stack, char* format);
void freeStack(Stack* stack);
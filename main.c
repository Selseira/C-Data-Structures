#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "stack.h"
//#include "ArrayList.h"
#include "Queue.h"

void printQ(const Queue* q);

int main(int argc, char** argv) {

    Queue queue;

    initQ(&queue, sizeof(int));

    int x = 123;
    addQ(&queue, &x);

    x = 124;
    addQ(&queue, &x);

    printQ(&queue);

    pollQ(&queue, &x);
    printf("X: %d\n", x);

    printQ(&queue);

    freeQ(&queue);

    return 0;
}

void printQ(const Queue* q) {
    for (int i = 0; i < q->size - 1; ++i) {
        printf("%d <-- ", *(int*)(q->items[i].data));
    }
    printf("%d\n", *(int*)(q->items[q->size - 1].data));
}
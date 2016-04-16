#pragma once

#define CAPACITY 1

struct elem_t {
	size_t size;
	void* data;
};


struct set_t {
	int size;
	int capacity;
	size_t itemSize;
	struct elem_t* items;
};

typedef struct set_t Set;

int addSet(Set* set, void* item);
void clearSet(Set* set);
int containsSet(const Set* set, const void* item);
int equalsSet(const void* item1, const void* item2, size_t elemSize);
int isEmptySet(const Set* set);
int sizeSet(const Set* set);
int removeSet(Set* set, const void* item);
void* toArraySet(const Set* set, void* array);
void initSet(Set* set, size_t itemSize);
void reallocateSet(Set** set);
void freeSet(Set* set);
void printSet(const Set* set);
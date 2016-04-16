#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Set.h"


int addSet(Set* set, void* item) {
	if (set == NULL || item == NULL) return -1;
	if (containsSet(set, item)) return 0;
	if (set->size < set->capacity) {
		set->items[set->size].data = malloc(set->itemSize);
		memcpy(set->items[set->size].data, item, sizeof(set->items[set->size].data));
		set->size++;
	}
	else {
		reallocateSet(&set);
		set->items[set->size].data = malloc(set->itemSize);
		memcpy(set->items[set->size].data, item, sizeof(set->items[set->size].data));
		set->size++;
	}
	return 1;
}

void clearSet(Set* set) {
	if (set == NULL) return;

	int i = 1;
	for (; i < set->size; ++i) {
		free(set->items[i].data);
	}
	char c = 0;
	memcpy(set->items[0].data, &c, sizeof(set->items[0].data));
	set->size = 0;
}

int containsSet(const Set* set, const void* item) {
	if (set == NULL || item == NULL || set->size == 0) return 0;

	int i = 0;
	for (; i < set->size; ++i) {
		if (memcmp(set->items[i].data, item, sizeof(set->items[i].data)) == 0) {
			return 1;
		}
	}
	return 0;
}

int equalsSet(const void* item1, const void* item2, size_t elemSize) {
	if (item1 == NULL && item2 == NULL) return 1;
	if (item1 == NULL || item2 == NULL) return 0;
	return memcmp(item1, item2, elemSize) == 0;

}

int isEmptySet(const Set* set) {
	if (set == NULL) return -1;
	return set->size == 0;
}


int sizeSet(const Set* set) {
	if (set == NULL) return 0;
	return set->size;
}

int removeSet(Set* set, const void* item) {
	if (set == NULL || item == NULL || set->size == 0) {
		return -1;
	}
	int found = 0;
	for (int i = 0; i < set->size; ++i) {
		if (equalsSet(item, set->items[i].data, set->itemSize)) {
			for (int j = i; j < set->size-1; ++j) {
				memcpy(set->items[j].data, set->items[j + 1].data, sizeof(set->items[j].data));
			}
			found = 1;
		}
	}
	free(set->items[set->size - 1].data);
	set->size--;
	return found;
}

void* toArraySet(const Set* set, void* array) {
	if (set == NULL || array == NULL || set->size == 0) {
		return NULL;
	}

	int i = 0;
	for (; i < set->size; ++i) {
		memcpy(array, set->items[i].data, sizeof(set->items[i].data));
		char *c = (char*)array + set->itemSize;
		array = (void*)c;
	}
	return array;
}

void initSet(Set* set, size_t itemSize) {
	int i = 0;
	set->capacity = CAPACITY;
	set->size = 0;
	set->itemSize = itemSize;
	set->items = (struct elem_t*)calloc(set->capacity, sizeof(struct elem_t));
	for (; i < set->capacity; ++i) {
		set->items[i].size = itemSize;
	}
	for (i = 0; i < set->capacity; ++i) {
		set->items[i].data = NULL;
	}
}

void reallocateSet(Set** set) {
	if (set == NULL) return;

	Set temp;
	temp.capacity = (*set)->capacity;
	temp.size = (*set)->size;
	temp.itemSize = (*set)->itemSize;
	temp.items = (struct elem_t*)calloc(temp.capacity, sizeof(struct elem_t));

	int i = 0;
	for (; i < temp.capacity; ++i) {
		temp.items[i].size = temp.itemSize;
	}
	for (i = 0; i < temp.size; ++i) {
		temp.items[i].data = malloc(temp.itemSize);
		memmove(temp.items[i].data, (*set)->items[i].data, sizeof(temp.items[i].data));
	}
	freeSet(*set);

	(*set)->capacity = temp.capacity + CAPACITY;
	(*set)->size = temp.size;
	(*set)->itemSize = temp.itemSize;
	(*set)->items = (struct elem_t*)calloc((*set)->capacity, sizeof(struct elem_t));
	for (; i < (*set)->capacity; ++i) {
		(*set)->items[i].size = temp.itemSize;
	}
	for (i = 0; i < (*set)->size; ++i) {
		(*set)->items[i].data = malloc((*set)->itemSize);
		memmove((*set)->items[i].data, temp.items[i].data, sizeof((*set)->items[i].data));
	}
	freeSet(&temp);
}

void printSet(const Set* set) {
	if (set == NULL) return;

	int i = 0;
	for (; i < set->size - 1; ++i) {
		printf("%d --> ", *(int*)(set->items[i].data));
	}
	printf("%d\n", *(int*)(set->items[i].data));
}

void freeSet(Set* set) {
	if (set == NULL) return;

	int i = 0;
	for (; i < set->size; ++i) {
		free(set->items[i].data);
	}
	free(set->items);
}
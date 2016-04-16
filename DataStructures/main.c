#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "stack.h"
//#include "ArrayList.h"
//#include "Queue.h"
#include "Set.h"

int main(int argc, char** argv) {

	Set set;
	initSet(&set, sizeof(int));

	int x = 999;
	addSet(&set, &x);

	x = 777;
	addSet(&set, &x);

	x = 776;
	addSet(&set, &x);
	
	clearSet(&set);

	for (; x >= 700; --x)
		addSet(&set, &x);

	printSet(&set);

	printf("\n\n");

	x = 760;
	removeSet(&set, &x);

	int size = sizeSet(&set);
	int setArray[500];
	memset(setArray, 0, 500 * sizeof(int));

	printSet(&set);

	toArraySet(&set, setArray);

	for (int i = 0; i < size; ++i) {
		printf("Set[%d]: %d\n", i, setArray[i]);
	}

	freeSet(&set);

	return 0;
}


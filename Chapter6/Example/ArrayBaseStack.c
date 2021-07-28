#include "ArrayBaseStack.h"
#include <stdio.h>

void StackInit(Stack* pstack) {
	pstack->topIndex = -1;
}

int SIsEmpty(Stack* pstack) {
	if (pstack->topIndex == -1)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack* pstack, Data data) {
	pstack->topIndex += 1;
	pstack->stackArr[pstack->topIndex] = data;
}

Data SPop(Stack* pstack) {
	if (SIsEmpty(pstack)) {
		printf("Stack memory error!");
		return -1;
	}

	Data rdata = pstack->stackArr[pstack->topIndex];
	pstack->topIndex -= 1;

	return rdata;
}

Data SPeek(Stack* pstack) {
	if (SIsEmpty(pstack)) {
		printf("Stack memory error!");
		return -1;
	}

	return pstack->stackArr[pstack->topIndex];
}
#include <stdio.h>
#include "ArrayList.h"

void ListInit(List* plist) {
	plist->numOfData = 0;
	plist->curPosition = -1;
}

void LInsert(List* plist, LData pdata) {
	if (plist->numOfData + 1 > LIST_LEN) {
		printf("가득 찼습니다.\n");
		return;
	}
	plist->arr[plist->numOfData] = pdata;
	plist->numOfData++;
}

int LFirst(List* plist, LData* pdata) {
	plist->curPosition = -1;
	*pdata = plist->arr[++plist->curPosition];
	if (plist->curPosition + 1 <= plist->numOfData) {
		return 1;
	}
	return 0;
}

int LNext(List* plist, LData* pdata) {
	plist->curPosition++;
	*pdata = plist->arr[plist->curPosition];
	if (plist->curPosition + 1 <= plist->numOfData) {
		return 1;
	}
	return 0;
}

LData LRemove(List* plist) {
	LData temp;
	if (plist->curPosition + 1 == plist->numOfData) {
		temp = plist->arr[plist->curPosition];
		plist->curPosition--;
	}
	else {
		temp = plist->arr[plist->curPosition];
		for (int i = plist->curPosition; i < plist->numOfData-1; i++) {
			plist->arr[i] = plist->arr[i + 1];
		}
		plist->curPosition--;
	}
	plist->numOfData--;
	return temp;
}

int LCount(List* plist) {
	return plist->numOfData;
}

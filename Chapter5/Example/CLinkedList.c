#include <stdio.h>
#include "CLinkedList.h"

void ListInit(List* plist) { // 초기화
	plist->tail = NULL;
	plist->cur = NULL;
	plist->before = NULL;
	plist->numOfData = 0;
}

void LInsert(List* plist, Data data) { // tail에 추가
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if (plist->tail == NULL) { // 비어있는 경우
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else {
		newNode->next = plist->tail->next; // 새 노드와 기존에 저장된 노드 연결
		plist->tail->next = newNode; // 기존 노드의 tail이 새 노드를 가리키게 연결
		plist->tail = newNode; // tail이 새로 추가된 노드를 가르키게 함
	}
	(plist->numOfData)++;
}

void LInsertFront(List* plist, Data data) { // Head에 추가
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if(plist->tail == NULL) { // 비어있는 경우
		plist->tail = newNode;
		newNode->next = newNode;
	}
	else {
		newNode->next = plist->tail->next; // 새 노드와 기존에 저장된 노드 연결
		plist->tail->next = newNode; // 기존 노드의 tail이 새 노드를 가르키게 연결
	}
	(plist->numOfData)++;
}

int LFirst(List* plist, Data* pdata) {
	if (plist->tail == NULL) { // 비어있는 경우
		return FALSE;
	}
	plist->before = plist->tail; // before가 tail을 가리키게 한다.
	plist->cur = plist->tail->next; // cur이 tail의 다음을 가리키게 한다

	*pdata = plist->cur->data; 
	return TRUE;
}

int LNext(List* plist, Data* pdata) {
	if (plist->tail == NULL) { // 비어있는 경우
		return FALSE;
	}
	plist->before = plist->cur; // before가 cur을 가리키게 한다
	plist->cur = plist->cur->next; // cur이 cur의 다음을 가리키게 한다.

	*pdata = plist->cur->data;
	return TRUE;
}

Data LRemove(List* plist) {
	Node* rpos = plist->cur;
	Data rdata = rpos->data;

	
	if (rpos == plist->tail) { // 삭제하려는 노드가 tail인 경우
		if (plist->tail == plist->tail->next) { // 노드가 하나인 경우
			plist->tail == NULL;
		}
		else {
			plist->tail = plist->before;
		}
	}

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;
	
	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List* plist) {
	return (plist->numOfData);
}

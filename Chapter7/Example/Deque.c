#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"

void DequeInit(Deque* pdeq) {
	pdeq->head = NULL;
	pdeq->tail = NULL;
}

int DQIsEmpty(Deque* pdeq) {
	if (pdeq->head == NULL) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void DQAddFirst(Deque* pdeq, Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = pdeq->head;

	if (DQIsEmpty(pdeq)) {
		pdeq->tail = newNode;
	}
	else {
		pdeq->head->prev = newNode;
	}
	newNode->prev = NULL;
	pdeq->head = newNode;
}

void DQAddLast(Deque* pdeq, Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->prev = pdeq->tail;

	if (DQIsEmpty(pdeq)) {
		pdeq->head = newNode;
	}
	else {
		pdeq->tail->next = newNode;
	}
	newNode->next = NULL;
	pdeq->tail = newNode;
}

Data DQRemoveFirst(Deque* pdeq) {
	if (DQIsEmpty(pdeq)) {
		printf("Queue Memoey Error!\n");
		exit(-1);
	}

	Node* rNode = pdeq->head;
	Data rData = pdeq->head->data;

	pdeq->head = pdeq->head->next;
	free(rNode);

	if (pdeq->head == NULL) {
		pdeq->tail = NULL;
	}
	else
		pdeq->head->prev = NULL;

	return rData;
}

Data DQRemoveLast(Deque* pdeq) {
	if (DQIsEmpty(pdeq)) {
		printf("Queue Memoey Error!\n");
		exit(-1);
	}

	Node* rNode = pdeq->tail;
	Data rData = pdeq->tail->data;
	
	pdeq->tail = pdeq->tail->prev;

	if (pdeq->tail == NULL) {

	}
}

Data DQGetFirst(Deque* pdeq) {

}

Data DQGetLast(Deque* pdeq) {

}

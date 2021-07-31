#include <stdio.h>
#include <stdlib.h>
#include "CircularQueue.h"

void QueueInit(Queue* pq) {
	pq->front = 0;
	pq->rear = 0;
}

int QIsEmpty(Queue* pq) {
	if (pq->front == pq->rear) {
		return TRUE;
	}
	else
		return FALSE;
}

int NextPosIdx(int pos) {
	if (pos == QUE_LEN - 1)
		return 0;
	else
		return pos + 1;
}

void Enqueue(Queue* pq, Data data) {
	int rnext = NextPosIdx(pq->rear);
	if (rnext == pq->front) {
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	pq->queArr[rnext] = data;
	pq->rear = rnext;
}

Data Dequeue(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue Memory Error!\n");
		exit(-1);
	}
	pq->front = NextPosIdx(pq->front);
	Data rdata = pq->queArr[pq->front];
	
	return rdata;
}

Data QPeek(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	return pq->queArr[NextPosIdx(pq->front)];
}
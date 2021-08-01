# 8-1 트리의 개요 <br>
트리는 앞에서 배웠던 리스트, 스택, 큐 등의 선형 자료구조와 달리 비선형 자료구조이다. <br>

``` C
void QueueInit(Queue * pt);
// 큐의 초기화를 진행한다.
// 큐 생성 후 제일 먼저 호출되어야 하는 함수이다.

int QIsEmpty(Queue * pq);
// 큐가 빈 경우 TRUE(1)을, 그렇지 않은 경우 FALSE(0)을 반환한다.

void Enqueue(Queue * pq, Data data);
// 큐에 데이터를 저장한다. 매개변수 data로 전달된 값을 저장한다.

Data Dequeue(Queue * pq);
// 저장순서가 가장 앞선 데이터를 삭제한다.
// 삭제된 데이터는 반환한다.
// 본 함수의 호출을 위해서는 데이터가 하나 이상 존재함이 보장되어야 한다.

Data QPeek(Queue * pq);
// 저장순서가 가장 앞선 데이터를 반환하되 삭제하지 않는다.
// 본 함수의 호출을 위해서는 데이터가 하나 이상 존재함이 보장되어야 한다.
```

이제 이 ADT를 기반으로 배열 기반, 연결 리스트 기반으로 구현해보자.

# 7-2 큐의 배열 기반 구현

큐에서는 중요한 두가지 함수가 있다. 바로 Enqueue, Dequeue이며 각각 큐에 데이터를 삽입하는 함수, 삭제하는 함수이다. <br>
가장 먼저 Enqueue를 살펴보자 아래의 그림을 통해 쉽게 볼 수 있다. <br>
<img src = "/res/Chapter7/Enqueue.JPG" width = 700 height = 400> <br>
큐의 머리를 가리키는 F는 그대로 있고 꼬리를 가리키는 R이 하나 증가하고 해당 위치에 데이터가 추가되는것을 알 수 있다. <br>

그렇다면 dequeue연산을 확인해보자. 배열로 큐를 만들 경우 F의 위치가 고정되는 방법, 움직이는 방법 2가지로 구분되는데 보통 움직이는 방법을 채택하며 이를 조금더 쉽게 사용하기 위해 원형 큐를 사용한다. 원형큐의 그림은 다음과 같다. <br>
<img src = "/res/Chapter7/CQueue.JPG" width = 500 height = 450> <br>
이 경우 한 칸을 비워두었기 때문에 F와 R이 같으면 Empty 상태이며 R이 가리키는 위치의 앞을 F가 가리키면 Full로 나타낼 수 있는 것이다. 그림은 각각 다음과 같다. <br>

<img src = "/res/Chapter7/Empty&Full.JPG">

다음은 헤더 파일이다. 이를 기반으로 CircularQueue.c를 구현해보자.<br>
``` C
#ifndef __AB_STACK_H__
#define __AB_STACK_H__

#define TRUE	1
#define FALSE	0
#define STACK_LEN	100

typedef int Data;

typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	int topIndex;
} ArrayStack;

typedef ArrayStack Stack;

void StackInit(Stack * pstack);
int SIsEmpty(Stack * pstack);

void SPush(Stack * pstack, Data data);
Data SPop(Stack * pstack);
Data SPeek(Stack * pstack);

#endif
}
```

이를 기준으로 작성한 CircularQueue.c는 다음과 같다. <br>
``` C
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
```

전체의 코드는 각각 다음과 같다. <br>
CircularQueue.h: ([C Language 코드](/Chapter7/Example/CircularQueue.h)) <br>
CircularQueue.c: ([C Language 코드](/Chapter7/Example/CircularQueue.c)) <br>
CircularQueueMain.c: ([C Language 코드](/Chapter7/Example/CircularQueueMain.c)) <br>

<hr>

# 큐의 연결 리스트 기반 구현
이번에는 큐를 연결 리스트 기반으로 구현하여 보자. 큐를 통해 구현하였으므로 바로 헤더파일을 살펴보자. <br>

``` C
#ifndef __LB_QUEUE_H__
#define __LB_QUEUE_H__

#define TRUE	1
#define FALSE	0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node * next;
} Node;

typedef struct _lQueue
{
	Node * front;
	Node * rear;
} LQueue;

typedef LQueue Queue;

void QueueInit(Queue * pq);
int QIsEmpty(Queue * pq);

void Enqueue(Queue * pq, Data data);
Data Dequeue(Queue * pq);
Data QPeek(Queue * pq);

#endif
```

위의 헤더파일을 기준으로 ListBaseQueue.c를 구현하면 다음과 같다. <br>
``` C
#include <stdio.h>
#include <stdlib.h>
#include "ListBaseQueue.h"

void QueueInit(Queue* pq) {
	pq->front = NULL;
	pq->rear = NULL;
}

int QIsEmpty(Queue* pq) {
	if (pq->front == NULL)
		return TRUE;
	else
		return FALSE;
}

void Enqueue(Queue* pq, Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	if (QIsEmpty(pq)) {
		pq->front = newNode;
		pq->rear = newNode;
	}
	else {
		pq->rear->next = newNode;
		pq->rear = newNode;
	}
}

Data Dequeue(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	Node* rNode = pq->front;
	Data rData = pq->front->data;

	pq->front = pq->front->next;
	free(rNode);

	return rData;
}

Data QPeek(Queue* pq) {
	if (QIsEmpty(pq)) {
		printf("Queue Memory Error!\n");
		exit(-1);
	}

	return pq->front->data;
}
```

전체의 코드는 각각 다음과 같다. <br>
ListBaseQueue.h: ([C Language 코드](/Chapter7/Example/ListBaseQueue.h)) <br>
ListBaseQueue.c: ([C Language 코드](/Chapter7/Example/ListBaseQueue.c)) <br>
ListBaseQueueMain.c: ([C Language 코드](/Chapter7/Example/ListBaseQueueMain.c)) <br>

<hr>

# 덱 (Deque)의 이해와 구현

덱은 큐와 비슷하지만 앞과 뒤로 삽입, 앞과 뒤로 삭제가 가능한 자료구조 이다. ADT를 살펴보자<br>

``` C
void DequeueInit(Deque * pdeq);
// 덱의 초기화를 진행한다.
// 덱 생성후 제일 먼저 호출되어야 하는 함수이다.

int DQIsEmpty(Deque * pdeq);
// 덱이 빈 경우 TRUE(1)을, 그렇지 않은 경우 FALSE(0)을 반환한다.

void DQAddFirst(Deque * pdeq, Data data);
// 덱의 머리에 데이터를 저장한다. data로 전달된 값을 저장한다.

void DQAddLast(Deque * pdeq, Data data);
// 덱의 꼬리에 데이터를 저장한다. data로 전달된 값을 저장한다.

Data DQRemoveFirst(Deque * pdeq);
// 덱의 머리에 위치한 데이터를 반환 및 소멸한다.

Data DQRemoveLast(Deque * pdeq);
// 덱의 꼬리에 위치한 데이터를 반환 및 소멸한다.

Data DQGetFirst(Deque * pdeq);
// 덱의 머리에 위치한 데이터를 소멸하지 않고 반환한다.

Data DQGetLast(Deque * pdeq);
// 덱의 꼬리에 위치한 데이터를 소멸하지 않고 반환한다.
```

이제 헤더파일을 보고 Deque.c를 구현해보자. <br>

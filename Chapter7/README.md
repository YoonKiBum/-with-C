# 7-1 큐의 이해와 ADT 정의 <br>
큐는 우리가 일상생활에서 흔히 경험할 수 있는 자료구조로 밥을 먹기 위해 줄을 서거나 은행 업무를 보기 위해 줄을 서는 행위를 표현하는 자료구조 이다.<br>
 <img src = "/res/Chapter7/Queue.JPG"><br>
위의 그림과 같으며 그림에서 보이듯이 오른쪽으로 in, 왼쪽으로 out을 하는 모습을 확인할 수 있다. <br>
실생활에서와 마찬가지로 먼저 온 사람이 먼저 나가고, 나중에 온 사람이 나중에 나가듯 FIFO(First In Fisrt Out) 구조의 자료구조 이다. <br>

그렇다면 큐의 ADT를 살펴보자. 다음과 같다. <br>
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
<img src = "/res/Chapter7/Enqueue.JPG">
큐의 머리를 가리키는 F는 그대로 있고 꼬리를 가리키는 R이 하나 증가하고 해당 위치에 데이터가 추가되는것을 알 수 있다. <br>

그렇다면 dequeue연산을 확인해보자. 배열로 큐를 만들 경우 F의 위치가 고정되는 방법, 움직이는 방법 2가지로 구분되는데 보통 움직이는 방법을 채택하며 <br>
이를 조금더 쉽게 사용하기 위해 원형 큐를 사용한다. 원형큐의 그림은 다음과 같다. <br>
<img src = "/res/Chapter7/CQueue.JPG">
이 경우 한 칸을 비워두었기 때문에 F와 R이 같으면 Empty 상태이며 R이 가리키는 위치의 앞을 F가 가리키면 Full로 나타낼 수 있는 것이다. <br>
그림은 각각 다음과 같다. <br>

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
ArrayBaseStack.h: ([C Language 코드](/Chapter6/Example/ArrayBaseStack.h)) <br>
ArrayBaseStack.c: ([C Language 코드](/Chapter6/Example/ArrayBaseStack.c)) <br>
ArrayBaseStackMain.c: ([C Language 코드](/Chapter6/Example/ArrayBaseStackMain.c)) <br>

<hr>

# 스택의 연결 리스트 기반 구현
앞서 스택을 배열로 구현하였는데 연결 리스트로도 구현할 수 있다. 단순하게 자료구조가 바뀐것 이외에는 개념적 단계에서의 구현에는  <br>
큰 차이가 없으므로 바로 헤더파일과 이를 통한 구현을 보일것이다. <br>

``` C
#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#define TRUE	1
#define FALSE	0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node * next;
} Node;

typedef struct _listStack
{
	Node * head;
} ListStack;


typedef ListStack Stack;

void StackInit(Stack * pstack);
int SIsEmpty(Stack * pstack);

void SPush(Stack * pstack, Data data);
Data SPop(Stack * pstack);
Data SPeek(Stack * pstack);

#endif
```

위의 헤더파일을 기준으로 ListBaseStack.c를 구현하면 다음과 같다. <br>
``` C
#include "ListBaseStack.h"
#include <stdio.h>
#include <stdlib.h>

void StackInit(Stack* pstack) {
	pstack->head = NULL;
}

int SIsEmpty(Stack* pstack) {
	if (pstack->head == NULL)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack* pstack, Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = pstack->head;
	pstack->head = newNode;
}

Data SPop(Stack* pstack) {
	if (SIsEmpty(pstack)) {
		printf("stack memory error!");
		exit(-1);
	}

	Data rdata;
	Node * rNode;

	rNode = pstack->head;
	rdata = pstack->head->data;
	
	pstack->head = pstack->head->next;

	free(rNode);

	return rdata;
}

Data SPeek(Stack* pstack) {
	if (SIsEmpty(pstack)) {
		printf("stack memory error!");
		exit(-1);
	}

	return pstack->head->data;
}
```

전체의 코드는 각각 다음과 같다. <br>
ListBaseStack.h: ([C Language 코드](/Chapter6/Example/ListBaseStack.h)) <br>
ListBaseStack.c: ([C Language 코드](/Chapter6/Example/ListBaseStack.c)) <br>
ListBaseStackMain.c: ([C Language 코드](/Chapter6/Example/ListBaseStackMain.c)) <br>

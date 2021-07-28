# 6-1 스택의 이해와 ADT 정의 <br>
스택은 자료구조중에 하나로서 흔히 박스를 쌓는 구조로 설명을 한다. 이를 그림으로 표현하면 다음과 같다.<br>
 <img src = "/res/Chapter6/stack.JPG" width = "240" height ="360"><br>
위의 그림을 보면 2, 4, 6, 8, 10 의 순서로 삽입을 한 형태이다. 먼저 들어온 2가 바닥에 있고 나중에 넣은 10이 위에 있음을 알 수 있다.<br>
이를 상자를 쌓았다고 가정해보자. 상자의 밑 부분 부터 뺄 수 없으므로 당연히 맨 위에 부분부터 뺄 수 있을 것이다. <br>
스택 역시 마찬가지이며 10 부터 뺼 수 있음을 알 수 있다. 이를 후입선출이라 하며 영어로 LIFO(Last In First Out)이다. <br>

그렇다면 스택의 ADT를 살펴보자. 다음과 같다. <br>
``` C
void StackInit(Stack * pstack);
// 스택의 초기화를 진행한다.
// 스택 생성 후 제일 먼저 호출되어야 하는 함수이다.

int SIsEmpty(Stack * pstack);
// 스택이 빈 경우 TRUE(1)을, 그렇지 않은 경우 FALSE(0)을 반환한다.

void SPush(Stack * pstack, Data data);
// 스택에 데이터를 저장한다. 매개변수 data로 전달된 값을 저장한다.

Data SPop(Stack * pstack);
// 마지막에 저장된 요소를 삭제한다.
// 삭제된 데이터는 반환이 된다.
// 본 함수의 호출을 위해서는 데이터가 하나 이상 존재함이 보장되어야 한다.

Data SPeek(Stack * pstack);
// 마지막에 저장된 요소를 반환하되 삭제하지 않는다.
// 본 함수의 호출을 위해서는 데이터가 하나 이상 존재함이 보장되어야 한다.
```

이제 이 ADT를 기반으로 배열 기반, 연결 리스트 기반으로 구현해보자.

# 배열 기반 스택 구현

스택에서 구현해야 하는 함수는 push, pop이 있고 이를 top이라는 스택의 가장 윗 부분을 담당하는 변수를 이용하여 구현한다. <br>
가장 중요한 함수는 push, pop으로 push의 경우 top을 한칸 올리고 top이 가리키는 위치에 데이터를 저장하고 <br>
pop의 경우 top이 가리키는 데이터를 반환하고, top을 아래로 한칸 내린다. <br>
push연산을 그림으로 표현하면 다음과 같다. <br>
<img src =  "/res/Chapter6/push.JPG">
확인할 수 있는 점은 top의 시작은 -1 이며 하나의 데이터가 들어올 때 0이 된다는 것이다. 처음에 A를 추가할 때 <br>
top이 하나 증가한 뒤 해당 top의 위치에 원소가 추가되는것을 확인할 수 있으며 이후로도 마찬가지 이다. <br>

pop연산역시 그림으로 표현하면 다음과 같다. <br>
<img src = "/res/Chapter6/pop.JPG">

다음은 헤더 파일이다. 이를 기반으로 ArrayBaseStack.c를 구현해보자.<br>
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

이를 기준으로 작성한 ArrayBaseStack.c는 다음과 같다. <br>
``` C
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
```

이번에는 조회를 살펴보자. 조회의 경우도 Fisrt, Next즉 두가지의 경우에 대한 함수가 존재한다.<br>
LFisrt의 경우 Head가 없기 때문에 tail이 가리키는 다음 노드를 Cur로 한 뒤 이를 반환한다. 그림으로 표현하면 다음과 같다.<br>
<img src = "/res/Chapter5/LFirst.JPG">
``` C
int LFirst(List* plist, Data* pdata) {
	if (plist->tail == NULL) { // 비어있는 경우
		return FALSE;
	}
	plist->before = plist->tail; // before가 tail을 가리키게 한다.
	plist->cur = plist->tail->next; // cur이 tail의 다음을 가리키게 한다

	*pdata = plist->cur->data; 
	return TRUE;
}
```
LNext의 경우도 단순히 before가 cur을 가리키게 하고 cur에 cur이 가리키는 다음 노드를 가리키게 하면 된다. <br>
그 후 cur이 가리키는 노드를 반환하면 된다.마찬가지로 그림으로 나타내면 다음과 같다. <br>
<img src = "/res/Chapter5/LNext.JPG">

``` C
int LNext(List* plist, Data* pdata) {
	if (plist->tail == NULL) { // 비어있는 경우
		return FALSE;
	}
	plist->before = plist->cur; // before가 cur을 가리키게 한다
	plist->cur = plist->cur->next; // cur이 cur의 다음을 가리키게 한다.

	*pdata = plist->cur->data;
	return TRUE;
}
```

이 두가지 함수 모두 리스트에 원소가 없을 경우에 대해서 처리가 필요한데 단순하게 ADT를 참조하여 노드가 존재하지 않으면<br>
False를 반환하면 된다.<br>

<hr>

이번에는 노드의 삭제에 대해서 알아보자. <br>
노드의 삭제의 경우 두가지의 경우가 존재하는데 삭제할 노드가 tail인 경우 또는 아닌경우 삭제할 노드가 tail인 경우 <br>
노드가 하나밖에 없는 경우 역시 추가로 고려를 해주어야 한다. 다음의 코드를 살펴보자.<br>
``` C
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
```
위에서 볼 수 있듯 삭제하려는 노드가 tail이 아닌 경우는 다음의 그림처럼 삭제를 진행하면 된다. <br>
<img src = "/res/Chapter5/LRemove.JPG">
그러나 삭제하려는 노드가 tail인 경우는 단순하게 tail을 하나 앞으로 이동시키면 된다. 단순히 plist->tail = plist->before;을 통해서 말이다. <br>

전체의 코드는 각각 다음과 같다. <br>
CLinkedList.h: ([C Language 코드](/Chapter5/Example/CLinkedList.h)) <br>
CLinkedList.c: ([C Language 코드](/Chapter5/Example/CLinkedList.c)) <br>
CLinkedListMain.c: ([C Language 코드](/Chapter5/Example/CLinkedListMain.c)) <br>

<hr>

# 5-2 양방향 연결 리스트

양방향 연결 리스트의 경우 앞서서 구현했던 단순 연결 리스트에서 좌측 혹은 우측을 연결하는 포인터 변수의 존재가 큰 차이점 이다. <br>
그렇다면 헤더파일과 그림을 보고 양방향 연결 리스트를 구현해보자. 헤더파일은 다음과 같다. <br>
``` C
#ifndef __DB_LINKED_LIST_H__
#define __DB_LINKED_LIST_H__

#define TRUE	1
#define FALSE	0

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node * next;
	struct _node * prev;
} Node;

typedef struct _dbLinkedList
{
	Node * head;
	Node * cur;
	int numOfData;
} DBLinkedList;

typedef DBLinkedList List;

void ListInit(List * plist);
void LInsert(List * plist, Data data);

int LFirst(List * plist, Data * pdata);
int LNext(List * plist, Data * pdata);
int LPrevious(List * plist, Data * pdata);

int LCount(List * plist);

#endif
```
<img src = "/res/Chapter5/DBLinkedList.JPG">
리스트의 초기화는 각각의 포인터 변수를 NULL로 초기화 하면 된다. 다음과 같다. <br>

``` C
void ListInit(List* plist) {
	plist->head = NULL;
	plist->cur = NULL;
	plist->numOfData = 0;
}
```

<hr>

삽입의 경우 2가지의 경우가 존재하는데 각각 리스트가 비어있을때, 비어있지 않을 때 이다. <br>
이를 코드로 작성하면 다음과 같다. <br>

``` C
void LInsert(List* plist, Data data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head;
	newNode->prev = NULL;
	plist->head = newNode;

	(plist->numOfData)++;
}
```

<hr>

데이터의 조회의 경우 양방향 연결 리스트의 특성으로 좌측, 우측을 모두 조회할 수 있다. <br>
이를 함수료 표현하면 각각 LFisrt, LNext, LPrevious 이며 다음과 같다.
```C
int LFirst(List* plist, Data* pdata) {
	if (plist->head == NULL)
		return FALSE;

	plist->cur = plist->head;
	*pdata = plist->head->data;
	return TRUE;
}

int LNext(List* plist, Data* pdata) {
	if (plist->head == NULL)
		return FALSE;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;
	return TRUE;
}

int LPrevious(List* plist, Data* pdata) {
	if (plist->head == NULL)
		return FALSE;

	plist->cur = plist->cur->prev;
	*pdata = plist->cur->data;
	return TRUE;
}
```

전체의 코드는 각각 다음과 같다. <br>
DBLinkedList.h: ([C Language 코드](/Chapter5/Example/DBLinkedList.h)) <br>
DBLinkedList.c: ([C Language 코드](/Chapter5/Example/DBLinkedList.c)) <br>
DBLinkedListMain.c: ([C Language 코드](/Chapter5/Example/DBCLinkedListMain.c)) <br>

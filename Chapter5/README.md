# 5-1 원형 연결 리스트 (Circular Linked List) <br>
단순 연결 리스트에서 마지막 노드가 첫 번째 노드를 가리켜서 원의 형태로 연결이 된 리스트를 *원형 연결 리스트* 라고 한다. <br>
이를 그림으로 나타내면 다음과 같다. <br>
 <img src = "/res/Chapter5/circular.PNG">

위의 그림에서 head나 tail에 새로운 노드 1을 추가한다고 가정하면 1 -> 2 -> 4 -> 6 -> 8 -> 1 .... 의 형태 혹은 <br>
2 -> 4 6 -> 8 ->  1 -> 2.... 즉 서로 같은 형태가 되므로 head, tail의 구분이 명확히 존재하지 않는다. <br>
유일한 차이점은 tail이 가리키는 노드가 다르다는 것 이다. 따라서 이를 머리에 추가하는 함수, 꼬리에 추가하는 함수는 각각 다음과 같다. <br>

``` C
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
그렇다면 헤더파일을 보고 양방향 연결 리스트를 구현해보자. 헤더파일은 다음과 같다. <br>
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

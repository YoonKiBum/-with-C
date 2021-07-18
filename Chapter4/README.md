# 4-1 연결 리스트의 개념적인 이해 <br>
먼저 연결리스트를 배우기에 앞서서 배열기반 리스트를 살펴보면 배열은 길이의 변경이 불가능하다는것을 알 수 있다. <br>
따라서 이러한 문제점을 해결한게 연결 리스트(Linked List) 이다. <br>
 
먼저 다음의 구조체를 살펴보자 <br>
``` C
typedef struct _node {
  int data; // 데이터를 담을 공간
  struct _node * next; // 연결의 도구
} Node;
```
이 Node 구조체를 이용하여 필요할 때마다 하씩 동적할당하여 데이터를 저장하고 이들을 배열처럼 연결할 수 있는 <br>
연결 리스트가 되는 것 이다. 여기에서 구조체 Node 변수를 노드라 하며 이를 그림으로 그리면 다음과 같다. <br>

노드 하나의 표현<br>
<img src = "/res/Chapter4/expression.PNG">

노드들의 연결 표현<br>
<img src = "/res/Chapter4/connection.PNG">

먼저 ADT를 살펴보자. ADT는 다음과 같다. <br>
``` C
void ListInit(List * plist); 
// 초기화할 리스트의 주소 값을 인자로 전달한다.
// 리스트 생성 후 제일 먼저 호출되어야 하는 함수이다.

void LInsert(List * plist, LData data);
// 리스트에 데이터를 저장한다. 매개변수 data에 전달된 값을 저장한다.

int LFirst(List * plist, LData * pdata);
// 첫 번째 데이터가 pdata가 가리키는 메모리에 저장된다.
// 데이터의 참조를 위한 초기화가 진행된다.
// 참조 성공 시 TRUE(1), 실패 시 FALSE(0) 반환

int LNext(List * plist, LData * pdata);
// 참조된 데이터의 다음 데이터가 pdata가 가리키는 메모리에 저장된다.
// 순차적인 참조를 위해서 반복 호출이 가능하다.
// 참조를 새로 시작하려면 먼저 LFirst함수를 호출해야 한다.
// 참조 성공 시 TRUE(1), 실패 시 FALSE(0) 반환

LData LRemove(List * plist);
// LFirst 또는 LNext 함수의 마지막 반환 데이터를 삭제한다.
// 삭제된 데이터는 반환된다.
// 마지막 반환 데이터를 삭제하므로 연이은 반복 호출을 허용하지 않는다.

int LCount(List * plist);
// 리스트에 저장되어 있는 데이터의 수를 반환한다.

void SetSortRule(List * plist, int (*comp)(LData d1, LData d2));
// 리스트에 정렬의 기준이 되는 함수를 등록한다.
```

배열 리스트와 비교해보면 SetSortRule함수가 추가된 것을 볼 수 있으며 이는 Head에 추가할 지 Tail에 추가할 지 정하는 것이다. <br>
장단점은 각각 다음과 같다. <br>
<img src = "/res/Chapter4/table.PNG"><br>

또한 SetSortRule 함수의 매개변수를 보면 함수 포인터가 매개변수로 존재하는것을 알 수 있는데 반환형이 int, LData형 2개를 전달받는 함수의
주소값을 전달하는 것이다. 예를 들면 다음의 함수의 주소값이 매개변수로 전달될 수 있다.
``` C
int WhoIsPrecede(LData d1, LData d2) {
	if (d1 < d2)
		return 0; // d1이 정렬 순서가 앞서는 경우
	else
		return 1; // d2가 정렬 순서가 앞서는 경우
}
```
<hr>

먼저 다음의 형태의 기본적인 노드의 연결상태를 보고 단점을 파악해보자. <br>
<img src = "/res/Chapter4/addTail.PNG" width = "800" height = "400"><br>
이 경우 노드의 추가 및 삭제 또는 조회의 방법에서 첫 번째 노드와 두 번째 노드의 연결에 차이가 있다. 따라서 이를 방지하기 위해 <br>
헤드의 바로 다음에 dummy node를 넣어 어떤 위치에 있던 방법을 일관화 할 수 있다.<br> 

<hr>

이제 연결 리스트를 구현해보자. 다음의 구조체를 기반으로 정의한다. <br>
``` C
typedef struct _linkedList {
	Node * head;			  // 더미 노드를 가리키는 멤버
	Node * cur;			  // 참조 및 삭제를 돕는 멤버
	Node * before;			  // 삭제를 돕는 멤버
	int numOfData;			  // 저장된 데이터의 수를 기록하기 위한 멤버
	int (*comp)(LDatat d1, LData d2); // 정렬의 기준을 등록하기 위한 멤버
} LinkedList;
```

헤더 파일은 다음과 같다. DLinkedList.h: ([C Language 코드](/Chapter4/Example/DLinkedList.h)) <br>
이를 기준으로 초기화와 삽입을 살펴보자. 초기화는 다음과 같다. <br>

``` C
void ListInit(List * plist) {
	plist->head = (Node*)malloc(sizeof(Node));	// 더미 노드의 생성
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}
```
<img src = "/res/Chapter4/init.PNG"><br>
노드를 새로 추가하기 위한 함수는 다음과 같다. <br>
``` C
void LInsert(List * plist, LData data) {
	if(plist->comp == NULL)		// 정렬 기준이 없다면
		FInsert(plist, data);   // 머리에 노드를 추가
	else				// 정렬 기준이 있다면
		SInsert(plist, data);   // 정렬 기준에 의하여 노드를 추가
}
```

여기에서 볼 수 있는것은 comp 즉 노드를 정렬하기 위한 기준이 마련되어있느냐에 따라 FInsert, SInsert로 나뉜다는 것이다. <br>
그러나 이들은 내부적으로 정의된 함수이기에 사용자가 직접 호출할 수 없는 함수이다. 먼저 FInsert는 다음과 같다. <br>
``` C
void FInsert(List * plist, LData data) {
	Node * newNode = (Node*)malloc(sizeof(Node));		// 새 노드 저장
	newNode->data = data;					// 새 노드에 데이터 저장
	
	newNode->next = plist->head->next; 			// 새 노드가 다른 노드를 가리키게 함
	plist->head->next = newNode;				// 더미 노드가 새 노드를 가리키게 함
	
	(plist->numOfData)++;					// 저장된 노드의 수를 하나 증가시킴
)
```
그림으로 보면 다음과 같다. <br>
<img src = "/res/Chapter4/Finsert.PNG"><br>

<hr>

데이터 조회 역시 배열 리스트의 그것과 비슷하지만 before과 Dummy node가 존재한다는것에서 차이가 있다. <br>
먼저 LFirst 함수를 보자.
``` C
int LFisrt(List * plist, LData * pdata) {
	if(plist->head->next == NULL)		// 더미 노드가 NULL을 가리킨다면
		return FALSE;
	plist->before = plist->head;		// before는 더미 노드를 가리키게 함
	plist->cur = plist->head->next; 	// cur은 첫번째 노드를 가리키게 함
	
	*pdata = plist->cur->data;		// 첫 번째 노드의 데이터를 전달
	return TRUE;				// 데이터 반환 성공!
}
```
역시 그림으로 나타내면 다음과 같다. <br>
<img src = "/res/Chapter4/LFirst.PNG"><br>

LNext 역시를 보면 다음과 같다. <br>
``` C
int LFisrt(List * plist, LData * pdata) {
	if(plist->cur->next == NULL)		// cur이 NULL을 가리킨다면
		return FALSE;
	plist->before = plist->cur;		// cur이 가리키던 것을 before가 가리킴
	plist->cur = plist->cur->next; 		// cur은 그 다음 노드를 가리킴
	
	*pdata = plist->cur->data;		// cur이 가리키는 노드의 데이터 전달
	return TRUE;				// 데이터 반환 성공!
}
```
역시 그림으로 나타내면 다음과 같다. <br>
<img src = "/res/Chapter4/LNext.PNG"><br>

<hr>

노드의 삭제 역시 배열 기반 리스트의 삭제와 비슷하다. <br>
``` C
LData LRemove(List * plist) {
	Node * rpos = plist->cur;		// 소멸 대상의 주소 값을 rpos에 저장
	LData rdata = rpos->data;		// 소멸 대상의 데이터를 rdata에 저장
	
	plist->before->next = plist->cur->next;	// 소멸 대상을 리스트에서 제거
	plist->cur = plist->before;		// cur이 가리키는 위치를 재조정!
	
	free(rpos);				// 리스트에서 제거된 노드 소멸
	(plist->numOfData)--;			// 저장된 데이터의 수 하나 감소
	return rdata;				// 제거된 노드의 데이터 반환
}
```
<img src = "/res/Chapter4/LRemove.PNG"><br>

전체의 코드는 각각 다음과 같다. <br>
DLinkedList.h: ([C Language 코드](/Chapter4/Example/DLinkedList.h)) <br>
DLinkedList.c: ([C Language 코드](/Chapter4/Example/DLinkedList.c)) <br>
DLinkedListMain.c: ([C Language 코드](/Chapter4/Example/DLinkedListMain.c)) <br>


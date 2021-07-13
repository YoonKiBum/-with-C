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
이 Node 구조체를 이용하여 필요할 때미디 하니씩 동적할당하여 데이터를 저장하고 이들을 배열처럼 연결할 수 있는 <br>
연결 리스트가 되는 것 이다. 여기에서 구조체 Node 변수를 노드라 하며 이를 그림으로 그리면 다음과 같다. <br>

노드 하나의 표현<br>
<img src = "/res/Chapter4/expression.PNG">

노드들의 연결 표현<br>
<img src = "/res/Chapter4/connection.PNG">

이제 노드의 삽입에 대해서 배워보자.

<hr>

먼저 간략하게 알아보자. 다음의 3가지 포인터 변수들이 존재한다. <br>
``` C
Node * head = NULL; // 리스트의 머리를 가리키는 포인터 변수
Node * tail = NULL; // 리스트의 꼬리를 가리키는 포인터 변수
Node * cur = NULL;  // 저장된 데이터의 조회에 사용되는 포인터 변수
```
초기 상황을 그림으로 표현하면 다음과 같다. <br>
<img src = "/res/Chapter4/initial.PNG" width = "800" height = "300"><br>
이 후 다음의 세 문장에 의해 노드가 생성 및 초기화가 된다.
``` C
newNode = (Node*)malloc(sizeof(Node));	// 노드의 생성
newNode->data = readData;		// 노드에 데이터 저장
newNode->newxt = NULL;			// 노드의 next를 NULL로 초기화
```
생성 및 초기화 직후 그림으로 표현하면 다음과 같다. (새로운 노드가 5라고 가정)<br>
<img src = "/res/Chapter4/newNode.PNG" width = "800" height = "500"><br>
이 후 포인터 변수 head가 NULL을 가리키므로 (첫 노드이므로) head는 newNode를 가리키게 되고 tail역시 노드의 <br>
가르키므로 다음의 코드 및 그림과 같다.<br>
``` C
if(head == NULL)
	head = newNode;
else
	tail->next = newNode;

tail = newNode;
```
<img src = "/res/Chapter4/headTail.PNG" width = "800" height = "400"><br>
초기과정은 위와 같고 그 이후로 두번째 이후부터의 노드에서는 다음과 같다. 먼저 다음의 코드를 보자. <br>
``` C
if(head == NULL)
	head = newNode;
else
	tail->next = newNode;

tail = newNode;
```
즉 head가 가리키는 것이 NULL이 아니므로 tail->next = newNode;를 실행하면 다음과 같다.(새로 추가한 노드는 10이라 가정한다.)
<img src = "/res/Chapter4/addTail.PNG" width = "800" height = "400"><br>


 # 3-2 배열을 이용한 리스트의 구현<br>
리스트에는 크게 두가지의 종류가 있고 이는 다음과 같다. <br>
  - 순차 리스트
  - 연결 리스트

리스트 자료구조는 *데이터를 나란히 저장한다는 점과 중복 데이터의 저장을 허용한다*는 큰 특성이 있다. <br>
이제 위의 ADT를 기반으로 main함수를 작성하면 다음과 같다.<br>
ListMain.c: ([C Language 코드](/Chapter3/Example/ListMain.c))
``` C
#include <stdio.h>
#include "ArrayList.h"

int main(void)
{
	/*** ArrayList의 생성 및 초기화 ***/
	List list;
	int data;
	ListInit(&list);

	/*** 5개의 데이터 저장 ***/
	LInsert(&list, 11);  LInsert(&list, 11);
	LInsert(&list, 22);  LInsert(&list, 22);
	LInsert(&list, 33);

	/*** 저장된 데이터의 전체 출력 ***/
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &data))    // 첫 번째 데이터 조회
	{
		printf("%d ", data);

		while (LNext(&list, &data))    // 두 번째 이후의 데이터 조회
			printf("%d ", data);
	}
	printf("\n\n");

	/*** 숫자 22을 탐색하여 모두 삭제 ***/
	if (LFirst(&list, &data))
	{
		if (data == 22)
			LRemove(&list);

		while (LNext(&list, &data))
		{
			if (data == 22)
				LRemove(&list);
		}
	}

	/*** 삭제 후 저장된 데이터 전체 출력 ***/
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while (LNext(&list, &data))
			printf("%d ", data);
	}
	printf("\n\n");
	return 0;
}
}
```
위의 ListMain.c를 기반으로 하는 ArrayList.h, ArrayList.c도 다음과 같다.<br>
ArrayList.h: ([C Language 코드](/Chapter3/Example/ArrayList.h))
``` C
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE    1
#define FALSE   0

/*** ArrayList의 정의 ****/
#define LIST_LEN        100
typedef int LData;

typedef struct __ArrayList
{
        LData arr[LIST_LEN];
        int numOfData;
        int curPosition;
} ArrayList;


/*** ArrayList와 관련된 연산들 ****/
typedef ArrayList List;

void ListInit(List* plist);
void LInsert(List* plist, LData data);

int LFirst(List* plist, LData* pdata);
int LNext(List* plist, LData* pdata);

LData LRemove(List* plist);
int LCount(List* plist);

#endif
```
ArrayList.c: ([C Language 코드](/Chapter3/Example/ArrayList.c))
``` C
#include <stdio.h>
#include "ArrayList.h"

void ListInit(List* plist)
{
        (plist->numOfData) = 0;
        (plist->curPosition) = -1;
}

void LInsert(List* plist, LData data)
{
        if (plist->numOfData > LIST_LEN)
        {
                puts("저장이 불가능합니다.");
                return;
        }

        plist->arr[plist->numOfData] = data;
        (plist->numOfData)++;
}

int LFirst(List* plist, LData* pdata)
{
        if (plist->numOfData == 0)
                return FALSE;

        (plist->curPosition) = 0;
        *pdata = plist->arr[0];
        return TRUE;
}

int LNext(List* plist, LData* pdata)
{
        if (plist->curPosition >= (plist->numOfData) - 1)
                return FALSE;

        (plist->curPosition)++;
        *pdata = plist->arr[plist->curPosition];
        return TRUE;
}

LData LRemove(List* plist)
{
        int rpos = plist->curPosition;
        int num = plist->numOfData;
        int i;
        LData rdata = plist->arr[rpos];

        for (i = rpos; i < num - 1; i++)
                plist->arr[i] = plist->arr[i + 1];

        (plist->numOfData)--;
        (plist->curPosition)--;
        return rdata;
}

int LCount(List* plist)
{
        return plist->numOfData;
}
```

위의 코드들을 자세히 살펴보면 배열기반 리스트의 삭제가 복잡한것을 알 수 있다. <br>
먼저 배열 리스트의 데이터 삭제를 살펴보자<br>
배열의 특성상, 그리고 리스트의 특성상 데이터가 나란히 존재해야 하므로 다음의 그림처럼 되는것을 확인할 수 있다.<br>
<img src = "/res/Chapter3/ArrayListRemove.PNG">

또한 가장 최근에 참조가 이루어진 데이터의 인덱스 정보를 담는 변수 curPosition 역시 참조하던 데이터가 삭제되면<br>
앞의 데이터를 참조해야 한다. 이는 다음의 그림과 같다. <br>
<img src = "/res/Chapter3/ArrayListCurposition.PNG"><br>
실제로 리스트에는 예시의 정수 이외에 다른 자료들도 들어간다. 이번에는 그렇다면 구조체 변수의 주소 값을 저장하여 보자<br>
구조체는 다음과 같다.<br>
``` C
typedef struct _point {
	int xpos; // x좌표
	int ypos; // y좌표
} Point;
```
이 Point 구조체를 위한 Point.h, Point.c는 각각 다음과 같다.<br>
Point.h: ([C Language 코드](/Chapter3/Example/Point.h))
Point.c: ([C Language 코드](/Chapter3/Example/Point.c))

이 후 ArrayList.h, ArrayList.c를 기반으로 위의 Point 구조체를 저장할 수 있도록 하면 이 과정에서 <br>
헤더파일은 변경이 되어도 되지만 소스파일은 변경이 되면 안된다.<br>
헤더파일에서 달라진 점은 ``` typedef int LData; ``` 에서 ``` typedef Point * LData; ``` 으로 변경되었다.<br>
또한 ArrayList.h의 선언문에 ``` #include "Point.h"``` 를 추가한다.
이제 main함수는 다음과 같다.<br>
PointListMain.c: ([C Language 코드](/Chapter3/Example/PointListMain.c))
``` C
#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Point.h"

int main(void) {
	List list;
	Point comPos;
	Point* ppos;

	ListInit(&list);

	// 4개의 데이터 저장
	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 1);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 2, 2);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 1);
	LInsert(&list, ppos);

	ppos = (Point*)malloc(sizeof(Point));
	SetPointPos(ppos, 3, 2);
	LInsert(&list, ppos);

	// 저장된 데이터의 출력
	printf("현재 데이터의 수는 : %d \n", LCount(&list));

	if (LFirst(&list, &ppos)) {
		ShowPosition(ppos);

		while (LNext(&list, &ppos)) {
			ShowPosition(ppos);
		}
	}
	printf("\n");

	// xpos가 2인 모든 데이터 삭제
	comPos.xpos = 2;
	comPos.ypos = 0;

	if (LFirst(&list, &ppos)) {
		if (PointComp(ppos, &comPos) == 1) {
			ppos = LRemove(&list);
			free(ppos);
		}

		while (LNext(&list, &ppos)) {
			if (PointComp(ppos, &comPos) == 1) {
				ppos = LRemove(&list);
				free(ppos);
			}
		}
	}

	// 삭제 후 남은 데이터 전체 출력
	printf("현재 데이터의 수는 : %d \n", LCount(&list));

	if (LFirst(&list, &ppos)) {
		ShowPosition(ppos);

		while (LNext(&list, &ppos)) {
			ShowPosition(ppos);
		}
	}
	printf("\n");

	return 0;
}
```


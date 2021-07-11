 # 3-1 추상 자료형: Abstract Data Type <br>
      
추상 자료형은 간단히 ADT라고 불리며 기능만 언급하며 기능의 과정은 포함하지 않는다.<br>
이번에 배울 배열기반 리스트 자료구조의 ADT는 다음과 같다.<br>
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
```
<hr>

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


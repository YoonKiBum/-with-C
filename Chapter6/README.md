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

전체의 코드는 각각 다음과 같다. <br>
ArrayBaseStack.h: ([C Language 코드](/Chapter6/Example/ArrayBaseStack.h)) <br>
ArrayBaseStack.c: ([C Language 코드](/Chapter6/Example/ArrayBaseStack.c)) <br>
ArrayBaseStackMain.c: ([C Language 코드](/Chapter6/Example/ArrayBaseStackMain.c)) <br>

<hr>

# 스택의 연결 리스트 기반 구현
앞서 스택을 배열로 구현하였는데 연결 리스트로도 구현할 수 있다. 단순하게 자료구조가 바뀐것 이외에는 개념적 단계에서의 구현에는  <br>
큰 차이가 없으므로 바로 헤더파일과 이를 통한 구현을 보일것이다. <br>



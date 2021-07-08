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

 # 3-2 배열을 이용한 리스트의 구현<br>
리스트에는 크게 두가지의 종류가 있고 이는 다음과 같다. <br>
  - 순차 리스트
  - 연결 리스트

리스트 자료구조는 데이터를 나란히 저장한다는 점과 중복 데이터의 저장을 허용한다는 큰 특성이 있다. <br>
이제 위의 ADT를 기반으로 main함수를 작성하면 다음과 같다.<br>
ListMain.c: ([C Language 코드](/Chapter3/Example/ListMain.c))

<img src = "/res/Chapter2/recursive.PNG"><br>
Recursive 함수를 실행하는 중간에 다시 Recursive 함수가 호출되면, Recursive 함수의 복사본을 하나 더 만들어서 복사본을 실행하게 된다.<br>
재귀함수의 중요한 점 *탈출 조건을 설정해야 한다.*<br>
위의 코드의 경우 탈출 조건이 없으므로 무한 호출이 된다. 다음의 코드에서는 탈출 조건을 설정하여 3번 출력이 되는것을 확인할 수 있다. <br>
RecursiveFunc.c: ([C Language 코드](/Chapter2/Example/RecursiveFunc.c))
``` C
#include <stdio.h>

void Recursive(int num) {
	if (num <= 0) // 탈출 조건
		return;
	printf("Recursive call! %d \n", num);
	Recursive(num - 1);
}

int main(void) {
	Recursive(3);
	return 0;
}
```
재귀함수의 예시로 팩토리얼 함수를 들 수 있다. 먼저 팩토리얼의 수식을 쓰면 다음과 같다.<br>
<img src = "/res/Chapter2/factorial.PNG"><br>
이를 코드적인 관점에서 생각해보면 n이 1인 경우는 1을 반환하고 그 이외의 경우는 n-1을 반환하면 되는 것이다.<br>
코드로 작성하면 다음과 같다. <br>
``` C
#include <stdio.h>
 
int Factorial(int num) {
    if (num == 0) // 탈출 조건
        return 1;
    return num * Factorial(num - 1);
}
 
int main(void) {
    printf("1! = %d\n", Factorial(1));
    printf("2! = %d\n", Factorial(2));
    printf("3! = %d\n", Factorial(3));
    printf("4! = %d\n", Factorial(4));
    printf("9! = %d\n", Factorial(9));
    return 0;
}
```
RecursiveFactorial.c: ([C Language 코드](/Chapter2/Example/RecursiveFactorial.c))
<hr>

# 2-2 재귀의 활용
재귀의 또다른 예로 피보나치 함수가 존재. 피보나치가 그것이다. 이를 코드 적인 관점에서 생각하면<br> 
n이 1인 경우는 0, 2인 경우는 1로 설정하고 그 외의 경우는 n-1번째 수+ n-2번째 수로 하면 된다. 코드로 작성하면 다음과 같다.
``` C
#include <stdio.h>
 
int Fibo(int num) {
    if (num == 1) // 1번째인 경우 0 반환
        return 0;
    else if (num == 2) // 2번째인 경우 1 반환
        return 1;
    else // 그 외의 경우
        return Fibo(num-1) + Fibo(num-2);
}
 
int main(void) {
    for (int i = 1; i <= 15; i++) { // 피보나치 수 15개 출력
        printf("%d ", Fibo(i));
    }
    return 0;
}
```
FibonacciFunc.c: ([C Language 코드](/Chapter2/Example/FibonacciFunc.c))<br>
앞서서 다루었던 이진 탐색의 경우 반복문을 통해 작성하였다. <br>
이 또한 방금 배운 재귀를 이용하여 작성할 수 있다.반복문에서는 while(first <= last) 의 조건을 통해 구현하였으니 이를 탈출 조건으로 작성하면 된다. <br>
소스코드로 나타내면 다음과 같다.
``` C
#include <stdio.h>
 
int BSearchRecur(int arr[], int first, int last, int target) {
    int mid;
    if (first > last) // 탈출조건
        return -1;
    
    mid = (first + last) / 2;
    if (arr[mid] == target) // 찾은 경우 해당 위치의 인덱스 반환
        return mid;
    else if (arr[mid] > target) // mid의 값이 target보다 큰 경우 좌측에서 탐색해야함
        return BSearchRecur(arr, first, mid - 1, target);
    else // mid의 값이 target보다 작은 경우 우측에서 탐색해야함
        return BSearchRecur(arr, mid + 1, last, target);
}
 
int main(void) {
    int arr[] = { 1, 3, 5, 7, 9 };
    int idx;
 
    idx = BSearchRecur(arr, 0, sizeof(arr) / sizeof(int) - 1, 5);
    if (idx == -1)
        printf("탐색 실패 \n");
    else
        printf("타겟의 인덱스는 %d 입니다.\n", idx);
 
    idx = BSearchRecur(arr, 0, sizeof(arr) / sizeof(int) - 1, 8);
    if (idx == -1)
        printf("탐색 실패 \n");
    else
        printf("타겟의 위치는 %d 입니다.\n", idx);
 
    return 0;
}
```
RecursiveBinarySearch.c: ([C Language 코드](/Chapter2/Example/RecursiveBinarySearch.c))

# 2-3 하노이 타워: The Tower of Hanoi]
알아야 할 것은 원반은 한 번에 하나만 옮길 수 있고 작은 원반 위에 큰 원반이 놓여서는 안 된다는 것이다.<br>
이를 자세하게 살펴보면 하노이 역시 일련의 과정을 반복하므로 재귀를 통해 구현할 수 있다는 것을 알 수 있다.<br>
``` C
#include <stdio.h>
 
void HanoiTowerMove(int num, char from, char by, char to) {
    if (num == 1)
        printf("원반 1을 %c에서 %c로 이동\n", from, to);
    else {
        HanoiTowerMove(num - 1, from, to, by); 
        printf("원반 %d를 %c에서 %c로 이동\n", num, from, to); 
        HanoiTowerMove(num - 1, by, from, to);
    }
}
 
int main(void) {
    HanoiTowerMove(3, 'A', 'B', 'C');
    return 0;
}
```
HanoiTowerSolu.c: ([C Language 코드](/Chapter2/Example/HanoiTowerSolu.c))

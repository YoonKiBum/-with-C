 # 2-1 함수의 재귀적 호출의 이해<br>
      
재귀함수란 함수 내에서 자기 자신을 다시 호출하는 함수를 말하며 동작과정은 다음과 같다.<br>
먼저 다음의 재귀함수 코드를 보자.<br>
``` C
void Recursive(void) {
    printf("Recursive call! \n");
    Recursive();
}
```
이를 그림으로 표현하면 다음과 같다.<br>
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

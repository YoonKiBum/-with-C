 # 재귀함수란?<br>
      
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

# LinearSearch.c
LinerSearch.c: ([C Language 코드](/Chapter1/Example/LinearSearch.c))<br>
이 경우 최악의 시간복잡도는 O(N)이다. 최선, 평균, 최악이 있지만 최악을 기준으로 잡는다.<br>
이번에는 이진 탐색(Binary Search)알고리즘을 보자. 순차 탐색에 비해 좋은 성능을 내지만 정렬이 되어있어야 한다는
제약 조건이 존재한다.<br>


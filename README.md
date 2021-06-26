# 자료구조 

## 1. 자료구조와 알고리즘의 이해
  - 1.1. 자료구조에 대한 기본적인 이해
  - 1-2. 알고리즘의 성능 분석 방법
    - 시간 복잡도(Time Complexity)와 공간 복잡도(Space Complexity)<br>
      시간 복잡도는 속도에 관한것이며 공간 복잡도는 메모리 사용량에 관한 것이다. 시간복잡도는 연산횟수로 구한다.<br> 
      <img src = "/res/Chapter1/graph.PNG"><br>
      데이터의 개수가 n이하는 알고리즘 A가 유리하고 n이상은 알고리즘 B가 유리한것을 확인할 수 있다.<br> 
      따라서 상황에 맞게 적절한 알고리즘을 택해야 한다. 다음의 코드를 살펴보자. <br>
      LinerSearch.c: ([C Language 코드](/Chapter1/Example/LinearSearch.c))<br>
      이 경우 최악의 시간복잡도는 O(n)이다. 최선, 평균, 최악이 있지만 최악을 기준으로 잡는다.<br>
      이번에는 이진 탐색(Binary Search)알고리즘을 보자. 순차 탐색에 비해 좋은 성능을 내지만 정렬이 되어있어야 한다는<br>
      제약 조건이 존재한다.<br>
      <img src = "/res/Chapter1/BinarySearch.PNG"><br>
      BinarySearch.c: ([C Language 코드](/Chapter1/Example/BinarySearch.c))<br>

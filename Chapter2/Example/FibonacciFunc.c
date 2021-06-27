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

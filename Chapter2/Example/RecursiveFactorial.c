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

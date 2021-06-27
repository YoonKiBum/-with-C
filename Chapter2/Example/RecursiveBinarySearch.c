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

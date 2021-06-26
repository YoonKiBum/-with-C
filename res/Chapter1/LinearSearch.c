#include <stdio.h>

int LSearch(int arr[], int len, int target) { // Linear Search 함수
	for (int i = 0; i < len; i++) {
		if (arr[i] == target) // 찾으면 해당 위치의 인덱스 반환
			return i;
	}
	return -1;
}
int main(void) {
	int arr[] = { 2, 5, 3, 1, 9 };
	int idx;

	idx = LSearch(arr, sizeof(arr) / sizeof(int), 9);
	if (idx == -1) 
		printf("탐색 실패\n");
	else 
		printf("타겟 인덱스: %d \n", idx);

	idx = LSearch(arr, sizeof(arr) / sizeof(int), 6);
	if (idx == -1)
		printf("탐색 실패\n");
	else
		printf("타겟 인덱스: %d \n", idx);

	return 0;
}

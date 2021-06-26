#include <stdio.h>

int BSearch(int arr[], int len, int target) {
	int first = 0;
	int last = len - 1;
	int mid;

	while (first <= last) { // fist와 last가 뒤집어지면 종료
		mid = (first + last) / 2;
		if (arr[mid] == target)
			return mid;
		else if (arr[mid] > target) // 중간 값이 target보다 큰 경우
			last = mid - 1; // mid 좌측에서 탐색 진행
		else // 중간 값이 target보다 작은 경우
			first = mid + 1;
	}
	return -1; // 탐색하지 못한 경우
}

int main(void) {
	int arr[] = { 1, 3, 5, 7, 9, 11 };
	int idx;

	idx = BSearch(arr, sizeof(arr) / sizeof(int), 7);
	if (idx == -1)
		printf("탐색 실패 \n");
	else
		printf("타겟 인덱스 위치: %d \n", idx);

	idx = BSearch(arr, sizeof(arr) / sizeof(int), 8);
	if (idx == -1)
		printf("탐색 실패 \n");
	else
		printf("타겟 인덱스 위치: %d \n", idx);

	return 0;
}

#include <stdio.h>
#include "ArrayList.h"

int main(void) {
	// 리스트 초기화
	List list;
	ListInit(&list);
	int data;

	// 리스트에 1부터 9까지 삽입
	for (int i = 0; i < 9; i++) {
		LInsert(&list, (i + 1));
	}

	// 리스트에 저장된 값 순차적으로 참조 후 그 합을 계산하여 출력
	int total = 0;
	if (LFirst(&list, &data)) {
		total += data;
		while (LNext(&list, &data)) {
			total += data;
		}
	}
	printf("리스트 내의 모든 원소들의 합 : %d\n", total);

	// 리스트에 저장된 값에서 2의 배수와 3의 배수에 해당하는 값 모두 삭제
	if (LFirst(&list, &data)) {
		if (data % 2 == 0 || data % 3 == 0)
			LRemove(&list);
		while (LNext(&list, &data)) {
			if (data % 2 == 0 || data % 3 == 0)
				LRemove(&list);
		}
	}

	printf("2의 배수와 5의 배수를 제거 합니다.\n");
	if (LFirst(&list, &data)) {
		printf("%d ", data);
		while (LNext(&list, &data)) {
			printf("%d ", data);
		}
	}
	return 0;
}

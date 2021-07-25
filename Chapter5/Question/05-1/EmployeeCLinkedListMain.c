#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "EmployeeInfo.h"
#include "CLinkedList.h"

Employee* ShowWhoIsNext(List* plist, char name[], int day) {
	Employee* e;
	int num = LCount(plist);
	LFirst(plist, &e);
	bool flag = FALSE;

	if (strcmp(e->name, name) != 0) { // 처음이름이랑 같지 않은 경우
		for (int i = 0; i < num-1; i++) { // 전체 수에서 하나 뺀 만큼 조회
			LNext(plist, &e);
			if (strcmp(e->name, name) == 0)
				flag = TRUE;
				break;
		}
		if (flag == FALSE) // 전체 다 돌려도 탐색하지 못한 경우
			return NULL;
	}

	for (int i = 0; i < day; i++) {
		LNext(plist, &e);
	}

	return e;
}

void ShowEmployee(Employee* emp) {
	printf("일할 사람은 %s 입니다.\n", emp->name);
	printf("일할 사람의 사번은 %d 입니다.\n", emp->empNum);
}


int main(void) {
	CList list;
	Employee * emp;

	ListInit(&list); // 초기화

	// tail에 데이터 추가
	emp = (Employee*)malloc(sizeof(Employee));
	emp->empNum = 1;
	strcpy(emp->name, "가가가");
	LInsert(&list, emp);

	// tail에 데이터 추가
	emp = (Employee*)malloc(sizeof(Employee));
	emp->empNum = 2;
	strcpy(emp->name, "나나나");
	LInsert(&list, emp);

	// tail에 데이터 추가
	emp = (Employee*)malloc(sizeof(Employee));
	emp->empNum = 3;
	strcpy(emp->name, "다다다");
	LInsert(&list, emp);

	// tail에 데이터 추가
	emp = (Employee*)malloc(sizeof(Employee));
	emp->empNum = 4;
	strcpy(emp->name, "라라라");
	LInsert(&list, emp);
		
	// 현재 상태
	// 가가가 -> 나나나 -> 다다다 -> 라라라 -> 가가가 -> 나나나 -> .....

	// 가가가 뒤로 3일 뒤 당직자
	emp = ShowWhoIsNext(&list, "가가가", 3);
	ShowEmployee(emp);

	// 나나나 뒤로 10일 뒤 당직자
	emp = ShowWhoIsNext(&list, "가가가", 10);
	ShowEmployee(emp);

	// 할당된 메모리 전체 소멸
	if (LFirst(&list, &emp)) {
		free(emp);

		for (int i = 0; i < LCount(&list) - 1; i++)
			if(LNext(&list, &emp))
				free(emp);
	}

	return 0;
}



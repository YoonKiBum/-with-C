#include <stdio.h>
#include "ArrayList.h"
#include "NameCard.h"

int main(void) {
	List list;
	ListInit(&list);
	NameCard* card;
	
	card = MakeNameCard("김김김", "010-0000-0000");
	LInsert(&list, card);

	card = MakeNameCard("이이이", "010-1111-1111");
	LInsert(&list, card);

	card = MakeNameCard("박박박", "010-2222-2222");
	LInsert(&list, card);

	// 전화번호 조회
	if (LFirst(&list, &card)) {
		if (NameCompare(card, "이이이") == 0) {
			ShowNameCardInfo(card);
		}
		else {
			while (LNext(&list, &card)) {
				if (NameCompare(card, "이이이") == 0) {
					ShowNameCardInfo(card);
					break;
				}
			}
		}
	}

	// 전화번호 변경
	if (LFirst(&list, &card)) {
		if (NameCompare(card, "이이이")==0) {
			ChagePhoneNum(card, "010-3333-3333");
		}
		else {
			while (LNext(&list, &card)) {
				if (NameCompare(card, "이이이")==0) {
					ChagePhoneNum(card, "010-3333-3333");
					break;
				}
			}
		}
	}

	// 전화번호 삭제
	if (LFirst(&list, &card)) {
		if (NameCompare(card, "김김김")==0) {
			LRemove(&list);
		}
		else {
			while (LNext(&list, &card)) {
				if (NameCompare(card, "김김김")==0) {
					LRemove(&list);
					break;
				}
			}
		}
	}

	// 출력
	if (LFirst(&list, &card)) {
		ShowNameCardInfo(card);
		while (LNext(&list, &card)) {
			ShowNameCardInfo(card);
		}
	}
	return 0;
}

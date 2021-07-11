#ifndef __POINT_H__
#define __POINT_H__

typedef struct _point {
	int xpos;
	int ypos;
} Point;

// Point 변수의 xpos, ypos 값 설장
void SetPointPos(Point* ppos, int xpos, int ypos);

// Point 변수의 xpos, ypos정보 출력
void ShowPosition(Point* ppos);

// 두 Point 변수의 비교
int PointComp(Point* pos1, Point* pos2);

#endif

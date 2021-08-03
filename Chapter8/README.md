# 8-1 트리의 개요 <br>
트리는 앞에서 배웠던 리스트, 스택, 큐 등의 선형 자료구조와 달리 비선형 자료구조이다. 이러한 트리의 예로는 컴퓨터의 디렉토리 구조 혹은 조직도 등이 있다. <br>
따라서 트리는 선형구조의 자료구조처럼 어떠한 데이터를 삽입, 삭제 하는 방식이 아닌 표현을 중심으로 하는 도구 이다. <br>
다음의 그림을 통해 트리의 구조를 알아보자. <br>
<img src = "/res/Chapter8/tree.JPG" width = "500" height ="300"> <br>
구성요소는 다음과 같다. <br>
### 노드 Node
A, B, C, D, E 와 같은 요소 <br>

### 간선 Edge
각 노드를 연결하는 선

### 루트 노드 Root Node
최상위 노드 위의 그림에서는 A

### 단말 노드 Terminal Node
아래로 다른 노드가 없는 경우 위의 그림에서는 C, D, E

### 부모 노드 Parent Node
노드의 부모 노드 위의 그림에서 B, C, D의 부모 노드는 A

### 자식 노드 Child Node
노드의 아래 노드 위의 그림에서 A의 자식 노드는 B, C, D

### 이진 트리 Binary Tree
루트 노드를 중심으로 두개의 서브 트리로 나누어지고 그 서브트리 역시 두개의 서브트리로 나누어진다. <br>
<img src = "/res/Chapter8/Btree.JPG" width = "500" height ="300"> <br>
위의 그림역시 B의 자식노드가 D하나 밖에 없지만 공집합 노드가 존재한다고 가정하여 이진트리가 된다. <br>

### 포화 이진 트리 (Full Binary Tree)
꽉찬 이진 트리 이다. <br>
<img src = "/res/Chapter8/FBTree.JPG" width = "800" height ="400">

### 완전 이진 트리 (Complete Binary Tree)
포화 이진 트리와 다르게 꽉 찬 상태는 아니지만 빈 틈이 없는 트리 <br>
<img src = "/res/Chapter8/CBTree.JPG" width = "800" eight ="400">
	  
<hr>

# 이진 트리의 구현 
이번에는 이진 트리를 구현해보자. 앞의 자료구조과 마찬가지로 연결 리스트, 배열 모두 구현이 가능하다. <br>

``` C
BTreeNode * MakeBTreeNode(void);
// 이진 트리 토드를 생성하여 그 주소 값을 반환한다.

BTData GetData(BTreeNode * bt);
// 노드에 저장된 데이터를 반환한다.

void SetData(BTreeNode * bt, BTData data);
// 노드에 데이터를 저장한다. data로 전달된 값을 저장한다.

BTreeNode * GetLeftSubTree(BTreeNode * bt);
// 왼쪽 서브 트리의 주소 값을 반환한다.

BTreeNode * GetRightSubTree(BTreeNode * bt);
// 오른쪽 서브 트리의 주소 값을 반환한다.

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub);
// 왼쪽 서브 트리를 연결한다.

void MakeRightSubTree(BTreeNode * main, BTreeNode * sub);
// 오른쪽 서브 트리를 연결한다.
```

이제 이 ADT를 기반으로 배열 기반, 연결 리스트 기반으로 구현해보겠다. 먼저 헤더파일을 보자. <br>
``` C
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode * left;
	struct _bTreeNode * right;
} BTreeNode;

/*** BTreeNode 관련 연산들 ****/
BTreeNode * MakeBTreeNode(void);
BTData GetData(BTreeNode * bt);
void SetData(BTreeNode * bt, BTData data);

BTreeNode * GetLeftSubTree(BTreeNode * bt);
BTreeNode * GetRightSubTree(BTreeNode * bt);

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub);
void MakeRightSubTree(BTreeNode * main, BTreeNode * sub);

#endif
```

위의 ADT를 기반으로 구현한 BinaryTree.c는 다음과 같다. <br>
``` C
#include <stdio.h>
#include "BinaryTree.h"

BTreeNode* MakeBTreeNode(void) {
	BTreeNode* nd = (BTreeNode*)malloc(sizeof(BTreeNode));
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTData GetData(BTreeNode* bt) {
	return bt->data;
}

void SetData(BTreeNode* bt, BTData data) {
	bt->data = data;
}

BTreeNode* GetLeftSubTree(BTreeNode* bt) {
	return bt->left;
}

BTreeNode* GetRightSubTree(BTreeNode* bt) {
	return bt->right;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub) {
	if (main->left != NULL)
		free(main->left);
	main->left = sub;
}

void MakeRightSubTree(BTreeNode* main, BTreeNode* sub) {
	if (main->right != NULL)
		free(main->right);
	main->right = sub;
}

```
# 이진 트리의 순회(Traversal)

이진 트리의 순회 즉 조회에는 3가지의 방법이 있으며 다음이 그것이다. 1. 전위 순회, 2. 중위 순회, 3. 후위 순회 각각 루트노드를 처음에, 중간에, 마지막에 <br>
조회하는 방법이며 각각의 그림은 다음과 같다. 좌측부터 전위 순회, 중위 순회, 후위 순회이다. <br>
<img src = "/res/Chapter8/traversal.JPG"> <br>
루트의 높이가 3이상이더라도 해당 과정을 재귀적으로 반복하면 되기 때문에 나머지 역시 쉽게 이해할 수 있다. 노드의 순회를 출력으로 대체한다고 하면 중의 순회는 다음과 같다. <br>
``` C
void InorderTraverse(BTreeNode * bt) {	
	if(bt == NULL) {		// 탈출조건 bt가 NULL이면 재귀 탈출
		return;
	}
	
	InorderTraverse(bt->left);	// 1단계 왼쪽 서브 트리의 순회
	printf("%d \n", bt->data);	// 2단계 루트 노드의 방문
	InorderTraverse(bt->right);	// 3단계 오른쪽 서브 트리의 순회
}
```

전위연산도 다음과 같다. 
``` C
void PreorderTraverse(BTreeNode * bt) {	
	if(bt == NULL) {		// 탈출조건 bt가 NULL이면 재귀 탈출
		return;
	}
	
	printf("%d \n", bt->data);	
	PreorderTraverse(bt->left);	
	PreorderTraverse(bt->right);	
}
```

후위연산도 다음과 같다.
``` C
void PostorderTraverse(BTreeNode * bt) {	
	if(bt == NULL) {		// 탈출조건 bt가 NULL이면 재귀 탈출
		return;
	}
	
	PostorderTraverse(bt->left);	
	PostorderTraverse(bt->right);	
	printf("%d \n", bt->data);	
}
```

<hr>

# 수식 트리의 구현
7 + 4 * 2 - 1 이라는 식이 있다고 생각해보자. 이 식은 컴퓨터가 다음의 그림처럼 수식 트리로 인식을 한다. <br>
<img src = "/res/Chapter8/expressiontree.JPG" width = "600" height = "500">

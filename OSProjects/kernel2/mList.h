#ifndef __MLIST_H__
#define __MLIST_H__

#include "../kernel1/OSDefine.h"

#pragma pack(push, 1)

typedef struct _ListNode{
	struct _ListNode* next;
	DWORD data;
}LNode;

typedef struct _mLList{
	int nodeCount;		//노드 수
	LNode* header;		//맨 앞 노드
	LNode* tail;		//맨 뒤 노드
}mLList;

#pragma pack(pop)

void initList(mLList* list);
void insertItemBack(mLList* list, const DWORD data);
int deleteItemFront(mLList* list);		//성공시 0, 실패시  -1을 반환
int deleteItemBack(mLList* list);
DWORD popItem(mLList* list);
int removeItem(mLList* list, int index);
int searchItem(const mLList* list, const DWORD data);		//못찾으면 -1을 반환
DWORD getItem(const mLList* list, int index);

#endif /*__MLIST_H__*/

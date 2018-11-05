#include "mList.h"
#include "mMemory.h"

void initList(mLList* list) {
	list->nodeCount = 0;
	list->header = 0;
	list->tail = 0;
}

void insertItemBack(mLList* list, const DWORD data) {
	LNode* node = mMalloc(sizeof(LNode));

	node->data = data;
	node->next = 0;

	// 비어 있는 경우
	if (list->nodeCount == 0) {
		list->header = node;
		list->tail = node;
		list->nodeCount++;
	}
	// 노드가 하나 이상 있는 경우
	else {
		list->tail->next = node;
		list->tail = node;
		list->nodeCount++;
	}
}

int deleteItemFront(mLList* list) {
	//노드가 없는 경우
	if (list->nodeCount == 0) {
		return -1;
	}
	//노드가 하나인 경우
	else if (list->nodeCount == 1) {
		if (mFree(list->header, sizeof(*list->header)) == -1)
			return -1;
		list->header = 0;
		list->tail = 0;
	}
	//노드가 2개 이상인 경우
	else if (list->nodeCount >= 2) {
		LNode* oldHeader = list->header;
		list->header = oldHeader->next;
		if (mFree(oldHeader, sizeof(*oldHeader)) == -1)
			return -1;
	}
	list->nodeCount--;
	return 0;
}

int deleteItemBack(mLList* list) {
	LNode* node;
	int i;
	//노드가 없는 경우
	if (list->nodeCount == 0) {
		return -1;
	}
	//노드가 하나인 경우
	else if (list->nodeCount == 1) {
		if (mFree(list->header, sizeof(*list->header)) == -1)
			return -1;
		list->header = 0;
		list->tail = 0;
	}
	//노드가 2개 이상인 경우
	else if (list->nodeCount >= 2) {
		LNode* oldTail = list->tail;
		node = list->header;
		for (i = 0; i < list->nodeCount - 1; i++) {
			node = node->next;
		}
		node->next = 0;
		list->tail = node;
		if (mFree(oldTail, sizeof(*oldTail)) == -1)
			return -1;
	}
	list->nodeCount--;
	return 0;
}

DWORD popItem(mLList* list) {
	DWORD data = list->header->data;
	deleteItemFront(list);
	return data;
}

int removeItem(mLList* list, int index) {
	LNode* node;		//지울 대상의 이전 노드
	LNode* target;		//지울 대상
	int i;
	if (index < 0 || (list->nodeCount - 1) < index) {
		return -1;
	}

	//지울 대상이 맨 앞이었을 경우
	if (index == 0) {
		return deleteItemFront(list);
	}
	//지울 대상이 맨 뒤였을 경우
	if (index == (list->nodeCount - 1)) {
		return deleteItemBack(list);
	}
	//그 이외의 경우
	//지울 노드의 이전 노드까지 이동
	node = list->header;
	for (i = 0; i < index - 1; i++) {
		node = node->next;
	}
	//노드를 지우고 앞 노드와 뒤 노드를 연결
	target = node->next;
	node->next = target->next;
	list->nodeCount--;
	if (mFree(target, sizeof(LNode)))
		return -1;
	return 0;
}

int searchItem(const mLList* list, const DWORD data) {
	LNode* node;
	int i = 0;

	node = list->header;
	if (node->data == data)
		return 0;
	for (i = 0; i < list->nodeCount; i++) {
		node = node->next;
		if (node->data == data)
			return (i + 1);
	}
	return -1;
}

DWORD getItem(const mLList* list, int index) {
	LNode* node;
	int i = 0;

	if (index < 0 || (list->nodeCount - 1) < index) {
		return 0;
	}

	node = list->header;
	for (i = 0; i < index; i++) {
		node = node->next;
	}
	return node->data;
}

#pragma once
#include "Heap.h"

class DLinkedList
{
public:
	DLinkedList(Heap*& _hp);
	~DLinkedList();

	void* get(int pos);
	void  add(void* data, int sz);
	void* take_first();
	void* take_last();
	void* take(int pos);
	int   count();
	void  itReset();
	bool  itHasNext();
	void* itNext();

private:
	struct Node
	{
		void* data;
		Node* prev;
		Node* next;
	};
	Node* first;
	Node* last;
	Node* iter;
	int _count;
	bool err;

protected:
	Heap* hp;
};


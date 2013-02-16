#pragma once
#include <string.h>
#include "DLinkedList.h"

DLinkedList::DLinkedList(Heap*& _hp)
{
	_count = 0;
	first = nullptr;
	last = nullptr;
	err = false;
	hp = _hp;
}

DLinkedList::~DLinkedList()
{
	Node* itr = first;
	while (first != nullptr)
	{
		itr = first;
		first = first->next;
		hp->free_mem((void*&)itr);
	}
	delete hp;
	hp = nullptr;
}

void* DLinkedList::get(int pos)
{
	if(first == nullptr) return nullptr;
	if(pos > _count - 1 || pos < 0) return nullptr;
	Node* itr = first; int itPos = 0;
	while (itPos != pos) {
		itPos++;
		itr = itr->next;
	}

	return itr->data;
}

void DLinkedList::add(void* data, int sz)
{
	_count++;
	Node* elem = (Node*) hp->get_mem(sizeof(Node));
	elem->data = hp->get_mem(sz);
	memcpy(elem->data, data, sz);
	elem->next = nullptr; elem->prev = nullptr;

	if(first == nullptr) {
		first = elem;
		last = elem;
		return;
	}

	Node* itr = first;
	while (itr->next != nullptr) itr = itr->next;

	itr->next = elem;
	elem->prev = itr;
	last = elem;
}

void* DLinkedList::take_first()
{
	if(first == nullptr) return nullptr;
	_count--;
	if(first->next == nullptr) {
		Node* answer = first;
		first = last = nullptr;
		return answer->data;
	}
	Node* asnwer = first;
	first->next->prev = nullptr;
	first = first->next;
	return asnwer->data;
}

void* DLinkedList::take_last()
{
	if(first == nullptr) return nullptr;
	_count--;
	if(first->next == nullptr) {
		Node* answer = first;
		first = last = nullptr;
		return answer->data;
	}
	Node* answer = last;
	last->prev->next = nullptr;
	last = last->prev;
	return answer->data;
}

void* DLinkedList::take(int pos)
{
	if(first == nullptr) return nullptr;
	_count--;
	if(pos == 0) return take_first();
	if(pos == _count - 1) return take_last();
	int counter = -1;
	Node* itr = first;
	while (itr != nullptr)
	{
		counter++;
		if(counter == pos)
		{
			Node* answer = itr;
			itr->prev->next = itr->next;
			itr->next->prev = itr->prev;
			return answer->data;
		}
		itr = itr->next;
	}
}

int DLinkedList::count() { return _count; }

void DLinkedList::itReset() {
	iter = first;
}

bool DLinkedList::itHasNext() {
	return iter != nullptr;
}

void* DLinkedList::itNext() {
	void* answer = iter->data;
	iter = iter->next;
	return answer;
}
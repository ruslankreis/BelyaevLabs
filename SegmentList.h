#pragma once
#include "DLinkedList.h"

class SegmentList : public DLinkedList
{
private:
	struct Segment {
		int els;
		int length;
		void* arr;
		void  init(Heap*& hp, int _els, int elc) {
			els = _els;
			arr = hp->get_mem(els * elc);
			length = 0;
		}
		void* get(int i) {
			char* answer = (char*)arr;
			answer += els * i;
			return answer;
		}
		void  set(int i, void* data) {
			void* bf = get(i);
			memcpy(bf, data, els);
		}
		void  add(void* data, int sz) {
			char* carr = (char*)arr;
			carr += (length * els);
			memcpy(carr, data, sz);
			length++;
		}
	};
	int first_index;
	int last_index;
	int elem_size;
	int elems_count;
	int count_insegs;

public:
	SegmentList(int _elSize, int _elCount, Heap*& _hp) : DLinkedList(_hp) {
		elem_size = _elSize;
		elems_count = _elCount;
		first_index = 0;
		count_insegs = 0;
	}

	~SegmentList() {
		DLinkedList::~DLinkedList();
	}

	void* sget(int pos) {
		if(pos < 0) return nullptr;
		Segment* cr = nullptr; int counter = -first_index;
		itReset();
		while(itHasNext()) {
			cr = (Segment*) itNext();
			counter += elems_count;
			if(counter > pos) break;
		}
		int realPos = ( (pos - first_index) - (elems_count - first_index) ) % elems_count;
		realPos = realPos < 0 ? realPos + elems_count : realPos;
		return cr->get(realPos);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
	} // checked

	void  sadd(void* data, int sz) {
		count_insegs++;
		if(count() == 0) {
			Segment* f = (Segment*) hp->get_mem(sizeof(Segment));
			f->init(hp, elem_size, elems_count);
			f->add(data, sz);
			add(f, sizeof(Segment));
			return;
		}

		Segment* lst = (Segment*) this->get(count() - 1);
		if(lst->length != elems_count) {
			lst->add(data, sz);
			return;
		} else {
			Segment* f = (Segment*) hp->get_mem(sizeof(Segment));
			f->init(hp, elem_size, elems_count);
			f->add(data, sz);
			add(f, sizeof(Segment));
		}
	} // checked

	void* stake_first() {
		if(count() == 0) return nullptr;
		count_insegs--;
		if(first_index >= elems_count) {
			Segment* forDel = (Segment*) take_first();
			hp->free_mem(forDel->arr);
			hp->free_mem((void*&) forDel);
			first_index = 0;
		}
		Segment* res = (Segment*) get(0);
		void* answer = res->get(first_index++);
		return answer;
	} // checked

	void* stake_last() {
		if(count() == 0) return nullptr;
		count_insegs--;
		Segment* res = (Segment*) get(count() - 1);
		if(res->length == 1) {
			void* answer = res->get(0);
			hp->free_mem((void*&) res);
			take_last();
			return answer;
		}

		void* answer = res->get(res->length - 1);
		res->length--;
		return answer;
	} // checked

	void* stake(int pos) {
		return nullptr;
		// Not yet implemented!
	}

	int scount() {
		return count_insegs;
	}
};
#pragma once
#include "SegmentList.h"

class Stack : SegmentList
{
protected:
	int sz;
public:
	Stack(Heap*& hp, int part) : SegmentList(sizeof(double), part, hp) { sz = sizeof(double); };
	~Stack() { SegmentList::~SegmentList(); }

	void   push(double x) { sadd(&x, sz); };
	
	double pop() {
		double* res = (double*) stake_last();
		return res != nullptr ? *res : 0;
	}; 
};
#pragma once
#include "SegmentList.h"

class Deque : SegmentList
{
protected:
	int sz;
public:
	Deque(Heap*& hp, int part) : SegmentList(sizeof(double), part, hp) { sz = sizeof(double); };
	~Deque() { SegmentList::~SegmentList(); }

	void   put(double x) { sadd(&x, sz); };
	double first() { double *res = (double*) stake_first(); return *res; };
	double last()  { double *res = (double*) stake_last(); return *res; };

};
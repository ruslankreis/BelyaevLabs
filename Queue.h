#pragma once
#include "SegmentList.h"

class Queue : SegmentList
{
protected:
	int sz;
public:
	Queue(Heap*& hp, int part) : SegmentList(sizeof(double), part, hp) { sz = sizeof(double); };
	~Queue() { SegmentList::~SegmentList(); }

	void   put(double x) { sadd(&x, sz); };
	double get() { double *res = (double*) stake_first(); return *res; };
};
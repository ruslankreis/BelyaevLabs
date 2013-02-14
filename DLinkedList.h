#include "Heap.h"

class DLinkedList
{
public:
	DLinkedList(Heap *_hp = nullptr);
	~DLinkedList();

	void*      get(int pos);
	void       add(void* data);
	void*       take_first();
	void*       take_last();
	void*       take(int pos);
	int        count();
	Heap* getMemManager();

private:
	struct Node
	{
		void*    data;
		Node* prev;
		Node* next;
	};
	Node*         first;
	Node*         last;
	int _count;
	bool             err;
	Heap* hp;
};


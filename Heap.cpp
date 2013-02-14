#include "Heap.h"


Heap::Heap(int _segment_size) {
	current = nullptr;
}

Heap::~Heap() {
	delete_segments();
}

int Heap::make_segment() {
	// Типичный алгоритм добавления узла в список.
	if(current == 0) {
		current = new Segment();
	} else {
		Segment *it = current;
		while (it->prev != 0) it = it->prev;
		it->prev = new Segment();
	}

	return 0;
}

void Heap::delete_segments() {
	// Типичное удаление списка.
	Segment *temp;
	while (current != 0) {
		temp = current->prev;
		delete current;
		current = temp;
	}
}

void* Heap::get_mem(int size) {
	if(size >= SEGMENTSIZE)  return nullptr;
	Segment *itr = current;

	while (true)
	{
		if(itr == 0) { // если сегментов нет вообще
			make_segment();
			itr = current;
			break;

		} else if(itr->total_size + size < SEGMENTSIZE && itr->descriptor_count < SEGMENTCOUNT) { // нашли сегмент, в который можно поместить наш объект
			int minSize = SEGMENTSIZE, ik = 0; bool isFound = false;							  // Теперь мы ищем ячейку, наиболее подходящую под наш объект
			for(int i = 0; i < itr->descriptor_count; i++)                                        // так как если маленький объект займёт большую ячейку
				if(itr->descriptor[i].used == false && itr->descriptor[i].size >= size) {         // то у нас будет утечка памяти, так как он закроет доступ к свободной памяти в ячейке
					isFound = true;																  // break - закрывает цикл  и мы переходим в конец кода, где заполняем результирующую структуру и отдаем пользователю
					if(itr->descriptor[i].size - size < minSize) {
						ik = i;
						minSize = itr->descriptor[i].size - size;
					}
				}
			if(isFound) { // Проверка нужна, чтобы убедиться - есть ли вообще ячейка в том сегменте, но по идее если мы зашли в этот блок,
				itr->descriptor[ik].used = true; // то такая ячейка обязана существовать...
				return itr->descriptor[ik].offset;
			}

			break;

		} else if(itr->prev == nullptr) { // Если сегмент со свободным местом не найден, создаем новый.
			make_segment();
			itr = itr->prev;
			break;


		} else itr = itr->prev;
	}
	Segment::fill_desc(itr->descriptor, itr->data, itr->descriptor_count, true, size, itr->total_size); // Бойлер-плейт вынесен вниз.
	return itr->descriptor[itr->descriptor_count - 1].offset;
}

void Heap::free_mem(void* &pMem) {
	//if(pMem == 0 || pMem < current) return; // если наш указатель меньше нижней границы нашей памяти
	// нет информации, как выделяет память система - возможен случай, что для n+1 сегмента адрес указателя будет меньше чем у n-сегмента

	Segment *itr = current; Segment* maybeDel = nullptr;
	while (itr != nullptr) {
		// if((int)itr->data + itr->total_size < (int)pMem) continue; // Проверяем - если адрес указателя больше, то в предыдущих блоках 
		for(int i = 0; i < itr->descriptor_count; i++) // нашего указателя точно нет. Этот блок имеет такую же проблему, описанную выше
			if(itr->descriptor[i].offset == pMem) {    // поэтому данная оптимизация закомментирована
				itr->descriptor[i].used = false;
				pMem = 0;
				itr->total_size -= itr->descriptor[i].size;
				if(itr->total_size == 0) {
					delete itr;
					itr = nullptr;
					if(maybeDel != nullptr)
						maybeDel->prev = 0;
					else current = nullptr;
				}
				return;
			}
		maybeDel = itr;
		itr = itr->prev;
	}
}
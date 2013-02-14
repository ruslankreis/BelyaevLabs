#define SEGMENTSIZE 65536
#define SEGMENTCOUNT 1024
#include <string.h>

class Heap {
public:
	Heap(int _segment_size = SEGMENTSIZE); // check
	~Heap(); // check

	void* get_mem(int size); // check
	void  free_mem (void* &pMem);

private:
	struct Segment_def {       
		bool      used; // Использование данной ячейки
		int       size; // размер занятой памяти
		void*     offset; // сдвиг относительно указателя data
	};
	struct Segment {
		char*        data; // общая память сегмента для всех ячеек
		Segment*     prev; // следующий элемент 
		Segment_def  descriptor[SEGMENTCOUNT]; // наши ячейки
		int          descriptor_count; // количество занятых ячеек
		int total_size; // общая занятая память в сегменте

		Segment(int seg_size = SEGMENTSIZE) {
			descriptor_count = 0;
			prev = 0;
			data = new char[seg_size + 1];
			data[seg_size] = 0x00;
			total_size = 0;
		}

		~Segment() {
			delete[] data;
		}
		// desarr - массив ячеек. bf - указатель на data(метод static не имеет доступа к data), indx = позиция свободной ячейки
		// use - установка занятости(может быть удалена), sz - размер занимаемой ячейки, tt_size - занятая память(ссылка - для изменения)
		static void fill_desc(Segment_def *desarr, void* bf, int &indx, bool use, int sz, int &tt_size) {
			//DBG/char* offs = (char*)bf; // вычисляем сдвиг относительно главного указателя data, который передается в bf.
			//DBG/for(int i = 0; i < indx; i++)
			//DBG/	offs += desarr[i].size;

			char* dbg = (char*)desarr[indx - 1].offset;
			dbg += desarr[indx - 1].size;

			desarr[indx].offset = (void*)dbg;
			//DBG/desarr[indx].offset = (void*)offs;
			desarr[indx].used = use;
			desarr[indx].size = sz;
			indx++; // позиция следующей свободной ячейки
			tt_size += sz; // новое значение занятой памяти
		}
	};
	
	int	 make_segment(); // check
	void delete_segments(); // check
	Segment* current;
};
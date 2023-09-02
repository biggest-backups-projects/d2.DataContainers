#include "Vector.h"

namespace DataContainers {

	template <typename type>
	void Vector<type>::SetCapacity(int value) {
		if (value == -1)
			capacity *= 2;

		type* newData = new type[capacity];

		if (size != 0) {
			for (unsigned int i = 0; i < size; i++)
				newData[i] = data[i];

			delete data;
		}
		data = newData;
	}

	template <typename type>
	Vector<type>::Vector() {
		size = 0;
		capacity = 8;
		data = new type[capacity];
	}

	template <typename type>
	Vector<type>::Vector(const Vector<type>& list) {
		for (unsigned int i = 0; i < list.Size(); i++)
			PushBack(list[i]);
	}

	template <typename type>
	Vector<type>::Vector(const std::initializer_list<type> _arr) {
		for (size_t i = 0; i < _arr.size(); i++)
			PushFront(*(_arr.end() - i - 1));
	}

	template <typename type>
	type* Vector<type>::begin() const {
		return data;
	}

	template <typename type>
	type* Vector<type>::end() const {
		return data+size;
	}
}

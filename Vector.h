#pragma once
#include <cassert>
#include <functional>
#include <iostream>

namespace DataContainers {
	template<typename type>
	class Vector
	{
	private:
		type* data;
		unsigned int size;
		unsigned int capacity;

		void setCapacity(int value = -1) {
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
	public:

		Vector() {
			size = 0;
			capacity = 8;
			data = new type[capacity];
		}	
		Vector(const Vector<type>& list) {
			for (unsigned int i = 0; i < list.Size(); i++)
				PushBack(list[i]);
		}
		Vector(const std::initializer_list<type> _arr) : Vector() {
			for (const auto& elem : _arr)
				PushBack(elem);
		}

		~Vector() {
			Clear();
		}

		void PushBack(const type& elem) {
			if (size == capacity)
				setCapacity();

			data[size] = elem;
			size++;
		}
		void PushFront(const type& elem) {
			if (size == capacity)
				setCapacity();


			type* newData = new type[capacity];
			newData[0] = elem;

			for (unsigned int i = 0; i < size; i++)
				newData[i + 1] = data[i];

			delete[] data;
			data = newData;
			size++;
		}
		void Insert(const type& elem, unsigned ind) {

			if (ind == 0)
				return PushFront(elem);
			if (ind == size - 1)
				return PushBack(elem);
			if (size == capacity)
				setCapacity();

			type* newData = new type[capacity];

			for (unsigned int i = 0; i < ind; i++)
				newData[i] = data[i];

			newData[ind] = elem;

			for (unsigned int i = ind; i < size; i++)
				newData[i + 1] = data[i];


			delete[] data;
			data = newData;

			size++;
		}


		void ForEach(const std::function<void(type)>& function)	{
			for (size_t i = 0; i < size; i++)
				function(data[i]);
		}
		Vector<type> Filter(const std::function<bool(type)>& predicate) {
			Vector<type> result;
			for (size_t i = 0; i < size; i++) {
				if (predicate(data[i]))
					result.PushBack(data[i]);
			}
			return result;
		}


		[[nodiscard]]
		type PopBack() {
			assert(size > 0);

			type elem = data[size - 1];
			size--;
			return elem;
		}
		[[nodiscard]]
		type PopFront()	{
			type* newData = new type[capacity];

			for (unsigned int i = 0; i < size-1; i++)
				newData[i] = data[i + 1];

			type result = data[0];
			delete[] data;
			data = newData;
			size--;
			return result;
		}
		[[nodiscard]]
		type Pop(unsigned ind) {
			assert(ind < size && "Index out of range");
			if (ind == 0)
				return PopFront();
			if (ind == size - 1)
				return PopBack();

			type* newData = new type[capacity];

			for (uint32_t i = 0; i < ind; i++)
				newData[i] = data[i];

			type result = data[ind];

			for (uint32_t i = ind + 1; i < size; i++)
				newData[i] = data[i - 1];

			delete[] data;
			data = newData;
			size--;
			return result;
		}
		[[nodiscard]]
		type At(unsigned int ind) const {
			assert(ind < size && "Index out of range");
			return data[ind];
		}
		[[nodiscard]]
		type operator[](unsigned ind) const {
			return At(ind);
		}
		void Remove(unsigned ind) {
			assert(ind < size && "Index out of range");

			type* newData = new type[capacity];

			for (uint32_t i = 0; i < ind; i++)
				newData[i] = data[i];


			for (uint32_t i = ind + 1; i < size; i++)
				newData[i] = data[i - 1];


			delete[] data;
			data = newData;
			size--;
		}


		type* begin() const {
			return data;
		}
		type* end() const {
			return data + size;
		}


		void Clear() {
			delete[] data;
			data = nullptr;
			size = 0;

		}
		bool Empty() const {
			return size == 0;
		}
		unsigned int Size() const {
			return size;
		}
	};

	
}

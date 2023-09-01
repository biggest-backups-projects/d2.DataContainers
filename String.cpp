#include<iostream>
#include <list>
#include <vector>
#include "String.h"

#include <cassert>

using namespace std;

namespace DataContainers{

	String::String() {
		data = nullptr;
		size = 0;
	}

	String::String(const char* str) {
		size = CountSize(str) + 1;
		data = new char[size];

		for (size_t i = 0; i < size; i++)
			data[i] = str[i];
		data[size - 1] = '\0';

	}

	String::String(const String& st) {
		this->size = st.size;
		this->data = new char[this->size];

		for (int i = 0; i < this->size; i++)
			this->data[i] = st.data[i];
	}

	String::~String() {
		Сlear();
	}

	char String::operator[](unsigned int index) const {
		assert(index <= size - 1 && "Index out of range");
		return data[index];
	}

	String String::operator+(const String& str) {
		int oldLen = size;
		if (oldLen == 0) size++;
		size += (str.size - 1);

		char* NewData = new char[size];

		size_t i = 0;
		if (oldLen != 0)
			for (; i < oldLen - 1; i++)
				NewData[i] = data[i];

		for (size_t j = 0; i < size; i++, j++)
			NewData[i] = str[j];

		return String(NewData);
	}

	char* String::operator+(const char* str) {
		const int oldLen = size;
		if (size == 0) size++;
		size += (String::CountSize(str) - 1);

		char* NewData = new char[size];

		size_t i = 0;
		if (oldLen != 0)
			for (; i < oldLen - 1; i++)
				NewData[i] = data[i];


		for (size_t j = 0; i < size; i++, j++)
			NewData[i] = str[j];

		return NewData;
	}

	void String::operator+=(const char* str) {
		const int oldLen = size;
		if (size == 0) size++;
		size += (String::CountSize(str) - 1);

		char* oldData = new char[oldLen];

		for (size_t i = 0; i < oldLen; i++)
			oldData[i] = data[i];

		if (data != nullptr) {
			delete[]data;
			data = nullptr;
		}

		data = new char[size];
		size_t i = 0;

		if (oldLen != 0)
			for (; i < oldLen - 1; i++)
				data[i] = oldData[i];

		for (size_t j = 0; i < size; i++, j++)
			data[i] = str[j];
	}

	void String::operator+=(const String& str) {
		int oldLen = size;
		if (oldLen == 0) size++;
		size += (str.size - 1);

		char* oldData = new char[oldLen];

		for (size_t i = 0; i < oldLen; i++)
			oldData[i] = data[i];

		if (data != nullptr) {
			delete[]data;
			data = nullptr;
		}

		data = new char[size];
		size_t i = 0;
		if (oldLen != 0)
			for (; i < oldLen - 1; i++)
				data[i] = oldData[i];

		for (size_t j = 0; i < size; i++, j++)
			data[i] = str[j];

	}

	String& String::operator=(const char* str) {
		size = CountSize(str);

		Сlear();

		data = new char[size];
		for (size_t i = 0; i < size; i++)
			data[i] = str[i];

		return *this;
	}

	String& String::operator=(const String& str) {
		size = str.Size();

		Сlear();

		this->data = new char[size];
		for (size_t i = 0; i < size; i++)
			this->data[i] = str.data[i];

		return *this;
	}

	unsigned int String::CountSize(const char* str) {
		int res = 0;
		while (str[res] != '\0')
			res += 1;
		return res;
	}

	String String::Cat(const char* str) {
		const unsigned int strSize = CountSize(str);

		if (str == nullptr || strSize == 1)
			return *this;

		unsigned int newSize = 0;

		if (size == 0)
			newSize++;
		else
			newSize += size - 1;

		newSize += strSize;

		char* newData = new char[newSize];

		for (size_t i = 0; i < size; i++)
			newData[i] = this->data[i];
		
		for (size_t i = 0; i < strSize; i++)
			newData[size - 1 + i] = str[i];

		newData[size + strSize - 1] = '\n';
		return String{ newData };
	}

	String String::Cat(const String& str) {
		return Cat(str.CStr());
	}

	String String::Revers() const {
		char* newData = new char[size];
		for (size_t i = 0, j = size - 2; i < size-1; i++, j--)
			newData[i] = this->data[j];

		newData[size - 1] = '\0';
		return  newData;
	}

	bool String::Empty() const {
		return data == nullptr;
	}

	void String::Сlear() {
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
		}
		size = 0;
	}

	char* String::CStr() const {
		char* result = new char[size];

		for (size_t i = 0; i < size; i++)
			result[i] = data[i];

		return data;
	}

	unsigned int String::Size() const {
		return size;
	}

	std::ostream& operator<<(std::ostream& os, String& str) {
		if (!str.Empty())
			os << str.data;

		return os;
	}

	std::istream& operator>>(std::istream& in, String& str) {
		char* buffer = new char[_MAX_PATH];
		std::cin.getline(buffer, _MAX_PATH);
		const unsigned int size = String::CountSize(buffer);

		if (!str.Empty())
			str.Сlear();

		str.data = new char[size+1];
		str.size = size+1;
		for (unsigned int i = 0; i < size; i++)
			str.data[i] = buffer[i];

		str.data[size] = '\0';

		return in;
	}

}


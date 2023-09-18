#include "StringBuilder.h"
#include <cassert>


namespace DataContainers {
	int StringBuilder::calcLen(const char* string) {
		int res = 0;
		while (string[res++] != '\0') {}
		return res;
	}



	void StringBuilder::zeroArr(char**& arrToNull, unsigned int count) {
		for (int i = 0; i < count; i++)
			arrToNull[i] = nullptr;
	}


	void StringBuilder::Clear() {
		for (int i = 0; i < lastString; i++) {
			delete[] data[i];
			data[i] = nullptr;
		}
		delete[] data;

		this->capacity = 8;
		data = new char* [this->capacity];
		lastString = 0;
		//zeroArr(data, this->capacity);
	}

	StringBuilder::StringBuilder(unsigned int capacity = 8) {
		assert(capacity > 8);
		this->capacity = capacity;
		data = new char* [this->capacity];
		lastString = 0;
		size = 0;
	/*	zeroArr(data, this->capacity);*/
	}


	StringBuilder::~StringBuilder() {
		for (int i = 0; i < lastString; i++) {
			delete[] data[i];
			data[i] = nullptr;
		}
		capacity = 0;
		lastString = 0;
		delete[] data;
	}

	void StringBuilder::Append(const char* string, bool endl) {
		int size = calcLen(string);
		if (endl) size++;

		if (lastString == capacity)
			setCapacity();

		data[lastString] = new char[size];
		for (int i = 0; i < size - 1; i++)
			data[lastString][i] = string[i];

		if (endl) data[lastString][size - 2] = '\n';
		data[lastString][size - 1] = '\0';
		size -= 1;
		lastString++;
	}

	void StringBuilder::Append(const String& string, bool endl) {
		int size = string.Size();
		if (endl) size++;

		if (lastString == capacity) setCapacity();

		data[lastString] = new char[size];

		for (int i = 0; i < size - 1; i++)
			data[lastString][i] = string[i];

		if (endl) data[lastString][size - 2] = '\n';

		data[lastString][size - 1] = '\0';
		size += size - 1;
		lastString++;
	}


	void StringBuilder::AppendLine(const char* string) {
		Append(string, true);
	}


	unsigned int StringBuilder::Capacity() const {
		return capacity;
	}

	void StringBuilder::setCapacity(unsigned int newCapacity) {

		if (newCapacity == 0 || newCapacity <= lastString)
			newCapacity = 2 * capacity;

		char** newData = new char* [newCapacity];
		zeroArr(newData, newCapacity);

		for (int i = 0; i < lastString; i++)
			newData[i] = data[i];

		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	String StringBuilder::ToString() const {
		char* result = new char[size + 1];
		unsigned int currentPosition = 0;
		for (unsigned int s = 0; s < lastString; s++) {
			int i = 0;
			while (data[s][i] != '\0')
				result[currentPosition++] = data[s][i++];
		}
		result[size] = '\0';
		String res(result);

		return res;
	}
}

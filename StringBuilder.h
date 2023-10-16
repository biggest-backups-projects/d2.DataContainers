#pragma once
#include "String.h"
using namespace std;


namespace DataContainers
{
	class StringBuilder
	{
	private:
		char** data;
		uint32_t size;  // Number of substrings
		uint32_t capacity;
		uint32_t totalLen;  // Len of result string 

		void setCapacity(uint32_t newCapacity = 0) {

			if (newCapacity == 0 || newCapacity <= size)
				newCapacity = 2 * capacity;

			char** newData = new char*[newCapacity];
			for (int i = 0; i < newCapacity; i++)
				newData[i] = nullptr;

			for (int i = 0; i < size; i++)
				newData[i] = data[i];

			delete[] data;
			data = newData;
			capacity = newCapacity;
		}
		int getLen(const char* string) {
			int res = 0;
			while (string[res++] != '\0') {}
			return res;
		}
	public:

		StringBuilder(uint32_t capacity = 8) {
			this->capacity = capacity;
			data = new char*[this->capacity];
			size = 0;
			totalLen = 0;
		}
		~StringBuilder() {
			for (int i = 0; i < size; i++) {
				delete[] data[i];
				data[i] = nullptr;
			}
			capacity = 0;
			size = 0;
			delete[] data;
		}

		void Clear() {
			for (int i = 0; i < size; i++) {
				delete[] data[i];
				data[i] = nullptr;
			}
			delete[] data;

			this->capacity = 8;
			data = new char* [this->capacity];
			size = 0;
		}

		void Append(const char* string, bool endLine = false) {
			int len = getLen(string);

			if (size == capacity)
				setCapacity();

			if (endLine)
				len += 1;

			data[size] = new char[len];  // allocate memory to store new line

			for (int i = 0; string[i] != '\0'; i++)
				data[size][i] = string[i];

			if(endLine)
				data[size][len - 2] = '\n';

			data[size][len - 1] = '\0';
			totalLen += len - 1;
			size++;

		}
		void Append(const String& str, bool endLine = false) {
			int len = str.Len();

			if (size == capacity)
				setCapacity();

			if (endLine)
				len += 1;

			data[size] = new char[len];  // allocate memory to store new line

			for (int i = 0; str[i] != '\0'; i++)
				data[size][i] = str[i];

			if (endLine)
				data[size][len - 2] = '\n';

			data[size][len - 1] = '\0';
			totalLen += len - 1;
			size++;
		}
		void AppendLine(const char* string = "") {
			Append(string, true);
		}
		uint32_t Capacity() const {
			return capacity;
		}
		
		String ToString() const {
			char* result = new char[totalLen + 1];
			uint32_t current = 0;
			for (uint32_t s = 0; s < size; s++) {
				int i = 0;
				while (data[s][i] != '\0')
					result[current++] = data[s][i++];
			}
			result[totalLen] = '\0';

			return String(result);
		}
	};
}



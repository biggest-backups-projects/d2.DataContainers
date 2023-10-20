#pragma once
#include <cassert>
#include<iostream>
#include<fstream>
#include<istream>
#include "Vector.h"

using namespace std;

namespace DataContainers{
	class String
	{
	protected:
		char* data;
		uint32_t size;
		// TODO implement capacity
		//uint32_t capacity;
	public:
		String() {
			data = nullptr;
			size = 0;
		}
		String(const char* str) {
			size = getLen(str)+1;
			data = new char[size];

			for (uint32_t i = 0; i < size; i++)
				data[i] = str[i];
			data[size - 1] = '\0';

		}
		String(const String& str) {
			this->size = str.size;
			this->data = new char[this->size];

			for (int i = 0; i < this->size; i++)
				this->data[i] = str.data[i];
		}
		~String() {
			Ñlear();
		}

		static uint32_t getLen(const char* str) {
			int len = 0;
			while (str[len] != '\0')
				len += 1;
			return len;
		}
		String Append(const char* str) {
			const uint32_t len = getLen(str);

			if (str == nullptr || len == 1)
				return *this;

			uint32_t newLen = size == 0? 1 : size-1;

			newLen += len;

			char* newData = new char[newLen];

			for (uint32_t i = 0; i < size; i++)
				newData[i] = this->data[i];

			for (uint32_t i = 0; i < len; i++)
				newData[size - 1 + i] = str[i];

			newData[size + len - 1] = '\n';
			return String{ newData };
		}
		String Append(const String& str) {
			return Append(str.CStr());
		}
		String Revers() const {
			char* newData = new char[size];
			for (uint32_t i = 0, j = size - 2; i < size - 1; i++, j--)
				newData[i] = this->data[j];

			newData[size - 1] = '\0';
			return newData;
		}
		void Ñlear() {
			if (data != nullptr) {
				delete[] data;
				data = nullptr;
			}
			size = 0;
		}
		bool Empty() const {
			return size == 0;
		}
		char* CStr() const {
			char* result = new char[size];

			for (uint32_t i = 0; i < size; i++)
				result[i] = data[i];

			return result;
		}
		uint32_t Len() const {
			return size;
		}
		char operator[](uint32_t index)const {
			assert(index <= size - 1 && "Index out of range");
			return data[index];
		}

		friend std::ostream& operator<<(std::ostream& os, const String& str) {
			if (!str.Empty())
				os << str.data;
			return os;
		}
		friend std::istream& operator>>(std::istream& in, String& str) {
			char* buffer = new char[_MAX_PATH];
			std::cin.getline(buffer, _MAX_PATH);
			const uint32_t totalLen = String::getLen(buffer);

			if (!str.Empty())
				str.Ñlear();

			str.data = new char[totalLen + 1];
			str.size = totalLen + 1;
			for (uint32_t i = 0; i < totalLen; i++)
				str.data[i] = buffer[i];

			str.data[totalLen] = '\0';

			return in;
		}

		void operator+=(const char* str) {
			const int oldLen = size;
			if (size == 0) size++;
			size += (String::getLen(str) - 1);

			char* oldData = new char[oldLen];

			for (uint32_t i = 0; i < oldLen; i++)
				oldData[i] = data[i];

			if (data != nullptr) {
				delete[]data;
				data = nullptr;
			}

			data = new char[size];
			uint32_t i = 0;

			if (oldLen != 0)
				for (; i < oldLen - 1; i++)
					data[i] = oldData[i];

			for (uint32_t j = 0; i < size; i++, j++)
				data[i] = str[j];
		}
		void operator+=(const String& str) {
			int oldLen = size;
			if (oldLen == 0) size++;
			size += (str.size - 1);

			char* oldData = new char[oldLen];

			for (uint32_t i = 0; i < oldLen; i++)
				oldData[i] = data[i];

			if (data != nullptr) {
				delete[]data;
				data = nullptr;
			}

			data = new char[size];
			uint32_t i = 0;
			if (oldLen != 0)
				for (; i < oldLen - 1; i++)
					data[i] = oldData[i];

			for (uint32_t j = 0; i < size; i++, j++)
				data[i] = str[j];

		}
		char* operator+(const char* str) {
			const uint32_t oldLen = size;
			if (size == 0) size++;
			size += getLen(str);

			char* newData = new char[size];

			uint32_t i = 0;
			if (oldLen != 0)
				for (; i < oldLen - 1; i++)
					newData[i] = data[i];


			for (uint32_t j = 0; i < size; i++, j++)
				newData[i] = str[j];

			return newData;
		}
		String operator+(const String& str) {
			int oldLen = size;
			if (oldLen == 0) size++;
			size += (str.size - 1);

			char* NewData = new char[size];

			uint32_t i = 0;
			if (oldLen != 0)
				for (; i < oldLen - 1; i++)
					NewData[i] = data[i];

			for (uint32_t j = 0; i < size; i++, j++)
				NewData[i] = str[j];

			return String(NewData);
		}
		String& operator=(const char* str) {
			uint32_t newSize = getLen(str)+1;

			Ñlear();

			data = new char[newSize];
			for (uint32_t i = 0; i < newSize; i++)
				data[i] = str[i];

			size = newSize;
			return *this;
		}
		String& operator=(const String& str) {
			if (this == &str)
				return *this;

			const uint32_t newSize = str.Len();

			Ñlear();

			this->data = new char[newSize];
			for (uint32_t i = 0; i < size; i++)
				this->data[i] = str.data[i];

			size = newSize;
			return *this;
		}

		bool operator==(const String& str) const {
			if (size != str.size)
				return false;
			for (size_t i = 0; i < size; i++)
				if (data[i] != str[i])
					return false;
			return true;
		}

		// Based on Levenshtein distance algorithm
		// Return similarity between strings in percentage from 0 to 100
		uint32_t Similarity(const String& str) const {
			auto string1 = CStr();
			auto string2 = str.CStr();

			auto len1 = size-1;
			auto len2 = str.Len()-1;

			if(len2 > len1) {
				swap(string1, string2);
				swap(len1, len2);
			}

			Vector<uint32_t> currentRow(len1+1);
			for (uint32_t i = 0; i < len1 + 1; i++)
				currentRow.PushBack(i);

			for (size_t i=1; i < len2+1; i++) {
				Vector<uint32_t> previousRow = currentRow;
				currentRow[0] = i;
				for (size_t j=1; j < len1+1; j++) {
					uint32_t add = previousRow[j] + 1;
					uint32_t del = currentRow[j - 1] + 1;
					uint32_t change = previousRow[j - 1];

					if (string1[j - 1] != string2[i - 1])
						change += 1;

					Vector<uint32_t> tmp({});
					tmp.Append({ add, del, change });
					currentRow[j] = tmp.Min();
				}
			}
			return (1.f - static_cast<float>(currentRow[len1]) / static_cast<float>(len2)) * 100.f;
		}

	};

	

	
}


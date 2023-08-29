#include<iostream>
#include <list>
#include <vector>
#include "String.h"

using namespace std;

namespace DataContainers{

	String::String() {
		data = nullptr;
		size = 0;
	}

	String::String(const char* str) {
		size = String::StrLen(str);
		data = new char[size];

		for (size_t i = 0; i < size; i++)
			data[i] = str[i];
	}

	String::String(const String& st) {
		this->size = st.size;
		this->data = new char[this->size];

		for (int i = 0; i < this->size; i++)
			this->data[i] = st.data[i];
	}

	String::String(size_t n, const char elem) {
		for (size_t i = 0; i < n; i++)
			Cat(elem);
	}

	String::~String() {
		Сlear();
	}

	char String::operator[](unsigned n) const {
		assert(n <= size - 1 && "Index out of range");
		return data[n];
	}

	String String::operator+(String str) {
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
		size += (String::StrLen(str) - 1);

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
		size += (String::StrLen(str) - 1);

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

	void String::operator+=(String str) {
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
		size = String::StrLen(str);

		Сlear();

		data = new char[size];
		for (size_t i = 0; i < size; i++)
			data[i] = str[i];

		return *this;
	}

	String& String::operator=(String str) {
		size = StrLen(str.data);

		Сlear();

		this->data = new char[size];
		for (size_t i = 0; i < size; i++)
			this->data[i] = str.data[i];

		return *this;
	}

	int String::StrLen(char* str) {
		int res = 0;
		while (str[res++] != '\0') {}
		return res;
	}

	int String::StrLen(const char* str) {
		int res = 0;
		while (str[res++] != '\0') {}
		return res;
	}

	void String::kbInput() {
		char* buffer = new char[_MAX_PATH];
		cin.getline(buffer, _MAX_PATH);
		int size = String::StrLen(buffer);

		Сlear();

		data = new char[size];
		size = size;
		for (int i = 0; i < size; i++)
			data[i] = buffer[i];
	}

	void String::Cat(const char* cat) {
		if (cat == nullptr)
			return;

		int oldLen = size;

		if (oldLen == 0) size++;
		size += String::StrLen(cat) - 1;

		char* oldData = new char[oldLen];

		for (size_t i = 0; i < oldLen; i++)
			oldData[i] = data[i];

		Сlear();

		data = new char[size];
		size_t i = 0;

		if (oldLen != 0)
			for (; i < oldLen - 1; i++)
				data[i] = oldData[i];

		for (size_t j = 0; i < size; i++, j++)
			data[i] = cat[j];
	}

	void String::Cat(const char cat) {
		int oldLen = size;

		if (oldLen == 0) size += 2;
		else size++;

		char* oldData = new char[oldLen];

		for (size_t i = 0; i < oldLen; i++)
			oldData[i] = data[i];


		Сlear();

		data = new char[size];
		size_t i = 0;

		if (oldLen != 0)
			for (; i < oldLen - 1; i++)
				data[i] = oldData[i];

		data[i] = cat;
		data[i + 1] = '\0';
	}

	void String::revers() {
		int latsElemInd = size - 2;
		for (size_t i = 0, j = latsElemInd; i < size / 2; i++, j--)
			swap(data[i], data[j]);
	}

	bool String::Empty() const {
		return data == nullptr;
	}

	void String::Сlear() {
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
		}
		size = 0;
	}

	void String::PushBack(char elem) {
		Cat(elem);
	}

	char* String::c_str() {
		return data;
	}

	int String::Size() const {
		return size;
	}

	int StringBuilder::calcLen(const char* string) {
		int res = 0;
		while (string[res++] != '\0') {}
		return res;
	}

	void StringBuilder::Print() {
		std::cout << "\n ----- \n String Builder info : \n Capacity: "
				  << capacity
				  << " \n lastString: "
				  << lastString << "\n";

		for (int i = 0; i < lastString; i++)
			std::cout << i << " => " << data[i] << "\n";
	}

	void StringBuilder::zeroArr(char**& arrToNull, unsigned int count) {
		for (int i = 0; i < count; i++)
			arrToNull[i] = nullptr;
	}

	void StringBuilder::KillData() {
		for (int i = 0; i < lastString; i++) {
			delete[] data[i];
			data[i] = nullptr;
		}
		capacity = 0;
		lastString = 0;
		delete[] data;
	}

	void StringBuilder::Clear() {
		KillData();
		this->capacity = 8;
		data = new char* [this->capacity];
		lastString = 0;
		StringBuilder::zeroArr(data, this->capacity);
	}

	StringBuilder::StringBuilder(unsigned int capacity) {
		if (capacity <= 0) capacity = 8;
		this->capacity = capacity;
		data = new char* [this->capacity];
		lastString = 0;
		resultLen = 0;
		StringBuilder::zeroArr(data, this->capacity);
	}

	StringBuilder::StringBuilder(const char* string) : StringBuilder() {
		Append(string);
	}

	StringBuilder::StringBuilder(const String& str) : StringBuilder() {
		Append(str);
	}

	StringBuilder::StringBuilder(const String& str, unsigned int capacity) : StringBuilder(capacity) {
		Append(str);
	}

	StringBuilder::StringBuilder(const char* string, unsigned int capacity) : StringBuilder(capacity) {
		Append(string);
	}




	StringBuilder::~StringBuilder() {
		KillData();
	}


	void StringBuilder::Append(const char* string, bool endl) {
		int size = StringBuilder::calcLen(string);
		if (endl) size++;

		if (lastString == capacity)
			setCapacity();

		data[lastString] = new char[size];
		for (int i = 0; i < size - 1; i++)
			data[lastString][i] = string[i];
	
		if (endl) data[lastString][size - 2] = '\n'; 
		data[lastString][size - 1] = '\0';
		resultLen += size - 1;
		lastString++;
	}

	void StringBuilder::Append(const String& string, bool endl)	{
		int size = string.Size();
		if (endl) size++;

		if (lastString == capacity) setCapacity();

		data[lastString] = new char[size];

		for (int i = 0; i < size - 1; i++)
			data[lastString][i] = string[i];

		if (endl) data[lastString][size - 2] = '\n';

		data[lastString][size - 1] = '\0';
		resultLen += size - 1;
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
		StringBuilder::zeroArr(newData, newCapacity);

		for (int i = 0; i < lastString; i++)
			newData[i] = data[i];

		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	String StringBuilder::ToString() const {
		char* result = new char[resultLen + 1];
		unsigned int currentPosition = 0;
		for (unsigned int s = 0; s < lastString; s++) {
			int i = 0;
			while (data[s][i] != '\0')
				result[currentPosition++] = data[s][i++];
		}
		result[resultLen] = '\0';
		String res(result);

		return res;
	}

	std::ostream& operator<<(std::ostream& in, String& p)
	{
		if (p.size != 0)
			in << p.data << std::endl;

		return in;
	}

	std::istream& operator>>(std::istream& in, String& p)
	{
		char* buffer = new char[_MAX_PATH];
		std::cin.getline(buffer, _MAX_PATH);
		int size = String::StrLen(buffer);

		if (!p.Empty())
			p.Сlear();

		p.data = new char[size];
		p.size = size;
		for (int i = 0; i < size; i++)
			p.data[i] = buffer[i];

		return in;
	}


#pragma region BitString
	BitString::BitString() {
		data = nullptr;
		size = 0;
	}

	BitString::~BitString()	{
		Сlear();
	}

	BitString::BitString(const BitString& original) {
		if (original.size > 0) {
			data = new char[original.size];
			this->size = original.size;
			for (size_t i = 0; i < size; i++)
				data[i] = original.data[i];
		}
	}

	void BitString::operator=(const BitString& original)
	{
		if (this->data != nullptr) Сlear();

		if (original.size > 0) {
			data = new char[original.size];
			this->size = original.size;
			for (size_t i = 0; i < size; i++)
				data[i] = original.data[i];
		}

	}

	int BitString::to_decimal() {
		int res = 0;

		for (int i = size - 2, power = 0; i >= 0; i--, power++) {
			int tmp = data[i] - '0';
			if (tmp == 1) res += pow(2, power);
		}

		return res;
	}


	bool operator==(BitString& first, BitString& second) {
		if (first.size != second.size) return false;

		for (size_t i = 0; i < first.size; i++)
			if (first.data[i] != second.data[i])
				return false;

		return true;
	}

	bool operator!=(BitString& first, BitString& second) {
		if (first.size != second.size)
			return true;

		for (size_t i = 0; i < first.size; i++)
			if (first.data[i] != second.data[i]) return true;

		return false;
	}

	BitString& operator+=(BitString& first, BitString& second) {
		BitString lst1 = (first.size < second.size) ? first : second;
		BitString lst2 = (first.size < second.size) ? second : first;

		for (size_t i = lst1.size - 1; i < lst2.size - 1; i++)
			lst1 = '0' + lst1;

		BitString result;
		int carry = 0;

		for (int i = lst2.Size() - 1; i >= 0; i--) {
			int first = lst1.data[i] - '0';
			int second = lst2.data[i] - '0';
			char sum = (first ^ second ^ carry) + '0';
			result = sum + result;
			std::cout << result << std::endl;
			carry = (first ^ carry) | (second ^ carry) | (first ^ second);
		}

		if (carry)
			result = '1' + result;

		return result;
	}

	BitString operator+(char symbol, BitString& second) {
		BitString res;
		res.Cat(symbol);
		res.Cat(second.c_str());
		return res;
	}
#pragma endregion BitString
}


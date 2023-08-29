#pragma once
#include <cassert>
#include<iostream>

namespace DataContainers{
	class String
	{
	protected:
		char* data;
		unsigned int size;
	public:
		String();
		String(const char*);
		String(const String&);
		String(size_t, char);
		~String();

		char operator[](unsigned int n) const;

		friend std::ostream& operator<<(std::ostream& in, String& p);
		friend std::istream& operator>>(std::istream& in, String& p);


		String operator+(String str);

		char* operator +(const char* str);

		void operator +=(const char* str);

		void operator +=(String str);
		String& operator =(const char* str);
		String& operator =(String str);


		static int StrLen(const char* str);
		static int StrLen(char*);

		void kbInput();


		void Cat(const char*);
		void Cat(const char);

		void revers();
		bool Empty() const;

		void Ñlear();
		void PushBack(char);

		char* c_str();
		int Size() const;
	};

	class StringBuilder
	{
	private:
		char** data;
		unsigned int lastString;
		unsigned int capacity;
		unsigned int resultLen;

		static void zeroArr(char**& arrToNull, unsigned int count);
		static int calcLen(const char* string);
		void setCapacity(unsigned int newCapacity = 0);
		void KillData();

	public:
		explicit StringBuilder(unsigned int capacity = 8);
		StringBuilder(const char* string);
		StringBuilder(const String& str);
		StringBuilder(const String& str, unsigned int capacity);
		StringBuilder(const char* string, unsigned int capacity);

		~StringBuilder();

		void Clear();

		void Append(const char* string, bool endLine = false);
		void Append(const String& string, bool endLine = false);
		void AppendLine(const char* string);

		void Print();
		unsigned int Capacity()  const;
		String ToString() const;

	};

	class BitString : public String
	{
	public:
		BitString();
		~BitString();
		BitString(const char* string) {
			int size = StrLen(string);
			bool flag = true;

			for (size_t i = 0; i < size - 1; i++) {
				if (string[i] != '0' && string[i] != '1') {
					flag = false;
					break;
				}
			}


			if (flag) {
				data = new char[size];
				for (size_t i = 0; i < size; i++)
					data[i] = string[i];
				size = size;
			}
		}

		BitString(const BitString&);
		void operator=(const BitString&);

		friend bool operator==(BitString& first, BitString& second);
		friend bool operator!=(BitString& first, BitString& second);
		friend BitString& operator+=(BitString& first, BitString& second);
		friend BitString operator+(char, BitString& second);
		char* c_str() const {
			return data;
		}


		int to_decimal();
	};
}


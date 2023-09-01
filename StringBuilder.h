#pragma once
#include "String.h"

namespace DataContainers
{
	class StringBuilder
	{
	private:
		char** data;
		unsigned int lastString;
		unsigned int capacity;
		unsigned int size;

		static void zeroArr(char**& arrToNull, unsigned int count);
		static int calcLen(const char* string);
		void setCapacity(unsigned int newCapacity = 0);
		void KillData();

	public:

		StringBuilder(unsigned int capacity);
		~StringBuilder();

		void Clear();

		void Append(const char* string, bool endLine = false);
		void Append(const DataContainers::String& string, bool endLine = false);
		void AppendLine(const char* string);
		unsigned int Capacity()  const;

		void Print();

		String ToString() const;
	};
}



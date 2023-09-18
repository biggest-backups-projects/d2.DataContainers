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
		void setCapacity(unsigned int newCapacity = 0);
	public:

		StringBuilder(unsigned int capacity);
		~StringBuilder();

		void Clear();

		void Append(const char* string, bool endLine = false);
		void Append(const DataContainers::String& string, bool endLine = false);
		void AppendLine(const char* string);
		unsigned int Capacity()  const;
		static int calcLen(const char* string);
#ifdef DEBUG
		void DEBUG() {
			std::cout << "\n ----- \n String Builder info : \n Capacity: "
				<< capacity
				<< " \n lastString: "
				<< lastString << "\n";

			for (int i = 0; i < lastString; i++)
				std::cout << i << " => " << data[i] << "\n";
		}
#endif

		String ToString() const;
	};
}



#pragma once
#include<iostream>
#include<fstream>
#include<istream>

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
		~String();

		static unsigned int CountSize(const char* str);
	
		String Cat(const char*);
		String Cat(const String& str);
		String Revers() const;

		void Ñlear();

		bool Empty() const;
		char* CStr() const;
		unsigned int Size() const;
		char operator[](unsigned int index) const;

		friend std::ostream& operator<<(std::ostream& os, String& str);
		friend std::istream& operator>>(std::istream& in, String& str);

		char* operator+(const char* str);
		void operator+=(const char* str);
		void operator+=(const String& str);
		String operator+(const String& str);
		String& operator=(const char* str);
		String& operator=(const String& str);
	};

	

	
}


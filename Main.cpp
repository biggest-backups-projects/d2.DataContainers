#include <iostream>
#include "String.h"	
#include "Dictionary.h"
#include "StringBuilder.h"
using namespace std;
using namespace DataContainers;

int main() {
	srand(time(0));
	StringBuilder sb;
	sb.Append("Hello", true);
	sb.Append(" World!");
	sb.AppendLine();

	String str1("GILY");
	String str2("GEELY");
	cout << str1.Similarity(str2) << "%";

}

#include <iostream>
#include "String.h"	
#include "Dictionary.h"
#include "Vector.h"
using namespace std;
using namespace DataContainers;

int main() {
	srand(time(0));

	Vector<int> kv = { 54, 32, 55, 22, 2, 1, 6, 9, 88 };
	Dictionary<int, int> dict;
	for(const auto& elem : kv) {
		dict.Insert(elem, elem);
	}

	for (const auto& [key, value] : dict) {
		cout << key << " ";
	}

}

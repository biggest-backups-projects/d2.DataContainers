#include <iostream>
#include "Matrix.h"
#include "LinkedList.h"
#include "List.h"
#include "String.h"
#include "Vector.h"
#include "Dictionary.h"
using namespace std;
using namespace DataContainers;

int main() {
	srand(time(0));
	Dictionary<int, int> dict;
	
	//Vector<unsigned int> keys = { 3, 5, 7, 8, 9 };
	Vector<int> keys;

	for (size_t i = 0; i < 20; i++)
		keys.PushBack(i);

	for(const auto& key : keys)
		dict.Insert(key, key);

	int i = 0;
}


#include <iostream>
#include "Matrix.h"
#include "LinkedList.h"
#include "List.h"
#include "String.h"
#include "Vector.h"

using namespace std;
using namespace DataContainers;

int main() {
	Vector<int> test;

	for (size_t i = 0; i < 20; i++) {
		test.PushBack(i);
	}


	for(auto& i : test) {
		cout << i << " ";
	}

	/*test.Filter([](int i) { return i % 2 == 0; })
	.ForEach([](int i) { std::cout << i << std::endl; });*/
}


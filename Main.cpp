#include <iostream>
#include "String.h"	
#include "Dictionary.h"
#include "Vector.h"
using namespace std;
using namespace DataContainers;

int main() {
	srand(time(0));

	String aboba(" ab  ob a      ");

	auto i = aboba.Split();

	for (const auto& elem : i) {
		cout << elem << endl;
	}


}

#pragma once
#include <iostream>
#include "Matrix.h"
#include "String.h"
using namespace std;
using namespace DataContainers;

int main() {
	for(auto row : String("1, 2, 3, 4").Split(", "))
		cout << row << '\n';
}

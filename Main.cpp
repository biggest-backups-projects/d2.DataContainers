#include <iostream>
#include "Matrix.h"
#include "LinkedList.h"
#include "List.h"
#include "String.h"	
#include "Vector.h"
#define DEBUG
#include "Dictionary.h"
using namespace std;
using namespace DataContainers;

int main() {
	srand(time(0));

	//N1-----
	/*auto data1 = new int[9] {2, -1, -3,
							 8, -7, -6,
							-3, 4, 2};

	auto data2 = new int[9] {3, 5, -6,
		                     2, 4, 3,
							-3, 1, 1};

	Matrix<int> m(3, 3, data1);
	Matrix<int> m2(3, 3, data2);

	m.Print();
	cout << "\n\n";
	m2.Print();
	cout << "\n\n\n\n\n";

	auto t = m.Transposition();
	t.Print();
	cout << "\n\n\n";

	auto tmp = 2 * t;
	tmp.Print();
	cout << "\n\n\n";

	auto b = m * m2;
	b.Print();
	cout << "\n\n\n";

	auto res = b - tmp;
	res.Print(2, 1);*/

	//N2
	/*auto data1 = new int[16] {2, 5, 7, 1,
							 1, -7, 0, 1,
		                     0, 5, 3, 2,
							 1, -1, 8, 4
							};

	Matrix<int> m(data1, 4, 4);
	cout << m.Determinant();*/

	//N3

	auto data1 = new double[9] {0, 3, 2,
		                     1, 2, -3,
							 3, 4, 1 };

	Matrix<double> m(data1, 3, 3);

	m.test().Print();




}


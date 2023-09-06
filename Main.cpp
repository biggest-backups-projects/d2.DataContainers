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

	//List<int> lst;
	//for (size_t i = 0; i < 10; i++) {
	//	lst.PushBack(i);
	//}

	//for(const auto& elem : lst)
	//{
	//	cout << elem << endl;
	//}

	srand(time(0));
	Dictionary<int, int> dict;
	//Vector<unsigned int> keys = { 10, 50, 5, 8, 3, 60, 40, 9, 35, 30, 45, 37, 4, 2};
	Vector<unsigned int> keys = {100, 4, 5, 2, 3, 1, 0, 11, 22, 15, 17, 25};

	for(unsigned int i = 0; i < keys.Size(); i++) {
		//cout << keys[i] << endl;
		dict.Insert(Pair<int, int>(keys[i], i));
	}
	cout << "\n\n\n";
	//dict.ForEach([](int key) { cout << key << " "; });
	cout << "\n\n\n";
	dict.PrintFormat();
	
	//dict.Delete(40);	
	//dict.Print(); 


	int i = 0;
}


#include "pch.h"
#include "../../DataContainers/Vector.h"
#include "../../DataContainers/String.h"
using namespace DataContainers;


// Vector tests
TEST(VectorTests, Initializing) {
	//Initializing
	Vector<int> vector = { 1,2, 3, 4 };
	EXPECT_EQ(vector[0], 1);
	EXPECT_EQ(vector[1], 2);
	EXPECT_EQ(vector[2], 3);
	EXPECT_EQ(vector[3], 4);
	EXPECT_EQ(vector.Size(), 4);

	// Reinitialization
	vector = { 9, 8, 7, 6, 5 };
	EXPECT_EQ(vector[0], 9);
	EXPECT_EQ(vector[1], 8);
	EXPECT_EQ(vector[2], 7);
	EXPECT_EQ(vector[3], 6);
	EXPECT_EQ(vector[4], 5);
	EXPECT_EQ(vector.Size(), 5);
}

TEST(VectorTests, InsertData) {
	Vector<int> vector;

	for (size_t i = 0; i < 10; i++)
		vector.Append(i);
	EXPECT_EQ(vector.Size(), 10);

	for (size_t i = 0; i < 10; i++)
		EXPECT_EQ(vector[i], i);

	vector.Insert(999, 0);
	EXPECT_EQ(vector[0], 999);
	EXPECT_EQ(vector.Size(), 11);

	vector.Insert(666, 3);
	EXPECT_EQ(vector[3], 666);
	
}

TEST(VectorTests, DeleteData) {
	Vector<int> vector = { 1, 2, 3, 4, 5, 6 };

	vector.PopFront();
	for (size_t i = 0; i < vector.Size(); i++)
		EXPECT_EQ(vector[i], i + 2);

	vector = { 1, 2, 3, 4, 5, 6 };
	vector.Remove(5);

	EXPECT_EQ(vector.Size(), 5);
}


// String tests

TEST(StringTests, Initializing) {
	String test("Hello, World!");
	EXPECT_EQ(strcmp(test.CStr(), "Hello, World!"), 0);

	// Reinitialization
	test = "Test";
	EXPECT_EQ(strcmp(test.CStr(), "Test"), 0);
}


TEST(StringTests, Operators) {
	String str1("Hello, World!");
	String str2("Hello, World!");

	EXPECT_EQ(str1 == str2, true);
	EXPECT_EQ(strcmp(str1 + "test", "Hello, World!test"), 0);
}
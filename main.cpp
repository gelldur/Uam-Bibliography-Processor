#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char** argv)
{
	cout << "Hello, World!" << endl;
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}

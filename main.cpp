#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <gtest/gtest.h>

#include <parser/BibParser.h>
#include <DoiGeter.h>
#include <NameValidator.h>

using namespace std;

int Main(const vector<string>& args)
{
	cout << "args:" << args.size() << endl;
	for (auto& element : args)
	{
		cout << element << endl;
	}

	if (args.size() < 2)
	{
		cout << "Please pass file name to process" << endl;
		return 1;
	}

	ifstream file(args[1]);
	if (file.is_open() == false)
	{
		cout << "Can't open file:" << args[1] << endl;
		return 2;
	}

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	BibParser parser;
	auto bibs = parser.parse(content);
	cout << "Parsing file success!" << endl;
	cout << "Found:" << bibs.size() << " bibs" << endl;
	for (auto& element : bibs)
	{
		cout << element.getCite() << endl;
	}

	{
		DoiGeter doiGetet;
		doiGetet.checkMissingDoi(bibs);
	}
	{
		NameValidator nameValidator;
		nameValidator.check(bibs);
	}
	return 0;
}

int main(int argc, char** argv)
{
	vector<string> args;
	for (int i = 0; i < argc; ++i)
	{
		args.emplace_back(argv[i]);
	}

	if (std::find(args.begin(), args.end(), "--run_tests") != args.end())
	{
		cout << "Running tests" << endl;
		::testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();
		return 0;
	}

	return Main(args);
}

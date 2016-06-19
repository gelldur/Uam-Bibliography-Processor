#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <gtest/gtest.h>

#include <parser/BibParser.h>
#include <doi/Crossref.h>
#include <NameValidator.h>
#include <Config.h>

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

	auto configFlag = std::find(args.begin(), args.end(), "--config");
	if (configFlag == args.end())
	{
		cout << "Missing config flag (--config FILE_PATH)" << endl;
		return 1;
	}

	Config config{*(++configFlag)};

	auto inputFlag = std::find(args.begin(), args.end(), "--input");
	if (inputFlag == args.end())
	{
		cout << "Missing input flag (--input FILE_PATH)" << endl;
		return 2;
	}

	ifstream file(*(++inputFlag));
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
	//	for (auto& element : bibs)
	//	{
	//		cout << element.getCite() << endl;
	//	}

	if (config.isCrossrefEnabled())
	{
		Crossref crossref{config};
		crossref.fetchDoi(bibs);
	}
	if (config.isNameValidatorEnabled())
	{
		NameValidator nameValidator{config};
		nameValidator.check(bibs);
	}

	cout << "Saving BIBS" << endl;

	std::ofstream fileOutput((*inputFlag) + ".new");
	if (file.is_open() == false)
	{
		std::cout << "Can't save BIBS!" << std::endl;
		return 3;
	}
	for (const auto& bib : bibs)
	{
		fileOutput << bib.toString();
		fileOutput.flush();
	}
	fileOutput.flush();
	fileOutput.close();

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

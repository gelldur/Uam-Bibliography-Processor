//
// Created by Dawid Drozd aka Gelldur on 6/18/16.
//

#include "NameValidator.h"

#include <iostream>

using namespace std;

void NameValidator::check(std::vector<Bib>& bibs)
{
	const string KEY_JOURNAL = "journal";
	auto replaceMap = _config.getReplaceMap();
	for (auto& bib : bibs)
	{
		const auto& journal = bib.getValue(KEY_JOURNAL);
		std::string newName;
		auto found = replaceMap.find(journal);
		if (found == replaceMap.end())
		{
			cout << "Journal not found: " << journal << endl;
			cout << "Is it correct? Write (y)es or correct name" << endl;
			while (newName.empty())
			{
				getline(cin, newName);
			}
			if (newName == "y" || newName == "yes" || newName == "YES" || newName == "Y")
			{
				newName = journal;
			}

			replaceMap.emplace(journal, newName);
			_config.updateReplaceMap(replaceMap);
		}
		else
		{
			newName = found->second;
		}
		bool replace = true;
		if (_config.isAskBeforeReplace() && newName != journal)
		{
			cout << "Want to change name\nfrom: " << journal << "\nto: " << newName << endl;
			cout << "(y)es or (n)o ?" << endl;
			string response;
			cin >> response;
			if (response == "y" || response == "yes" || response == "YES" || response == "Y")
			{
				replace = true;
			}
			else
			{
				replace = false;
			}
		}
		if (replace)
		{
			bib.setValue(KEY_JOURNAL, newName);
		}
	}
}


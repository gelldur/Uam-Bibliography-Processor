//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#include "BibParser.h"

using namespace std;

std::vector<Bib> BibParser::parse(const std::string& text)
{
	//Find all bib's
	int lastFind = 0;
	const std::string KEY_BIB = "\\bib";
	while ((lastFind = text.find(KEY_BIB, lastFind)) != string::npos)
	{
		lastFind += KEY_BIB.length();

	}

	return {};
}

Bib BibParser::parse(const char* bibBegin, const char* bibEnd)
{
	return {};
}




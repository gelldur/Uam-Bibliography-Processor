//
// Created by Dawid Drozd aka Gelldur on 5/26/16.
//

#include "BibParser.h"

#include <sstream>
#include <cassert>

using namespace std;

std::vector<Bib> BibParser::parse(const std::string& text)
{
	std::vector<Bib> found;

	//Find all bib's
	int lastFind = 0;
	const std::string KEY_BIB = "\\bib";
	while ((lastFind = text.find(KEY_BIB, lastFind)) != string::npos)
	{
		lastFind += KEY_BIB.length();

		Bib bib;

		auto cite = extractBraces(text, lastFind);
		lastFind = cite.first;
		bib.setCite(cite.second);

		auto type = extractBraces(text, lastFind);
		lastFind = type.first;
		bib.setEntryType(type.second);

		auto content = extractBraces(text, lastFind);
		lastFind = content.first;
		parse(content.second, bib);

		found.emplace_back(bib);
	}

	return found;
}

void BibParser::parse(const std::string& text, Bib& bib)
{
	const auto& keyValues = extract(text);
	bib.add(keyValues);
}

std::pair<size_t, std::string> BibParser::extractBraces(const std::string& text, size_t offset)
{
	int open = 0;
	size_t start = offset;
	size_t end = 0;
	for (size_t i = offset; i < text.length(); ++i)
	{
		if (text[i] == '{')
		{
			if (open == 0)
			{
				start = i + 1;
			}
			++open;
		}
		else if (text[i] == '}' && open > 0)
		{
			--open;
			if (open < 1)
			{
				end = i;
				break;
			}
		}
	}

	if (start < end)
	{
		return make_pair(end + 1, text.substr(start, end - start));
	}
	return {text.length(), "error"};
}

std::vector<KeyValue> BibParser::extract(const std::string& text)
{
	//Find all key=value
	std::vector<KeyValue> keyValues;

	int lastFind = 0;
	const std::string KEY = "={";
	while ((lastFind = text.find(KEY, lastFind)) != string::npos)
	{
		//extract key
		--lastFind;
		int keyStart = lastFind;
		while (keyStart > -1 && isAsciiLetter(text[keyStart]))
		{
			--keyStart;
		}
		assert(keyStart + 1 < lastFind && "Invalid!");

		auto value = extractBraces(text, lastFind + KEY.length());
		KeyValue keyValue(text.substr(keyStart + 1, lastFind - keyStart), value.second);

		keyValues.emplace_back(keyValue);
		lastFind = value.first;
	}

	return keyValues;
}

bool BibParser::isAsciiLetter(char letter)
{
	return (letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z');
}

std::vector<std::string>& BibParser::split(const std::string& text, char delim, std::vector<std::string>& elements)
{
	std::stringstream ss(text);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elements.emplace_back(item);
	}
	return elements;
}

std::vector<std::string> BibParser::split(const std::string& text, char delim)
{
	std::vector<std::string> elems;
	split(text, delim, elems);
	return elems;
}


